#include "stdafx.h"
#include "Object.h"
#include "Model.h"

Object::Object()
{
	m_v3DefaultColor = Vector3(1.f, 1.f, 1.f);
}

Object::~Object()
{
}

void Object::setModel(Model * pModel)
{
	m_pModel = pModel;
}

void Object::setColor(const Vector3 & v3DefaultColor)
{
	m_v3DefaultColor = v3DefaultColor;
}

void Object::setPosition(float x, float y, float z)
{
	m_v3Position = Vector3(x, y, z);
}

void Object::setPosition(const Vector3 & v3Position)
{
	m_v3Position = v3Position;
}

void Object::move(const Vector3 & v3Direction, float fDistance)
{
	m_v3Position.x += v3Direction.x*fDistance;
	m_v3Position.y += v3Direction.y*fDistance;
	m_v3Position.z += v3Direction.z*fDistance;
}

void Object::move(float fDistanceX, float fDistanceY, float fDistanceZ)
{
	m_v3Position.x += fDistanceX;
	m_v3Position.y += fDistanceY;
	m_v3Position.z += fDistanceZ;
}

void Object::rotate(float fRadAngle, const Vector3 & v3Axis)
{
	m_qrRotation.rotate(fRadAngle, v3Axis);
}

void Object::update(float fDeltaTime)
{
}

void Object::render()
{
	glPushMatrix();
	glColor3f(m_v3DefaultColor.x, m_v3DefaultColor.y, m_v3DefaultColor.z);
	glTranslatef(m_v3Position.x, m_v3Position.y, m_v3Position.z);
	if (m_pModel)
		m_pModel->render();
	glPopMatrix();
	glColor3f(1.f, 1.f, 1.f);
}
