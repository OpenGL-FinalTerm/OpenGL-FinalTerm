#include "stdafx.h"
#include "Scene01.h"
#include "GLFramework.h"
#include "banana_draw.h"
#define whatBox 65
#define LightCount 4
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

struct tmp {
	float x;
	float y;
	float z;

	float xRate;
	float yRate;
	float zRate;
};

static tmp tmpRect;

float returnMainX()
{
	return tmpRect.x + tmpRect.xRate;
}

float returnMainY()
{
	return tmpRect.y + tmpRect.yRate;
}

float returnMainZ()
{
	return tmpRect.z + tmpRect.zRate;
}

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

	//for (int i = 0; i < 20; ++i) {
	//	objectBox[i].CreateBox(rand() % 120 - 60, 10, rand() % 140 - 70);
	//	objectBox[i].setColor(rand() % 255, rand() % 255, rand() % 255);
	//}
	tmpRect.x = -10;
	tmpRect.y = 10;
	tmpRect.z = 60;
	LightSetting();
	DefaultBoxPosSetting();
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
	glPushMatrix();
	m_Camera.ready();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-60, 0, -70);
	glVertex3f(-60, 0, 70);
	glVertex3f(60, 0, 70);
	glVertex3f(60, 0, -70);
	glEnd();

	//맵은 언제와요?
	//외로운 빈공간
	//BGM이랑 바나나만 있으니깐 공포겜이에요
	//조명이 여기 어딘가에 들어가야 할거에요
	//근데 맵....은.....
	//어따 그리지
	for (int i = 0; i < 65; ++i)
		objectBox[i].drawBox(20);

	for (int i = 0; i < LightCount; ++i)
		mapLight[i].drawLight();
	
	glPushMatrix();
	glTranslatef(tmpRect.x, tmpRect.y, tmpRect.z);
	glColor3f(1.f, 0.4f, 0.2f);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(mainCharacter.returnBoxCenterX(), mainCharacter.returnBoxCenterY(), mainCharacter.returnBoxCenterZ());
	banana_draw(0, 0, 0, 1, IDLE, banana.rot.degree);
	glPopMatrix();
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
			mainCharacter.movingZ(-1);
			tmpRect.z -= 1;
		
			while (check == FALSE) {

				if (returnMainZ() - 5 <= objectBox[i].returnBoxCenterZ() + 10 && !(returnMainZ() + 5 <= objectBox[i].returnBoxCenterZ() - 10)) {
					if (objectBox[i].returnBoxCenterX() - 10 < returnMainX() + 5 && objectBox[i].returnBoxCenterX() + 10 > returnMainX() - 5 && objectBox[i].returnBoxCenterY() + 10 > returnMainY() - 5 && objectBox[i].returnBoxCenterY() - 10 < returnMainY() + 5) {
						if (objectBox[i].returnCheck() == 0) {
							tmpRect.zRate -= 20;
							objectBox[i].movingZ(-1);
							objectBox[i].checkUpdate(1);
						}
					}
				}

				if (i == whatBox - 1) {
					cycle++;
					for (int j = 0; j < whatBox; ++j) {
						if (objectBox[j].returnCheck()) {
							count++;
						}
					}
					if (count == whatBox || count == 0 || cycle == whatBox)
						check = TRUE;
					else
						i = 0;

					count = 0;
				}
				else {
					i++;

				}

			}

			for (int k = 0; k < whatBox; ++k)
				objectBox[k].checkUpdate(0);
			check = FALSE;
			cycle = 0;
			tmpRect.xRate = 0;
			tmpRect.yRate = 0;
			tmpRect.zRate = 0;

			break;

		case 'a':
			tmpRect.x -= 1;
			mainCharacter.movingX(-1);

			while (check == FALSE) {

				if (returnMainX() - 5 <= objectBox[i].returnBoxCenterX() + 10 && !(returnMainX() + 5 <= objectBox[i].returnBoxCenterX() - 10)) {
					if (objectBox[i].returnBoxCenterZ() - 10 < returnMainZ() + 5 && objectBox[i].returnBoxCenterZ() + 10 > returnMainZ() - 5 && objectBox[i].returnBoxCenterY() + 10 > returnMainY() - 5 && objectBox[i].returnBoxCenterY() - 10 < returnMainY() + 5) {
						if (objectBox[i].returnCheck() == 0) {
							tmpRect.xRate -= 20;
							objectBox[i].movingX(-1);
							objectBox[i].checkUpdate(1);
						}
					}
				}

				if (i == whatBox - 1) {
					cycle++;
					for (int j = 0; j < whatBox; ++j) {
						if (objectBox[j].returnCheck()) {
							count++;
						}
					}
					if (count == whatBox || count == 0 || cycle == whatBox)
						check = TRUE;
					else
						i = 0;

					count = 0;
				}
				else {
					i++;

				}

			}

			for (int k = 0; k < whatBox; ++k)
				objectBox[k].checkUpdate(0);
			check = FALSE;
			cycle = 0;
			tmpRect.xRate = 0;
			tmpRect.yRate = 0;
			tmpRect.zRate = 0;

			break;

		case 's':
			tmpRect.z += 1;
			mainCharacter.movingZ(1);

			while (check == FALSE) {

				if (returnMainZ() - 5 <= objectBox[i].returnBoxCenterZ() + 10 && !(returnMainZ() + 5 <= objectBox[i].returnBoxCenterZ() - 10)) {
					if (objectBox[i].returnBoxCenterX() - 10 < returnMainX() + 5 && objectBox[i].returnBoxCenterX() + 10 > returnMainX() - 5 && objectBox[i].returnBoxCenterY() + 10 > returnMainY() - 5 && objectBox[i].returnBoxCenterY() - 10 < returnMainY() + 5) {
						if (objectBox[i].returnCheck() == 0) {
							tmpRect.zRate += 20;
							objectBox[i].movingZ(1);
							objectBox[i].checkUpdate(1);
						}
					}
				}

				if (i == whatBox - 1) {
					cycle++;
					for (int j = 0; j < whatBox; ++j) {
						if (objectBox[j].returnCheck()) {
							count++;
						}
					}
					if (count == whatBox || count == 0 || cycle == whatBox)
						check = TRUE;
					else
						i = 0;

					count = 0;
				}
				else {
					i++;

				}

			}

			for (int k = 0; k < whatBox; ++k)
				objectBox[k].checkUpdate(0);
			check = FALSE;
			cycle = 0;
			tmpRect.xRate = 0;
			tmpRect.yRate = 0;
			tmpRect.zRate = 0;
			break;

		case 'd':
			tmpRect.x += 1;
			mainCharacter.movingX(1);

			while (check == FALSE) {

				if (returnMainX() - 5 <= objectBox[i].returnBoxCenterX() + 10 && !(returnMainX() + 5 <= objectBox[i].returnBoxCenterX() - 10)) {
					if (objectBox[i].returnBoxCenterZ() - 10 < returnMainZ() + 5 && objectBox[i].returnBoxCenterZ() + 10 > returnMainZ() - 5 && objectBox[i].returnBoxCenterY() + 10 > returnMainY() - 5 && objectBox[i].returnBoxCenterY() - 10 < returnMainY() + 5) {
						if (objectBox[i].returnCheck() == 0) {
							tmpRect.xRate += 20;
							objectBox[i].movingX(1);
							objectBox[i].checkUpdate(1);
						}
					}
				}

				if (i == whatBox - 1) {
					cycle++;
					for (int j = 0; j < whatBox; ++j) {
						if (objectBox[j].returnCheck()) {
							count++;
						}
					}
					if (count == whatBox || count == 0 || cycle == whatBox)
						check = TRUE;
					else
						i = 0;

					count = 0;
				}
				else {
					i++;

				}

			}

			for (int k = 0; k < whatBox; ++k)
				objectBox[k].checkUpdate(0);
			check = FALSE;
			cycle = 0;
			tmpRect.xRate = 0;
			tmpRect.yRate = 0;
			tmpRect.zRate = 0;
			break;

		case 'p':
			for (int i = 0; i < 4; ++i)
				mapLight[i].LightOn(true, i);
			break;

		case 'P':
			for (int i = 0; i < 4; ++i)
				mapLight[i].LightOn(false, i);
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

