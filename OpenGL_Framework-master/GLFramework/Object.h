#pragma once
#include "Transformations.h"

class Model;

class Object
{
public:
	Vector3				m_v3Position;
	QuaternionRotation	m_qrRotation;
	Vector3				m_v3Scale;

	Vector3				m_v3DefaultColor;

	Model*				m_pModel;

public:

	Object();
	~Object();

	void setModel(Model* pModel);

	void setColor(const Vector3& v3DefaultColor);
	void setPosition(float x, float y, float z);
	void setPosition(const Vector3& v3Position);

	virtual void move(const Vector3& v3Direction, float fDistance);
	virtual void move(float fDistanceX, float fDistanceY, float fDistanceZ);

	virtual void rotate(float fRadAngle, const Vector3& v3Axis);

	virtual void update(float fDeltaTime);
	virtual void render();
};



