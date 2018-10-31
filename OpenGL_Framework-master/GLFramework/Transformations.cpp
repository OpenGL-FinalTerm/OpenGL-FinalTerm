#include "stdafx.h"
#include "Transformations.h"

QuaternionRotation::QuaternionRotation()
{
	m_RotationQuaternion.x = 0.f;
	m_RotationQuaternion.y = 0.f;
	m_RotationQuaternion.z = 0.f;
	m_RotationQuaternion.w = 1.f;
}

QuaternionRotation::~QuaternionRotation()
{
}

Matrix4x4 QuaternionRotation::getRotationMatrix()
{
	Matrix4x4 m4x4Result;

	float x = m_RotationQuaternion.x;
	float y = m_RotationQuaternion.y;
	float z = m_RotationQuaternion.z;
	float w = m_RotationQuaternion.w;

	m4x4Result[0][0] = 1.f - (2.f*y*y) - (2.f*z*z);
	m4x4Result[1][0] = (2.f*x*y) + (2.f*z*w);
	m4x4Result[2][0] = (2.f*x*z) - (2.f*y*w);
	m4x4Result[3][0] = 0.f;

	m4x4Result[0][1] = (2.f*x*y) - (2.f*z*w);
	m4x4Result[1][1] = 1.f - (2.f*x*x) - (2.f*z*z);
	m4x4Result[2][1] = (2.f*y*z) + (2.f*x*w);
	m4x4Result[3][1] = 0.f;

	m4x4Result[0][2] = (2.f*x*z) + (2.f*y*w);
	m4x4Result[1][2] = (2.f*y*z) - (2.f*x*w);
	m4x4Result[2][2] = 1.f - (2.f*x*x) - (2.f*y*y);
	m4x4Result[3][2] = 0.f;

	m4x4Result[0][3] = 0.f;
	m4x4Result[1][3] = 0.f;
	m4x4Result[2][3] = 0.f;
	m4x4Result[3][3] = 1.f;

	return m4x4Result;
}

Vector3 QuaternionRotation::rotatePoint(const Vector3 & v3Point)
{
	Vector4 v4Point(v3Point.x, v3Point.y, v3Point.z, 0.f);
	v4Point = V4::mult(V4::mult(m_RotationQuaternion, v4Point), V4::conj(m_RotationQuaternion));
	return Vector3(v4Point.x, v4Point.y, v4Point.z);
}

void QuaternionRotation::resetQuaternion()
{
	m_RotationQuaternion.x = 0.f;
	m_RotationQuaternion.y = 0.f;
	m_RotationQuaternion.z = 0.f;
	m_RotationQuaternion.w = 1.f;
}

void QuaternionRotation::rotate(float fRadAngle, Vector3 v3Axis)
{
	Vector4 v4LocalQuaternion;

	v3Axis = V3::normalize(v3Axis);
	float fHalfAngle = fRadAngle * 0.5f;

	v4LocalQuaternion.x = v3Axis.x * sin(fHalfAngle);
	v4LocalQuaternion.y = v3Axis.y * sin(fHalfAngle);
	v4LocalQuaternion.z = v3Axis.z * sin(fHalfAngle);
	v4LocalQuaternion.w = cos(fHalfAngle);

	m_RotationQuaternion = V4::mult(v4LocalQuaternion, m_RotationQuaternion);
}
