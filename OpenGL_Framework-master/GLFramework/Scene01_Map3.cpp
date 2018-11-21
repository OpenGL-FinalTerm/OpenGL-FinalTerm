#include "stdafx.h"
#include "Scene01_Map3.h"
#include "GLFramework.h"

S01Map3::S01Map3()
{
}

S01Map3::~S01Map3()
{
}

void S01Map3::init()
{
}

void S01Map3::exit()
{
}

void S01Map3::reset()
{
}

void S01Map3::render()
{
}

void S01Map3::reshape(int w, int h)
{
}

void S01Map3::keyboard(int key, bool pressed, int x, int y, bool special)
{
}

void S01Map3::mouse(int button, bool pressed, int x, int y)
{
}

void S01Map3::motion(bool pressed, int x, int y)
{
	m_Camera.rotate(x, y);
}

void S01Map3::update(float fDeltaTime)
{
}