void S01Main::DefaultBoxPosSetting()
{
	//1행
	objectBox[0].CreateBox(-50, 10, -60);
	objectBox[0].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[1].CreateBox(-30, 10, -60);
	objectBox[1].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[2].CreateBox(-10, 10, -60);
	objectBox[2].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[3].CreateBox(10, 10, -60);
	objectBox[3].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[4].CreateBox(30, 10, -60);
	objectBox[4].setColor(rand() % 255, rand() % 255, rand() % 255);

	//2행
	objectBox[5].CreateBox(-50, 10, -40);
	objectBox[5].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[6].CreateBox(-50, 30, -40);
	objectBox[6].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[7].CreateBox(-10, 10, -40);
	objectBox[7].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[8].CreateBox(-10, 30, -40);
	objectBox[8].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[9].CreateBox(10, 10, -40);
	objectBox[9].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[10].CreateBox(10, 30, -40);
	objectBox[10].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[11].CreateBox(30, 10, -40);
	objectBox[11].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[12].CreateBox(50, 10, -40);
	objectBox[12].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[13].CreateBox(50, 30, -40);
	objectBox[13].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[14].CreateBox(50, 50, -40);
	objectBox[14].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[15].CreateBox(50, 70, -40);
	objectBox[15].setColor(rand() % 255, rand() % 255, rand() % 255);

	//3행
	objectBox[16].CreateBox(-50, 10, -20);
	objectBox[16].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[17].CreateBox(-30, 10, -20);
	objectBox[17].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[18].CreateBox(-10, 10, -20);
	objectBox[18].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[19].CreateBox(10, 10, -20);
	objectBox[19].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[20].CreateBox(10, 30, -20);
	objectBox[20].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[21].CreateBox(50, 10, -20);
	objectBox[21].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[22].CreateBox(50, 30, -20);
	objectBox[22].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[23].CreateBox(50, 50, -20);
	objectBox[23].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[24].CreateBox(50, 70, -20);
	objectBox[24].setColor(rand() % 255, rand() % 255, rand() % 255);

	//4행
	objectBox[25].CreateBox(-50, 10, 0);
	objectBox[25].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[26].CreateBox(-50, 30, 0);
	objectBox[26].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[27].CreateBox(-50, 50, 0);
	objectBox[27].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[28].CreateBox(-30, 10, 0);
	objectBox[28].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[29].CreateBox(-30, 30, 0);
	objectBox[29].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[30].CreateBox(-10, 10, 0);
	objectBox[30].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[31].CreateBox(-10, 30, 0);
	objectBox[31].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[32].CreateBox(-10, 50, 0);
	objectBox[32].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[33].CreateBox(10, 10, 0);
	objectBox[33].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[34].CreateBox(10, 30, 0);
	objectBox[34].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[35].CreateBox(50, 10, 0);
	objectBox[35].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[36].CreateBox(50, 30, 0);
	objectBox[36].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[37].CreateBox(50, 50, 0);
	objectBox[37].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[38].CreateBox(50, 70, 0);
	objectBox[38].setColor(rand() % 255, rand() % 255, rand() % 255);

	//5행
	objectBox[39].CreateBox(-50, 10, 20);
	objectBox[39].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[40].CreateBox(-50, 30, 20);
	objectBox[40].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[41].CreateBox(-50, 50, 20);
	objectBox[41].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[42].CreateBox(-30, 10, 20);
	objectBox[42].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[43].CreateBox(-30, 30, 20);
	objectBox[43].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[44].CreateBox(10, 10, 20);
	objectBox[44].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[45].CreateBox(30, 10, 20);
	objectBox[45].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[46].CreateBox(30, 30, 20);
	objectBox[46].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[47].CreateBox(50, 10, 20);
	objectBox[47].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[48].CreateBox(50, 30, 20);
	objectBox[48].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[49].CreateBox(50, 50, 20);
	objectBox[49].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[50].CreateBox(50, 70, 20);
	objectBox[50].setColor(rand() % 255, rand() % 255, rand() % 255);


	// 6행
	objectBox[51].CreateBox(-50, 10, 40);
	objectBox[51].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[52].CreateBox(-50, 30, 40);
	objectBox[52].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[53].CreateBox(-50, 50, 40);
	objectBox[53].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[54].CreateBox(-30, 10, 40);
	objectBox[54].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[55].CreateBox(-30, 30, 40);
	objectBox[55].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[56].CreateBox(10, 10, 40);
	objectBox[56].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[57].CreateBox(30, 10, 40);
	objectBox[57].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[58].CreateBox(30, 30, 40);
	objectBox[58].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[59].CreateBox(50, 10, 40);
	objectBox[59].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[60].CreateBox(50, 30, 40);
	objectBox[60].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[61].CreateBox(50, 50, 40);
	objectBox[61].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[62].CreateBox(50, 70, 40);
	objectBox[62].setColor(rand() % 255, rand() % 255, rand() % 255);

	//7행

	objectBox[63].CreateBox(-30, 10, 60);
	objectBox[63].setColor(rand() % 255, rand() % 255, rand() % 255);

	objectBox[64].CreateBox(10, 10, 60);
	objectBox[64].setColor(rand() % 255, rand() % 255, rand() % 255);

}

