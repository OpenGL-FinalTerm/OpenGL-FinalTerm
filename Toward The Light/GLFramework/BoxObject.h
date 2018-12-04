#pragma once
#include <gl/freeglut.h>

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

	float colorR;
	float colorG;
	float colorB;

	bool pick = false;


public:

	Box();
	virtual ~Box();
	
	virtual void CreateBox(float x, float y, float z);
	virtual void setColor(GLfloat R, GLfloat G, GLfloat B);
	virtual void movingX(int inX);
	virtual void movingY(int inY);
	virtual void movingZ(int inZ);
	virtual void checkUpdate(int c);
	virtual void addXrate(int adX);
	virtual void addYrate(int adY);
	virtual void addZrate(int adZ);
	virtual void clearAdd();
	virtual void drawBox(float size);
	virtual void pickUp(bool check);

	virtual bool returnPickUp();
	virtual bool returnCheck();

	virtual float returnBoxCenterX();
	virtual float returnBoxCenterY();
	virtual float returnBoxCenterZ();

};


