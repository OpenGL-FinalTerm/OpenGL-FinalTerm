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
	m_Camera.setDistance(-300.f);
	m_Camera.setPerspective(30.f, 0.125f, 7'000.f);
	m_Camera.setSensitivity(10.f);
}

void S01Map1::exit()
{
}

void S01Map1::reset()
{
}

void S01Map1::render()
{
	m_Camera.ready();
	glColor3f(1.0f, 1.0f, 0.0f);
	glutWireCube(20);
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
