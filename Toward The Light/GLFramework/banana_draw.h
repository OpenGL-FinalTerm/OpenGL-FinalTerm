
#pragma once
//#include <GL/freeglut.h> 
#include "stdafx.h"

#define IDLE 0
#define RUN 1
#define JUMP 2
#define DOWN_JUMP 3

typedef struct Color
{
	int R;
	int G;
	int B;
};
typedef struct Translate_pos {
	float x;
	float y;
	float z;
	float degree;
};


typedef struct BoOL
{
	int b_x;
	int b_y;
	int b_z;
};

typedef struct QUAD
{
	Color cl[50];//색상
	Translate_pos pos[50];//총 정점 수 74 / 2
	Translate_pos move;
	Translate_pos scale;
	Translate_pos rot;

	int size;
	int select;
	int height;
	int slice;
	int stacks;
	BOOL b;
	BOOL any;

};

//머리 3


void Swap(float a, float b);
void banana_save_index();
void banana_index_change(float size); 
void banana_draw(int pivot_x, int pivot_y, int pivot_z, float size, int state, float sub_degree , float rotate);
void banana_head(int pivot_x, int pivot_y, int pivot_z, int size, float degree, int state, float rotate);
void banana_body(int pivot_x, int pivot_y, int pivot_z, int size, float rot_degree, int state, float rotate);

