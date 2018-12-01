#pragma once
#include "stdafx.h"

struct tmp {
	float x;
	float y;
	float z;

	float xRate;
	float yRate;
	float zRate;

	int jumpCount = 0;
};





float returnMainX();
float returnMainY();
float returnMainZ();