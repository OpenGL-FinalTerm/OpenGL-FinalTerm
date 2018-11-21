#include "stdafx.h"
#include "Scene01_Map1.h"
#include "GLFramework.h"

S01Map1::S01Map1()
{
}

S01Map1::~S01Map1()
{
}

void S01Map1::init()
{
}

void S01Map1::exit()
{
}

void S01Map1::reset()
{
}

void S01Map1::render()
{
}

void S01Map1::reshape(int w, int h)
{
}

void S01Map1::keyboard(int key, bool pressed, int x, int y, bool special)
{
}

void S01Map1::mouse(int button, bool pressed, int x, int y)
{
}

void S01Map1::motion(bool pressed, int x, int y)
{
	m_Camera.rotate(x, y);
}

void S01Map1::update(float fDeltaTime)
{
}
