#include "stdafx.h"
#include "Scene01.h"
#include "GLFramework.h"
#include "banana_draw.h"

typedef struct Shape
{
	Color cl;//색상
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

//은면제거
BOOL depth;
int depth_count;
//컬링
BOOL culling;
int culling_count;
//쉐이딩
BOOL shade;
int shade_count;


Shape banana;

S01Main::S01Main()
{
}

S01Main::~S01Main()
{
}

void S01Main::init()
{
	m_Camera.setDistance(3000.f);
	m_Camera.setPerspective(45.f, 0.125f, 7'000.f);
	m_Camera.setSensitivity(10.f);
}

void S01Main::exit()
{
}

void S01Main::reset()
{

}

void S01Main::render()
{
	m_Camera.ready();
	
	banana_draw(0, 0, 0, 30, IDLE, banana.rot.degree);

}

void S01Main::reshape(int w, int h)
{

}

void S01Main::keyboard(int key, bool pressed, int x, int y, bool special)
{
}

void S01Main::mouse(int button, bool pressed, int x, int y)
{
}

void S01Main::motion(bool pressed, int x, int y)
{
	if (s)
		m_Camera.rotate(x, 0.f, pressed);
	else
		m_Camera.rotate(0.f, y, pressed);
}

int switch_sign = -1;
int Time_count;

void S01Main::update(float fDeltaTime)
{
	Time_count++;
	if (Time_count % 20 == 0)
	{
		switch_sign *= -1;
	}
	banana.rot.degree += 0.1f * switch_sign;
}