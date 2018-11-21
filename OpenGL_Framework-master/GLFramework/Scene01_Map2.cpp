#include "stdafx.h"
#include "Scene01_Map2.h"
#include "GLFramework.h"

S01Map2::S01Map2()
{
}

S01Map2::~S01Map2()
{
}

void S01Map2::init()
{
}

void S01Map2::exit()
{
}

void S01Map2::reset()
{
}

void S01Map2::render()
{
}

void S01Map2::reshape(int w, int h)
{
}

void S01Map2::keyboard(int key, bool pressed, int x, int y, bool special)
{
}

void S01Map2::mouse(int button, bool pressed, int x, int y)
{
}

void S01Map2::motion(bool pressed, int x, int y)
{
	m_Camera.rotate(x, y);
}

void S01Map2::update(float fDeltaTime)
{
}