void S01Main::LightSetting()
{
	//조명 설정
	mapLight[0].DefaultLightPosSetting(30, 5, 60, 1);
	mapLight[1].DefaultLightPosSetting(-30, 45, 20, 1);

	mapLight[2].DefaultLightPosSetting(30, 5, 0, 0);
	mapLight[3].DefaultLightPosSetting(-30, 5, -40, 0);

	// 조명의 색상 지정

	mapLight[0].settingDiffuse(1.f, 0.f, 0.f, 0.6f);
	mapLight[1].settingDiffuse(1.f, 0.f, 0.f, 0.6f);

	mapLight[2].settingDiffuse(0.f, 0.f, 1.f, 0.6f);
	mapLight[2].settingDiffuse(0.f, 0.f, 1.f, 0.6f);

	//조명의 거울반사 세기 지정
	mapLight[0].settingSpecu(1.f, 0.f, 0.f, 1.f);
	mapLight[1].settingSpecu(1.f, 0.f, 0.f, 1.f);

	mapLight[2].settingSpecu(0.f, 0.f, 1.f, 1.f);
	mapLight[3].settingSpecu(0.f, 0.f, 1.f, 1.f);


	// 주변광
	//mapLight[0].settingAmbient(1.f, 1.f, 1.f, 0.f);
	//mapLight[1].settingAmbient(1.f, 1.f, 1.f, 0.f);

	//mapLight[2].settingAmbient(1.f, 1.f, 1.f, 0.f);
	//mapLight[3].settingAmbient(1.f, 1.f, 1.f, 0.f);

	for (int i = 0; i < 4; ++i)
		mapLight[i].LightOn(true, i);
}