#include "stdafx.h"
#include "Scene04_Ending.h"
#include "GLFramework.h"
#include "banana_draw.h"
#include "Character.h"

static int rotate;
S04End::S04End()
{
}

S04End::~S04End()
{
}

void S04End::init()
{
	m_Camera_end.init();
	m_Camera_end.setDistance(200.f);
	m_Camera_end.setPerspective(30.f, 0.125f, 3500.f);
	m_Camera_end.setSensitivity(1.f);
	rotate = 0;
}

void S04End::exit()
{
}

void S04End::reset()
{
}


void S04End::render()
{
	m_Camera_end.ready();
	m_Camera_end.rotate(rotate++, 0, true);

	glPushMatrix();
	banana_draw(tmpRect.x, tmpRect.y + 5, tmpRect.z, 0.5, IDLE, banana.rot.degree, 0);
	glPopMatrix();

	glColor3f(1.f, 1.f, 1.f);
	print("Banana is Dead", 0, 40, 0);
}

void S04End::reshape(int w, int h)
{

}

void S04End::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
		switch (key)
		{
		case 'r': m_Framework->toScene("Main"); break;
		case 'R': m_Framework->toScene("Main"); break;
		}

}

void S04End::mouse(int button, bool pressed, int x, int y)
{
}

void S04End::motion(bool pressed, int x, int y)
{
}

void S04End::update(float fDeltaTime)
{
	Time_count++;
	if (Time_count % 20 == 0)
	{
		switch_sign *= -1;
	}
	banana.rot.degree += 0.1f * switch_sign;
}
