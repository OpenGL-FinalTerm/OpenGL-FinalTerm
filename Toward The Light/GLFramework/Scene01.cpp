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
static int x;
static int y;
static int z;



S01Main::S01Main()
{
}

S01Main::~S01Main()
{
}

void S01Main::init()
{

	m_SoundPlayer.init();
	m_SoundPlayer.selectFolder("Resources\\BGM");

	m_Camera.setDistance(3000.f);
	m_Camera.setPerspective(45.f, 0.125f, 7'000.f);
	m_Camera.setSensitivity(10.f);

	for (int i = 0; i < 20; ++i) {
		objectBox[i].CreateBox();
		objectBox[i].setColor(255, 0, 0);
	}

}

void S01Main::exit()
{
	m_SoundPlayer.exit();
}

void S01Main::reset()
{
	m_SoundPlayer.play();
}

void S01Main::render()
{
	m_Camera.ready();
	

	//맵은 언제와요?
	//외로운 빈공간
	//BGM이랑 바나나만 있으니깐 공포겜이에요
	//조명이 여기 어딘가에 들어가야 할거에요
	//근데 맵....은.....
	//어따 그리지
	for (int i = 0; i < 5; ++i)
		objectBox[i].drawBox(50);
	glPushMatrix();
	glTranslatef(x, y, z);
	banana_draw(0, 0, 0, 10, IDLE, banana.rot.degree);
	glPopMatrix();

}

void S01Main::reshape(int w, int h)
{

}

void S01Main::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
	{
		switch (key)
		{
		case 'w':
			z -= 20;
			break;

		case 'a':
			x -= 20;
			break;

		case 's':
			z += 20;
			break;

		case 'd':
			x += 20;
			break;
		}
	}
}

void S01Main::mouse(int button, bool pressed, int x, int y)
{
}

void S01Main::motion(bool pressed, int x, int y)
{
	m_Camera.rotate(x, y, pressed);
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