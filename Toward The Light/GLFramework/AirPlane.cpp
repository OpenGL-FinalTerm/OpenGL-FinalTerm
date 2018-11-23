#include "stdafx.h"
#include "AirPlane.h"

AirPlane::AirPlane()
{
	m_v3DefaultColor = Vector3(1.f, 1.f, 1.f);
	m_v3Scale = Vector3(1.f, 1.f, 1.f);
	m_spin = 0;
}

AirPlane::~AirPlane()
{

}

void AirPlane::setModel(float size)
{
	m_fModelSize = size;
}

void AirPlane::setColor(const Vector3 & v3DefaultColor)
{
	m_v3DefaultColor = v3DefaultColor;
}

void AirPlane::setPosition(float x, float y, float z)
{
	m_v3Position = Vector3(x, y, z);
}

void AirPlane::setPosition(const Vector3 & v3Position)
{
	m_v3Position = v3Position;
}

void AirPlane::move(const Vector3 & v3Direction, float fDistance)
{
	m_v3Position.x += v3Direction.x*fDistance;
	m_v3Position.y += v3Direction.y*fDistance;
	m_v3Position.z += v3Direction.z*fDistance;
}

void AirPlane::move(float fDistanceX, float fDistanceY, float fDistanceZ)
{
	m_v3Position.x += fDistanceX;
	m_v3Position.y += fDistanceY;
	m_v3Position.z += fDistanceZ;
}

void AirPlane::scale(const Vector3 & v3Axis, float fRatio)
{
	/*m_v3Scale.x += v3Axis.x*fRatio;
	m_v3Scale.y += v3Axis.y*fRatio;
	m_v3Scale.z += v3Axis.z*fRatio;*/
}

void AirPlane::scale(float fRatioX, float fRatioY, float fRatioZ)
{
	m_v3Scale.x = fRatioX;
	m_v3Scale.y = fRatioY;
	m_v3Scale.z = fRatioZ;
}

void AirPlane::rotate(float fRadAngle, const Vector3 & v3Axis)
{
	m_qrRotation.rotate(fRadAngle, v3Axis);
}

void AirPlane::update(float fDeltaTime)
{
	m_spin++;
}

void AirPlane::render()
{
	glPushMatrix();
	{
		glTranslatef(m_v3Position.x, m_v3Position.y, m_v3Position.z);
		glMultMatrixf(&m_qrRotation.getRotationMatrix());
		glScalef(m_v3Scale.x, m_v3Scale.y, m_v3Scale.z);

		glColor3f(m_v3DefaultColor.x + 0.7f, m_v3DefaultColor.y, m_v3DefaultColor.z);
		glutSolidCone(m_fModelSize / 5, m_fModelSize, 12, 12);
		glColor3f(1.f, 1.f, 1.f);
		//glutWireCone(m_fModelSize / 5 + 3, m_fModelSize + 3, 12, 12);
		glPushMatrix();
		{
			glTranslatef(0.f, 0.f, m_fModelSize);
			glRotatef(m_spin*2.707, 0.f, 0.f, 1.f);
			glScalef(0.1f, 1.f, 0.1f);
			glColor3f(0.f, 1.f, 1.f);
			glutSolidCube(m_fModelSize);
		}glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.f, 0.f, m_fModelSize);
			glRotatef(m_spin*2.707, 0.f, 0.f, 1.f);
			glScalef(1.f, 0.1f, 0.1f);
			glColor3f(0.f, 1.f, 1.f);
			glutSolidCube(m_fModelSize);
		}glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.f, m_fModelSize / 3.f, m_fModelSize / 3.f);
			glScalef(0.1f, 1.f, 1.f);
			glColor3f(0.f, 0.f, 1.f);
			glutSolidCube(m_fModelSize / 2);
			glColor3f(1.f, 1.f, 1.f);
			//glutWireCube(m_fModelSize / 5 + 10);
		}glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(m_fModelSize / 5.f, 0.f, m_fModelSize / 5.f);
			glScalef(1.f, 0.1f, 1.f);
			glColor3f(0.f, 0.3f, 0.f);
			glutSolidCube(m_fModelSize / 2);
			glColor3f(1.f, 1.f, 1.f);
			//glutWireCube(m_fModelSize / 5 + 10);

			glTranslatef(- 2*m_fModelSize / 5.f, 0.f , 0.f);
			glColor3f(0.f, 0.3f, 0.f);
			glutSolidCube(m_fModelSize / 2);
			glColor3f(1.f, 1.f, 1.f);
			//glutWireCube(m_fModelSize / 5 + 10);
		}glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0.f, 0.f, -m_fModelSize / 10.f);
			glScalef(1.3f, 0.2f, 0.2f);
			glColor3f(0.3f, 0.3f, 0.3f);
			glutSolidCube(m_fModelSize);
			glColor3f(1.f, 1.f, 1.f);
			//glutWireCube(m_fModelSize + 10);
		}glPopMatrix();

	}glPopMatrix();
	glColor3f(1.f, 1.f, 1.f);
}