#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	init();
}

Camera::~Camera()
{
}

void Camera::init()
{
	m_v3Target.x = 0.f;
	m_v3Target.y = 0.f;
	m_v3Target.z = 0.f;

	m_v3Up.x = 0.f;
	m_v3Up.y = 1.f;
	m_v3Up.z = 0.f;

	m_v3PrevUp.x = 0.f;
	m_v3PrevUp.y = 1.f;
	m_v3PrevUp.z = 0.f;

	m_fDistance = 1.f;

	m_fFovy = 30.f;
	m_fNear = 0.1f;
	m_fFar = 1.f;

	m_nCursorType = -1;
	updateEye();
}

Vector3 Camera::getTarget()
{
	return m_v3Target;
}

Vector3 Camera::getUp()
{
	return m_v3Up;
}

Vector3 Camera::getEye()
{
	return m_v3Eye;
}

Vector3 Camera::getLook()
{
	return V3::subtract(m_v3Target, m_v3Eye);
}

Vector3 Camera::getRight()
{
	return V3::cross(getLook(), getUp());
}

float Camera::getDistance()
{
	return m_fDistance;
}

float Camera::getFovy()
{
	return m_fFovy;
}

float Camera::getNear()
{
	return m_fNear;
}

float Camera::getFar()
{
	return m_fFar;
}

void Camera::setTarget(const Vector3& v3Target)
{
	m_v3Target = v3Target;
}

void Camera::setUp(const Vector3& v3Up)
{
	m_v3PrevUp = v3Up;
}

void Camera::setDistance(float fDistance)
{
	m_fDistance = fDistance;
	updateEye();
}

void Camera::setSensitivity(float fSensitivity)
{
	if (!isZero(fSensitivity))
		m_fSensitivity = fSensitivity;
}

float Camera::getSensitivity()
{
	return m_fSensitivity;
}

void Camera::resetRotation()
{
	m_QuaternionRotation.resetQuaternion();
}

void Camera::setPerspective(float fFovy, float fNear, float fFar)
{
	m_fFovy = fFovy;
	m_fNear = fNear;
	m_fFar = fFar;
}

void Camera::updateEye()
{
	m_v3PrevEye = Vector3{ 0.f, 0.f, m_fDistance };
}

void Camera::rotate(float angle, const Vector3& axis)
{
	m_QuaternionRotation.rotate(angle, axis);
}

void Camera::rotate(int x, int y, bool blDrag, bool bInverseX, bool bInverseY)
{
	float fHorizontalDistance;
	float fVerticalDistance;

	float fx = float(x);
	float fy = float(y);

	int iScreenCenterX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	int iScreenCenterY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	if (!blDrag) {
		if (m_blMouseDrag)
			m_blMouseDrag = false;
		return;
	}
	if (!m_blMouseDrag)
	{
		m_v2MouseOldPos = Vector2{ fx, fy };
		m_v2MouseNewPos = m_v2MouseOldPos;
		m_blMouseDrag = true;
		return;
	}

	m_v2MouseOldPos = m_v2MouseNewPos;
	m_v2MouseNewPos = Vector2{ fx, fy };
	fHorizontalDistance = m_v2MouseNewPos.x - m_v2MouseOldPos.x;
	fVerticalDistance = m_v2MouseNewPos.y - m_v2MouseOldPos.y;

	float fFactor = m_fSensitivity / m_fDistance;

	fHorizontalDistance *= fFactor * float(bInverseX * 2 - 1);
	fVerticalDistance *= fFactor * float(bInverseY * 2 - 1);

	m_QuaternionRotation.rotate(fVerticalDistance, getRight());
	m_QuaternionRotation.rotate(fHorizontalDistance, getUp());
}

void Camera::ready(int nCursorType)
{
	float fAspect = static_cast<float>(glutGet(GLUT_WINDOW_WIDTH)) / static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT));

	if (nCursorType != m_nCursorType)
	{
		glutSetCursor(nCursorType);
		m_nCursorType = nCursorType;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(m_fFovy, fAspect, m_fNear, m_fFar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Matrix4x4 m4x4RotationMatrix = m_QuaternionRotation.getRotationMatrix();

	Vector4 v4Eye = V4::mult(m4x4RotationMatrix, Vector4(m_v3PrevEye.x, m_v3PrevEye.y, m_v3PrevEye.z, 0.f));
	Vector4 v4Up = V4::mult(m4x4RotationMatrix, Vector4(m_v3PrevUp.x, m_v3PrevUp.y, m_v3PrevUp.z, 0.f));

	m_v3Eye = Vector3(v4Eye.x, v4Eye.y, v4Eye.z);
	m_v3Up = Vector3(v4Up.x, v4Up.y, v4Up.z);

	gluLookAt(
		m_v3Eye.x, m_v3Eye.y, m_v3Eye.z,
		m_v3Target.x, m_v3Target.y, m_v3Target.z,
		m_v3Up.x, m_v3Up.y, m_v3Up.z);
}