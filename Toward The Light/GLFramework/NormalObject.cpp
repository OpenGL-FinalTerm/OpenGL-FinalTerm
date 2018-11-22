#include "stdafx.h"
#include "NormalObject.h"

NormalObject::NormalObject()
{
	m_v3DefaultColor = Vector3(1.f, 1.f, 1.f);
	m_v3Scale = Vector3(1.f, 1.f, 1.f);
}

NormalObject::~NormalObject()
{
}

void NormalObject::setModel(std::string Shape, float size, bool wire)
{
	m_sType = Shape;
	m_fModelSize = size;
	m_wireType = wire;
}

void NormalObject::setColor(const Vector3 & v3DefaultColor)
{
	m_v3DefaultColor = v3DefaultColor;
}

void NormalObject::setPosition(float x, float y, float z)
{
	m_v3Position = Vector3(x, y, z);
}

void NormalObject::setPosition(const Vector3 & v3Position)
{
	m_v3Position = v3Position;
}

void NormalObject::move(const Vector3 & v3Direction, float fDistance)
{
	m_v3Position.x += v3Direction.x*fDistance;
	m_v3Position.y += v3Direction.y*fDistance;
	m_v3Position.z += v3Direction.z*fDistance;
}

void NormalObject::move(float fDistanceX, float fDistanceY, float fDistanceZ)
{
	m_v3Position.x += fDistanceX;
	m_v3Position.y += fDistanceY;
	m_v3Position.z += fDistanceZ;
}

void NormalObject::scale(const Vector3 & v3Axis, float fRatio)
{
	/*m_v3Scale.x += v3Axis.x*fRatio;
	m_v3Scale.y += v3Axis.y*fRatio;
	m_v3Scale.z += v3Axis.z*fRatio;*/
}

void NormalObject::scale(float fRatioX, float fRatioY, float fRatioZ)
{
	m_v3Scale.x = fRatioX;
	m_v3Scale.y = fRatioY;
	m_v3Scale.z = fRatioZ;
}

void NormalObject::rotate(float fRadAngle, const Vector3 & v3Axis)
{
	m_qrRotation.rotate(fRadAngle, v3Axis);
}

void NormalObject::update(float fDeltaTime)
{
}

void NormalObject::render()
{
	glPushMatrix();
	glColor3f(m_v3DefaultColor.x, m_v3DefaultColor.y, m_v3DefaultColor.z);
	glTranslatef(m_v3Position.x, m_v3Position.y, m_v3Position.z);
	glMultMatrixf(&m_qrRotation.getRotationMatrix());
	glScalef(m_v3Scale.x, m_v3Scale.y, m_v3Scale.z);
	if (m_wireType)
	{
		if (m_sType == "Cube")
		{
			glutWireCube(m_fModelSize);
		}
		else if (m_sType == "Sphere")
		{
			glutWireSphere(m_fModelSize, 12, 12);
		}
		else if (m_sType == "Torus")
		{
			glutWireTorus(m_fModelSize, m_fModelSize - 50, 12, 12);
		}
	}
	else
	{
		if (m_sType == "Cube")
		{
			glutSolidCube(m_fModelSize);
		}
		else if (m_sType == "Sphere")
		{
			glutSolidSphere(m_fModelSize, 12, 12);
		}
		else if (m_sType == "Torus")
		{
			glutSolidTorus(m_fModelSize, m_fModelSize - 50, 12, 12);
		}
	}
	glPopMatrix();
	glColor3f(1.f, 1.f, 1.f);
}
