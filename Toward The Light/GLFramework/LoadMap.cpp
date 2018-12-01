#include "LoadMap.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

void LoadMap(Box objectBox[], int stage)
{
	int cnt;
	int tmp;
	string fileName;

	if (stage == 1)
		fileName = "stage_1.txt";
	else
		fileName = "stage_2.txt";
	
	ifstream in(fileName);

	in >> cnt;

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
}