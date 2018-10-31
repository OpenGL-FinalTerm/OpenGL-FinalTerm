#pragma once
#include "LinearMath.h"

class Picking
{
	static double		m_pdPickedPoint[3];
	static bool			m_bPicked;

public:

	static void get(int x, int y);
	static void draw(int nPointSize);
	static Vector3 toVector3();
};

