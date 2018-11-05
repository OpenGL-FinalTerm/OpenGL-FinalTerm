#pragma once
#include <GL/freeglut.h> 

class Box {
private:
	float x;
	float y;
	float z;

	float size;


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

	void drawBox(float size, float R, float G, float B)
	{
		glPushMatrix();
		glColor3f(R / 255, G / 255, B / 255);
		glTranslatef(x, y, z);
		glutSolidCube(size);
		glPopMatrix();
	}

	float returnBoxCenterX() {
		return x;
	}
	
	float returnBoxCenterY() {
		return y;
	}

	float returnBoxCenterZ() {
		return z;
	}
};