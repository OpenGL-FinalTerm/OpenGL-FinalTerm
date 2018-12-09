#include "Light.h"

Light::Light()
{
}

Light::~Light()
{
}

void Light::DefaultLightPosSetting(float inx, float iny, float inz, int color)
{
	x = inx;
	y = iny;
	z = inz;
	colorType = color;

	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}

void Light::LightOn(bool LightSwitch, int i)
{
	if (LightSwitch == true) {
		if (i == 0) {
			glEnable(GL_LIGHTING);
			glLightfv(GL_LIGHT0, GL_POSITION, pos);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
			glLightfv(GL_LIGHT0, GL_SPECULAR, specu);
			glLightfv(GL_LIGHT0, GL_POSITION, pos);

			glEnable(GL_COLOR_MATERIAL);

			glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
			// 이후에 나오는 모든 재질은 밝게 빛나는 완전 전반사 반사율을 갖는다.
			//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specu);
			glMateriali(GL_FRONT, GL_SHININESS, 64);

			glEnable(GL_LIGHT0);

		}

		else if (i == 1) {
			glEnable(GL_LIGHTING);
			glLightfv(GL_LIGHT1, GL_POSITION, pos);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
			glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
			glLightfv(GL_LIGHT1, GL_SPECULAR, specu);
			glLightfv(GL_LIGHT1, GL_POSITION, pos);

			glEnable(GL_COLOR_MATERIAL);

			glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
			// 이후에 나오는 모든 재질은 밝게 빛나는 완전 전반사 반사율을 갖는다.
			//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specu);
			glMateriali(GL_FRONT, GL_SHININESS, 64);
			glEnable(GL_LIGHT1);
		}

		else if (i == 2) {
			glEnable(GL_LIGHTING);
			glLightfv(GL_LIGHT2, GL_POSITION, pos);
			glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
			glLightfv(GL_LIGHT2, GL_SPECULAR, specu);
			glLightfv(GL_LIGHT2, GL_POSITION, pos);

			glEnable(GL_COLOR_MATERIAL);

			glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
			// 이후에 나오는 모든 재질은 밝게 빛나는 완전 전반사 반사율을 갖는다.
			//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specu);
			glMateriali(GL_FRONT, GL_SHININESS, 64);
			glEnable(GL_LIGHT2);
		}

		else if (i == 3) {
			glEnable(GL_LIGHTING);
			glLightfv(GL_LIGHT3, GL_POSITION, pos);
			glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLight);
			glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLight);
			glLightfv(GL_LIGHT3, GL_SPECULAR, specu);
			glLightfv(GL_LIGHT3, GL_POSITION, pos);

			glEnable(GL_COLOR_MATERIAL);

			glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
			// 이후에 나오는 모든 재질은 밝게 빛나는 완전 전반사 반사율을 갖는다.
			//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specu);\
			glMateriali(GL_FRONT, GL_SHININESS, 64);
			glEnable(GL_LIGHT3);
		}
	}

	else {
		if (i == 0)
			glDisable(GL_LIGHT0);
		else if (i == 1)
			glDisable(GL_LIGHT1);
		else if (i == 2)
			glDisable(GL_LIGHT2);
		else if (i == 3)
			glDisable(GL_LIGHT3);
	}
}

void Light::moveLight(float inx, float iny, float inz)
{
	x = inx;
	y = iny;
	z = inz;

	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}

void Light::settingAmbient(float first, float second, float third, float fourth)
{
	ambientLight[0] = first;
	ambientLight[1] = second;
	ambientLight[2] = third;
	ambientLight[3] = fourth;
}

void Light::settingDiffuse(float first, float second, float third, float fourth)
{
	diffuseLight[0] = first;
	diffuseLight[1] = second;
	diffuseLight[2] = third;
	diffuseLight[3] = fourth;
}

void Light::settingGray(float first, float second, float third, float fourth)
{
	gray[0] = first;
	gray[1] = second;
	gray[2] = third;
	gray[3] = fourth;
}
	
void Light::settingSpecu(float first, float second, float third, float fourth)
{
	specu[0] = first;
	specu[1] = second;
	specu[2] = third;
	specu[3] = fourth;
}

