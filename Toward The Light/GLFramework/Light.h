#pragma once
#include <gl/freeglut.h>

class Light {
private:
	float x;
	float y;
	float z;

	int colorType;
	
	GLfloat R;
	GLfloat G;
	GLfloat B;

	GLfloat pos[4] = { 0.f, 0.f, 0.f, 1.0f };
	GLfloat ambientLight[4] = { 0.1f, 0.1f, 0.1f, 0.0f };
	GLfloat diffuseLight[4] = { 0.6f, 0.5f, 0.2f, 1.0f};
	GLfloat specu[4] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat gray[4] = { 0.25f, 0.25f, 0.25f, 0.25f };

public:
	Light();
	~Light();
	virtual void DefaultLightPosSetting(float x, float y, float z, int color);
	virtual void moveLight(float inX, float inY, float inZ);
	virtual void LightOn(bool LightSwitch, int i);
	virtual void settingPos(float inx, float iny, float inz);
	virtual void settingAmbient(float first, float second, float third, float fourth);
	virtual void settingDiffuse(float first, float second, float third, float fourth);
	virtual void settingSpecu(float first, float second, float third, float fourth);
	virtual void settingGray(float first, float second, float third, float fourth);
	
	virtual float returnXpos();
	virtual float returnYpos();
	virtual float returnZpos();

	virtual void moveX(float inX);
	virtual void moveY(float inY);
	virtual void moveZ(float inZ);
	
	virtual void drawLight(bool LightSwitch, int i);
};

enum {
	selectNumber
};