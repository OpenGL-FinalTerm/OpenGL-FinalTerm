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
}

void Light::LightOn(bool LightSwitch, int i)
{
	if (LightSwitch == true) {
		if (i == 0) {
			glEnable(GL_LIGHTING);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
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
			glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
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
			glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLight);
			glLightfv(GL_LIGHT3, GL_SPECULAR, specu);
			glLightfv(GL_LIGHT3, GL_POSITION, pos);

			glEnable(GL_COLOR_MATERIAL);

			glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
			// 이후에 나오는 모든 재질은 밝게 빛나는 완전 전반사 반사율을 갖는다.
			//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specu);
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
}