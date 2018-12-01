#pragma once
#include "stdafx.h"
#include "banana_draw.h"

typedef struct Shape
{
	Color cl;//»ö»ó
	Translate_pos sp_pos[36];
	Translate_pos pos;
	Translate_pos move;
	Translate_pos scale;
	Translate_pos rot;

	int size;
	int select;
	int height;
	int slice;
	int stacks;
	BoOL b;
	BOOL any;

};


