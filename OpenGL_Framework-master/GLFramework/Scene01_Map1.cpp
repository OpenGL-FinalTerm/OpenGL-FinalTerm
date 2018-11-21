#include "stdafx.h"
#include "Scene01_Map1.h"
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


S01Map1::S01Map1()
{
}

S01Map1::~S01Map1()
{
}

void S01Map1::init()
{
	m_Camera.setDistance(-500.f);
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
	glPushMatrix();//-------------그리기 입력--------------------------
	{
		glPushMatrix();
		{
			if (shade) {
				glShadeModel(GL_SMOOTH);
			}
			else {
				glShadeModel(GL_FLAT);
			}
			//상자 그리기
			//glScaled(100, 100, 100);
			banana_draw(0, 0, 0, 5, IDLE, banana.rot.degree);

		}
		glPopMatrix();
	}
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
	m_Camera.rotate(x, 0);
}

int switch_sign = -1;
int Time_count;

void S01Map1::update(float fDeltaTime)
{
	Time_count++;
	if (Time_count % 20 == 0)
	{
		switch_sign *= -1;
	}
	banana.rot.degree += 0.1f * switch_sign;
}