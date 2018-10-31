#pragma once
#include "LinearMath.h"

class QuaternionRotation
{
public:

	QuaternionRotation();
	~QuaternionRotation();

	Matrix4x4 getRotationMatrix();
	Vector3 rotatePoint(const Vector3& v3Point);
	void rotate(float fRadAngle, Vector3 v3Axis);
	void resetQuaternion();

private:

	Vector4	m_RotationQuaternion;
	Matrix4x4 m_RotationMatrix;
};