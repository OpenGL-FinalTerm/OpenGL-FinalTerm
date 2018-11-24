#include "stdafx.h"
#include "Scene01.h"
#include "GLFramework.h"
#include "banana_draw.h"
#define whatBox 20
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

	m_SoundPlayer.init();
	m_SoundPlayer.selectFolder("Resources\\BGM");

	m_Camera.setDistance(300.f);
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
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-500, -10, -500);
	glVertex3f(-500, -10, 500);
	glVertex3f(500, -10, 500);
	glVertex3f(500, -10, -500);
	glEnd();

	//맵은 언제와요?
	//외로운 빈공간
	//BGM이랑 바나나만 있으니깐 공포겜이에요
	//조명이 여기 어딘가에 들어가야 할거에요
	//근데 맵....은.....
	//어따 그리지
	for (int i = 0; i < 20; ++i)
		objectBox[i].drawBox(20);
	glPushMatrix();
	glTranslatef(mainCharacter.returnBoxCenterX(), mainCharacter.returnBoxCenterY(), mainCharacter.returnBoxCenterZ());
	banana_draw(0, 0, 0, 1, IDLE, banana.rot.degree);
	glPopMatrix();

}

void S01Main::reshape(int w, int h)
{

}

void S01Main::keyboard(int key, bool pressed, int x, int y, bool special)
{
	int cycle = 0;
	int count = 0;
	int i = 0;
	BOOL check = FALSE;
	if (pressed)
	{
		switch (key)
		{
		case 'w':
			mainCharacter.movingZ(-20);
		
			//while (check == FALSE) {

			//	if (mainCharacter.returnBoxCenterZ() - 15 <= objectBox[i].returnBoxCenterZ() + 12.5 && !(mainCharacter.returnBoxCenterZ() + 15 <= objectBox[i].returnBoxCenterZ() - 12.5)) {
			//		if (objectBox[i].returnBoxCenterX() - 12.5 < mainCharacter.returnBoxCenterX() + 15 && objectBox[i].returnBoxCenterX() + 12.5 > mainCharacter.returnBoxCenterX() - 15 && objectBox[i].returnBoxCenterY() + 12.5 > mainCharacter.returnBoxCenterY() - 15 && objectBox[i].returnBoxCenterY() - 12.5 < mainCharacter.returnBoxCenterY() + 15) {
			//			if (objectBox[i].returnCheck() == 0) {
			//				mainCharacter.addZrate(-29);
			//				objectBox[i].movingZ(-1);
			//				objectBox[i].checkUpdate(1);
			//			}
			//		}
			//	}

			//	if (i == whatBox - 1) {
			//		cycle++;
			//		for (int j = 0; j < whatBox; ++j) {
			//			if (objectBox[j].returnCheck()) {
			//				count++;
			//			}
			//		}
			//		if (count == whatBox || count == 0 || cycle == whatBox)
			//			check = TRUE;
			//		else
			//			i = 0;

			//		count = 0;
			//	}
			//	else {
			//		i++;

			//	}

			//}

			//for (int k = 0; k < whatBox; ++k)
			//	objectBox[k].checkUpdate(0);
			//check = FALSE;
			//cycle = 0;
			//mainCharacter.clearAdd();

			break;

		case 'a':
			mainCharacter.movingX(-20);
			break;

		case 's':
			mainCharacter.movingZ(20);
			break;

		case 'd':
			mainCharacter.movingX(20);
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