void Light::settingPos(float inx, float iny, float inz)
{
	
	x = inx;
	y = iny;
	z = inz;

	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}

void Light::drawRedColunm()
{
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT7, GL_POSITION, pos);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT7, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT7, GL_SPECULAR, specu);
	glLightfv(GL_LIGHT7, GL_POSITION, pos);

	glEnable(GL_COLOR_MATERIAL);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	// 이후에 나오는 모든 재질은 밝게 빛나는 완전 전반사 반사율을 갖는다.
	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specu);
	glMateriali(GL_FRONT, GL_SHININESS, 64);

	glEnable(GL_LIGHT7);
	
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(90, 1, 0, 0);
	glColor3f(1.f, 0.f, 0.f);
	glutSolidCylinder(3, 40, 40, 40);
	glPopMatrix();
}

void Light::drawLight(bool LightSwitch, int i)
{
	if (LightSwitch == true) {
		if (i == 0) {
			GLfloat tmpSpe[4] = { 0.25f, 0.25f, 0.25f, 1.f };
			glEnable(GL_LIGHTING);
			glLightfv(GL_LIGHT0, GL_POSITION, pos);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
			glLightfv(GL_LIGHT0, GL_SPECULAR, specu);
			glLightfv(GL_LIGHT0, GL_POSITION, pos);

			glEnable(GL_COLOR_MATERIAL);

			glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
			// 이후에 나오는 모든 재질은 밝게 빛나는 완전 전반사 반사율을 갖는다.
			//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
			glMaterialfv(GL_FRONT, GL_SPECULAR, tmpSpe);
			glMateriali(GL_FRONT, GL_SHININESS, 64);

			glEnable(GL_LIGHT0);

		}

		else if (i == 1) {
			GLfloat tmpSpe[4] = { 0.25f, 0.25f, 0.25f, 1.f };
			glEnable(GL_LIGHTING);
			glLightfv(GL_LIGHT1, GL_POSITION, pos);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
			glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
			glLightfv(GL_LIGHT1, GL_SPECULAR, specu);
			glLightfv(GL_LIGHT1, GL_POSITION, pos);

			glEnable(GL_COLOR_MATERIAL);

			glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
			// 이후에 나오는 모든 재질은 밝게 빛나는 완전 전반사 반사율을 갖는다.
			//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
			glMaterialfv(GL_FRONT, GL_SPECULAR, tmpSpe);
			glMateriali(GL_FRONT, GL_SHININESS, 64);
			glEnable(GL_LIGHT1);
		}

		else if (i == 2) {
			GLfloat tmpSpe[4] = { 0.25f, 0.25f, 0.25f, 1.f };
			glEnable(GL_LIGHTING);
			glLightfv(GL_LIGHT2, GL_POSITION, pos);
			glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
			glLightfv(GL_LIGHT2, GL_SPECULAR, specu);
			glLightfv(GL_LIGHT2, GL_POSITION, pos);

			glEnable(GL_COLOR_MATERIAL);

			glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
			// 이후에 나오는 모든 재질은 밝게 빛나는 완전 전반사 반사율을 갖는다.
			//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
			glMaterialfv(GL_FRONT, GL_SPECULAR, tmpSpe);
			glMateriali(GL_FRONT, GL_SHININESS, 64);
			glEnable(GL_LIGHT2);
		}

		else if (i == 3) {
			GLfloat tmpSpe[4] = { 0.25f, 0.25f, 0.25f, 1.f };
			glEnable(GL_LIGHTING);
			glLightfv(GL_LIGHT3, GL_POSITION, pos);
			glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLight);
			glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLight);
			glLightfv(GL_LIGHT3, GL_SPECULAR, specu);
			glLightfv(GL_LIGHT3, GL_POSITION, pos);

			glEnable(GL_COLOR_MATERIAL);

			glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
			// 이후에 나오는 모든 재질은 밝게 빛나는 완전 전반사 반사율을 갖는다.
			//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
			glMaterialfv(GL_FRONT, GL_SPECULAR, tmpSpe);
			glMateriali(GL_FRONT, GL_SHININESS, 64);
			glEnable(GL_LIGHT3);
		}
		else if (i == 4) {
			glEnable(GL_LIGHTING);
			glLightfv(GL_LIGHT4, GL_POSITION, pos);
			glLightfv(GL_LIGHT4, GL_AMBIENT, ambientLight);
			glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuseLight);
			glLightfv(GL_LIGHT4, GL_SPECULAR, specu);
			glLightfv(GL_LIGHT4, GL_POSITION, pos);

			glEnable(GL_COLOR_MATERIAL);

			glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
			// 이후에 나오는 모든 재질은 밝게 빛나는 완전 전반사 반사율을 갖는다.
			//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specu);
			glMateriali(GL_FRONT, GL_SHININESS, 64);
			glEnable(GL_LIGHT4);
		}
		else if (i == 5) {
		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT5, GL_POSITION, pos);
		glLightfv(GL_LIGHT5, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT5, GL_SPECULAR, specu);
		glLightfv(GL_LIGHT5, GL_POSITION, pos);

		glEnable(GL_COLOR_MATERIAL);

		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		// 이후에 나오는 모든 재질은 밝게 빛나는 완전 전반사 반사율을 갖는다.
		//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specu);
		glMateriali(GL_FRONT, GL_SHININESS, 64);
		glEnable(GL_LIGHT5);
		}
		else if (i == 6) {
		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT6, GL_POSITION, pos);
		glLightfv(GL_LIGHT6, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT6, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT6, GL_SPECULAR, specu);
		glLightfv(GL_LIGHT6, GL_POSITION, pos);

		glEnable(GL_COLOR_MATERIAL);

		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		// 이후에 나오는 모든 재질은 밝게 빛나는 완전 전반사 반사율을 갖는다.
		//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specu);
		glMateriali(GL_FRONT, GL_SHININESS, 64);
		glEnable(GL_LIGHT6);
		}
		else if (i == 7) {
		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT7, GL_POSITION, pos);
		glLightfv(GL_LIGHT7, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT7, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT7, GL_SPECULAR, specu);
		glLightfv(GL_LIGHT7, GL_POSITION, pos);

		glEnable(GL_COLOR_MATERIAL);

		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		// 이후에 나오는 모든 재질은 밝게 빛나는 완전 전반사 반사율을 갖는다.
		//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specu);
		glMateriali(GL_FRONT, GL_SHININESS, 64);
		glEnable(GL_LIGHT7);
		}
	}

	else {
		if (i == 0)
			glDisable(GL_LIGHT0);
		else if (i == 1)
			glDisable(GL_LIGHT1);
		else if (i == 2)
			glDisable(GL_LIGHT2);
		else if (i == 3)
			glDisable(GL_LIGHT3);
	}
	glPushMatrix();
	glTranslatef(x, y, z);
	if (colorType == 1)
		glColor3f(1.f, 0.f, 0.f);
	else
		glColor3f(0.f, 0.f, 1.f);

	glutSolidSphere(4, 4, 4);
	glPopMatrix();
}

float Light::returnXpos()
{
	return x;
}

float Light::returnYpos()
{
	return y;
}

float Light::returnZpos()
{
	return z;
}

void Light::moveX(float inX)
{
	x += inX;
	pos[0] = x;
}

void Light::moveY(float inY)
{
	y += inY;
	pos[1] = y;
}

void Light::moveZ(float inZ)
{
	z += inZ;
	pos[2] = z;
}

bool Light::returnPickCheck()
{
	return pick;
}

void Light::pickUp(bool check)
{
	pick = check;
}

void Light::pickSetPos(float inX, float inY, float inZ)
{
	x = inX;
	y = inY;
	z = inZ;

	pos[0] = inX;
	pos[1] = inY;
	pos[2] = inZ;
}

void Light::throwLightUpdate(bool check)
{
	throwLight = check;
}

bool Light::returnThrowCheck()
{
	return throwLight;
}

void Light::insertDestination(float inX, float inY, float inZ)
{
	end[0] = inX;
	end[1] = inY;
	end[2] = inZ;
}

float Light::returnDestinationX()
{
	return end[0];
}

float Light::returnDestinationY()
{
	return end[1];
}

float Light::returnDestinationZ()
{
	return end[2];
}

int Light::returnType()
{
	return colorType;
}