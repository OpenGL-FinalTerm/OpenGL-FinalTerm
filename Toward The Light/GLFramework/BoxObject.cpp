#include "BoxObject.h"

Box::Box()
{
}

Box::~Box()
{
}

void Box::CreateBox(float inx, float iny, float inz)
{
	x = inx;
	y = iny;
	z = inz;
}

void Box::setColor(GLfloat R, GLfloat G, GLfloat B)
{
	colorR = R;
	colorG = G;
	colorB = B;
}

void Box::movingX(float inX)
{
	x += inX;
}

void Box::movingY(float inY)
{
	y += inY;
}

void Box::movingZ(float inZ)
{
	z += inZ;
}

void Box::checkUpdate(int c)
{
	if (c == 1)
		check = true;
	else
		check = false;
}

void Box::addXrate(int adX)
{
	addX += adX;
}

void Box::addYrate(int adY)
{
	addY += adY;
}

void Box::addZrate(int adZ)
{
	addZ += adZ;
}

void Box::clearAdd()
{
	addX = 0;
	addY = 0;
	addZ = 0;
}


void Box::drawBox(float size)
{
	glPushMatrix();
	glColor3f(colorR / 255, colorG / 255, colorB / 255);
	glTranslatef(x, y, z);
	glutSolidCube(size);
	glPopMatrix();
}

void Box::pickUp(bool check)
{
	pick = check;
}

float Box::returnBoxCenterX() {
	return x + addX;
}

float Box::returnBoxCenterY() {
	return y + addY;
}

float Box::returnBoxCenterZ() {
	return z + addZ;
}

bool Box::returnCheck() {
	return check;
}

bool Box::returnPickUp()
{
	return pick;
}