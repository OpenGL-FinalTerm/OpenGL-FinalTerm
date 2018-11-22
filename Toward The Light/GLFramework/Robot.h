#pragma once
#include "Transformations.h"

class Robot
{
public:
	Robot();
	~Robot();

	float				m_spin;

	void setPosition(float x, float y, float z);
	virtual void move(float fDistanceX, float fDistanceY, float fDistanceZ);
	virtual void update(float fDeltaTime);
	virtual void render();

	void setDir(int set);
	int spin;
	bool dir;

	int robotX, robotY, robotZ;
	int rotateDir;

	bool jump;
	bool jumpdir;
};