#pragma once
#include "Transformations.h"

class NormalObject
{
public:
	Vector3				m_v3Position;
	QuaternionRotation	m_qrRotation;
	Vector3				m_v3Scale;

	Vector3				m_v3DefaultColor;

	std::string			m_sType;
	float				m_fModelSize;
	bool				m_wireType;


public:

	NormalObject();
	~NormalObject();

	void setModel(std::string m_Shape, float size, bool wire);

	void setColor(const Vector3& v3DefaultColor);
	void setPosition(float x, float y, float z);
	void setPosition(const Vector3& v3Position);

	virtual void move(const Vector3& v3Direction, float fDistance);
	virtual void move(float fDistanceX, float fDistanceY, float fDistanceZ);

	virtual void scale(const Vector3& v3Axis, float fRatio);
	virtual void scale(float fRatioX, float fRatioY, float fRatioZ);

	virtual void rotate(float fRadAngle, const Vector3& v3Axis);

	virtual void update(float fDeltaTime);
	virtual void render();
};



