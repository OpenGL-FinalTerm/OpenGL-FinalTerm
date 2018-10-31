#pragma once
#include "Transformations.h"

class Camera
{
public:
	Camera();
	~Camera();

	void init();

	void setTarget(const Vector3& v3Target);
	void setUp(const Vector3& v3Up);

	void setDistance(float fDistance);
	void setSensitivity(float fSensitivity);
	void setPerspective(float fFovy, float fNear, float fFar);
	void updateEye();

	Vector3 getTarget();
	Vector3 getUp();
	Vector3 getEye();
	Vector3 getLook();
	Vector3 getRight();

	float getDistance();
	float getFovy();
	float getNear();
	float getFar();
	float getSensitivity();
	void resetRotation();

	void rotate(float angle, const Vector3& axis);													// rotation about an AXIS with a given angle
	void rotate(int x, int y, bool blDrag = true, bool bInverseX = false, bool bInverseY = false);	// Rotation based on Mouse movement
	void ready(int nCursorType = GLUT_CURSOR_LEFT_ARROW);

private:
	QuaternionRotation		m_QuaternionRotation;

	Vector3					m_v3PrevUp;
	Vector3					m_v3PrevEye;

	Vector3					m_v3Target;
	Vector3					m_v3Up;
	Vector3					m_v3Eye;

	Vector2					m_v2MouseNewPos{ 0, 0 };
	Vector2					m_v2MouseOldPos{ 0, 0 };

	float					m_fDistance;
	float					m_fFovy;
	float					m_fNear;
	float					m_fFar;
	float					m_fSensitivity{ 0.2f };

	int						m_nCursorType;

	bool					m_blMouseDrag{ false };

	//bool					ms_hide{ false };
};
