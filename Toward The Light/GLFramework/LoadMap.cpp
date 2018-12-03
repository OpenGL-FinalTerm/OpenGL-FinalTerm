#include "LoadMap.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>


int LoadMap(Box objectBox[], tmp &tmpRect, int stage)
{
	int cnt;
	int tmp;
	string fileName;

	if (stage == 1)
		fileName = "StageData\\stage_1.txt";
	else
		fileName = "StageData\\stage_2.txt";
	
	ifstream in(fileName);

	in >> cnt;
	
	int tmpX;
	int tmpY;
	int tmpZ;

	in >> tmpX;
	in >> tmpY;
	in >> tmpZ;

	tmpRect.x = -50 + (tmpX * 20);
	tmpRect.y = 10 + (tmpY * 20);
	tmpRect.z = -60 + (tmpZ * 20);


	int **ptr;
	ptr = (int**)malloc(sizeof(int *) * 6);

	for (int i = 0; i < 6; ++i)
		*(ptr + i) = (int *)malloc(sizeof(int) * 7);


	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 6; ++j) {
			in >> tmp;
			ptr[j][i] = tmp;
		}
	}
	
	int insertCount = 0;

	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 6; ++j) {
			for (int k = 0; k < ptr[j][i]; ++k) {
				objectBox[insertCount].CreateBox(-50 + (j * 20), 10 + (k * 20), -60 + (i * 20));
				objectBox[insertCount++].setColor(rand() % 255, rand() % 255, rand() % 255);
			}
		}
	}

	return cnt;
}

int LoadLight(Light mapLight[], int i)
{
	string fileName;
	int cnt;

	int tmpX;
	int tmpZ;
	int colorType;

	float diffuse[4];
	float specu[4];

	if (i == 1)
		fileName = "StageData\\LightPos\\stage_1-light.txt";
	else
		fileName = "StageData\\LightPos\\stage_2-light.txt";

	ifstream in(fileName);

	in >> cnt;
	
	for (int k = 0; k < cnt; ++k) {
		in >> tmpX;
		in >> tmpZ;
		in >> colorType;

		in >> diffuse[0] >> diffuse[1] >> diffuse[2] >> diffuse[3];
		in >> specu[0] >> specu[1] >> specu[2] >> specu[3];

		int lx;
		int ly;
		int lz;

		lx = -50 + (tmpX * 20);
		ly = 120;
		lz = -60 + (tmpZ * 20);

		mapLight[k].DefaultLightPosSetting(lx, ly, lz, colorType);
		mapLight[k].settingDiffuse((float)diffuse[0], (float)diffuse[1], (float)diffuse[2], (float)diffuse[3]);
		mapLight[k].settingSpecu((float)specu[0], (float)specu[1], (float)specu[2], (float)specu[3]);
		mapLight[k].drawLight(TRUE, k);
	}


	//mapLight[0].DefaultLightPosSetting(30, 5, 60, 1);
	//mapLight[1].DefaultLightPosSetting(-30, 45, 20, 1);

	//mapLight[2].DefaultLightPosSetting(30, 5, 0, 0);
	//mapLight[3].DefaultLightPosSetting(-30, 5, -40, 0);
	return cnt;
}