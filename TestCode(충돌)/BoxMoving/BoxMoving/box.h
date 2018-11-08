#pragma once
#include <GL/freeglut.h> 

class Box {
private:
	float x;
	float y;
	float z;

	float addX;
	float addY;
	float addZ;

	float size;
	bool check = false;


public:
	
	void movingX(int inX)
	{
		x += inX;
	}

	void movingY(int inY)
	{
		y += inY;
	}

	void movingZ(int inZ)
	{
		z += inZ;
	}

	void checkUpdate(int c)
	{
		if (c == 1)
			check = true;
		else
			check = false;
	}

	void addXrate(int adX)
	{
		addX += adX;
	}

	void addYrate(int adY)
	{
		addY += adY;
	}

	void addZrate(int adZ)
	{
		addZ += adZ;
	}

	void clearAdd()
	{
		addX = 0;
		addY = 0;
		addZ = 0;
	}


	void drawBox(float size, float R, float G, float B)
	{
		glPushMatrix();
		glColor3f(R / 255, G / 255, B / 255);
		glTranslatef(x, y, z);
		glutSolidCube(size);
		glPopMatrix();
	}

	float returnBoxCenterX() {
		return x + addX;
	}
	
	float returnBoxCenterY() {
		return y + addY;
	}

	float returnBoxCenterZ() {
		return z + addZ;
	}

	bool returnCheck() {
		return check;
	}
};