#include "stdafx.h"
#include "Scene02.h"
#include "GLFramework.h"
#include "banana_draw.h"// 애 이상한친구인데......................... 다른곳에 넣으면 안돌던데....
#include "LoadMap.h"
#include "Character.h"
#include "BananaSetting.h"

#define whatBox 65
#define LightCount 4

static int angle = 0;


S02Main::S02Main()
{
}

S02Main::~S02Main()
{
}

void S02Main::init()
{
	radian = 90;
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
	//DefaultBoxPosSetting();
	LoadMap(objectBox, 1);
}

void S02Main::exit()
{
	m_SoundPlayer.exit();
}

void S02Main::reset()
{
	m_SoundPlayer.play();
}

float S02Main::returnMainX()
{
	return tmpRect.x + tmpRect.xRate;
}

float S02Main::returnMainY()
{
	return tmpRect.y + tmpRect.yRate;
}

float S02Main::returnMainZ()
{
	return tmpRect.z + tmpRect.zRate;
}

void S02Main::render()
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

	for (int i = 0; i < 65; ++i)
		objectBox[i].drawBox(20);

	for (int i = 0; i < LightCount; ++i)
		mapLight[i].drawLight();

	//glPushMatrix();
	//glTranslatef(tmpRect.x, tmpRect.y, tmpRect.z);
	//glColor3f(1.f, 0.4f, 0.2f);
	//glutSolidCube(10);
	//glPopMatrix();

	glPushMatrix();
	banana_draw(tmpRect.x, tmpRect.y + 5, tmpRect.z, 0.5, IDLE, banana.rot.degree, radian + 90);
	glPopMatrix();

	glPopMatrix();
}

void S02Main::reshape(int w, int h)
{

}

static BOOL jump = FALSE;
static BOOL limited = FALSE;
static BOOL down = FALSE;
static bool wPress = false;
static bool aPress = false;
static bool sPress = false;
static bool dPress = false;

void S02Main::keyboard(int key, bool pressed, int x, int y, bool special)
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
			wPress = true;
			break;

		case 'a':
			aPress = true;
			break;

		case 's':
			sPress = true;
			break;

		case 'd':
			dPress = true;
			break;

		case ' ':
			if (jump == FALSE && down == FALSE)
				jump = TRUE;
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
	else {
		if (key == 'w')
			wPress = false;
		else if (key == 'a')
			aPress = false;
		else if (key == 's')
			sPress = false;
		else if (key == 'd')
			dPress = false;
	}

}

void S02Main::mouse(int button, bool pressed, int x, int y)
{
}

void S02Main::motion(bool pressed, int x, int y)
{
	m_Camera.rotate(x, y, pressed);
}


void S02Main::update(float fDeltaTime)
{
	int saveBoxIndex[100];
	Time_count++;
	if (Time_count % 20 == 0)
	{
		switch_sign *= -1;
	}
	banana.rot.degree += 0.1f * switch_sign;

	if (jump == TRUE && down == FALSE) {
		tmpRect.y += 1;
		tmpRect.jumpCount += 1;
		if (tmpRect.jumpCount > 30) {
			jump = FALSE;
			tmpRect.jumpCount = 0;
			down = TRUE;
		}
	}

	else {
		bool tmpcheck = false;
		for (int i = 0; i < whatBox; ++i) {
			if (objectBox[i].returnBoxCenterX() - 10 < returnMainX() + 5 && objectBox[i].returnBoxCenterX() + 10 > returnMainX() - 5 && objectBox[i].returnBoxCenterZ() + 10 > returnMainZ() - 5 && objectBox[i].returnBoxCenterZ() - 10 < returnMainZ() + 5 && tmpRect.y < objectBox[i].returnBoxCenterY() + 20) {
				down = FALSE;
				tmpcheck = true;
			}
		}

		if (tmpRect.y > 10 && tmpcheck == false) {
			tmpRect.y -= 1;
		}

		if (tmpRect.y <= 10 && tmpcheck == false)
			down = FALSE;

		tmpcheck = false;
	}



	// 캐릭도 연속 이동
	bool check = false;
	int cycle = 0;
	int count = 0;
	int boxCheckCount = 0;
	int i = 0;


	bool boxLanding = false;
	for (int k = 0; k < whatBox; ++k)
	{
		boxLanding = false;
		i = 0;
		check = FALSE;
		if (objectBox[k].returnBoxCenterY() - 10 > 0) {

			while (check == FALSE) {
				if ((objectBox[i].returnBoxCenterX() - 10 < objectBox[k].returnBoxCenterX() + 10 && objectBox[i].returnBoxCenterX() + 10 > objectBox[k].returnBoxCenterX() - 10 && objectBox[i].returnBoxCenterZ() + 10 > objectBox[k].returnBoxCenterZ() - 10 && objectBox[i].returnBoxCenterZ() - 10 < objectBox[k].returnBoxCenterZ() + 10) && i != k) {
					if (objectBox[k].returnBoxCenterY() - 10 <= objectBox[i].returnBoxCenterY() + 10 && (objectBox[k].returnBoxCenterY() + 10 > objectBox[i].returnBoxCenterY() - 10)) {
						boxLanding = true;
						//check = TRUE;
					}
				}

				i++;
				if (i == whatBox) {
					i = 0;
					check = TRUE;
				}

			}

			if (boxLanding != true)
				objectBox[k].movingY(-1);
		}

	}

	check = FALSE;
	if (wPress == true) {
		angle = 180;
		mainCharacter.movingZ(-1);
		tmpRect.z -= 1;
		boxCheckCount = 0;
		while (check == FALSE) {

			if (returnMainZ() - 5 <= objectBox[i].returnBoxCenterZ() + 10 && !(returnMainZ() + 5 <= objectBox[i].returnBoxCenterZ() - 10)) {
				if (objectBox[i].returnBoxCenterX() - 10 < returnMainX() + 5 && objectBox[i].returnBoxCenterX() + 10 > returnMainX() - 5 && objectBox[i].returnBoxCenterY() + 10 > returnMainY() - 5 && objectBox[i].returnBoxCenterY() - 10 < returnMainY() + 5) {
					if (objectBox[i].returnCheck() == 0) {
						tmpRect.zRate -= 20;
						//objectBox[i].movingZ(-1);
						objectBox[i].checkUpdate(1);
						saveBoxIndex[boxCheckCount] = i;
						boxCheckCount++;
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

		if (boxCheckCount < 3) {
			for (int o = 0; o < boxCheckCount; ++o)
				objectBox[saveBoxIndex[o]].movingZ(-1);
		}
		else
			tmpRect.z += 1;

		for (int k = 0; k < whatBox; ++k)
			objectBox[k].checkUpdate(0);

		boxCheckCount = 0;
		check = FALSE;
		cycle = 0;

		tmpRect.zRate = 0;
		tmpRect.xRate = 0;
		tmpRect.yRate = 0;
	}

	if (aPress == true) {
		angle = 270;
		tmpRect.x -= 1;
		mainCharacter.movingX(-1);
		boxCheckCount = 0;
		while (check == FALSE) {

			if (returnMainX() - 5 <= objectBox[i].returnBoxCenterX() + 10 && !(returnMainX() + 5 <= objectBox[i].returnBoxCenterX() - 10)) {
				if (objectBox[i].returnBoxCenterZ() - 10 < returnMainZ() + 5 && objectBox[i].returnBoxCenterZ() + 10 > returnMainZ() - 5 && objectBox[i].returnBoxCenterY() + 10 > returnMainY() - 5 && objectBox[i].returnBoxCenterY() - 10 < returnMainY() + 5) {
					if (objectBox[i].returnCheck() == 0) {
						tmpRect.xRate -= 20;

						//objectBox[i].movingX(-1);
						objectBox[i].checkUpdate(1);
						saveBoxIndex[boxCheckCount] = i;
						boxCheckCount++;
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

		if (boxCheckCount < 3) {
			for (int o = 0; o < boxCheckCount; ++o)
				objectBox[saveBoxIndex[o]].movingX(-1);
		}
		else
			tmpRect.x += 1;

		boxCheckCount = 0;
		check = FALSE;
		cycle = 0;
		tmpRect.xRate = 0;
		tmpRect.yRate = 0;
		tmpRect.zRate = 0;
	}

	if (sPress == true) {
		angle = 180;
		tmpRect.z += 1;
		mainCharacter.movingZ(1);
		boxCheckCount = 0;
		while (check == FALSE) {

			if (returnMainZ() - 5 <= objectBox[i].returnBoxCenterZ() + 10 && !(returnMainZ() + 5 <= objectBox[i].returnBoxCenterZ() - 10)) {
				if (objectBox[i].returnBoxCenterX() - 10 < returnMainX() + 5 && objectBox[i].returnBoxCenterX() + 10 > returnMainX() - 5 && objectBox[i].returnBoxCenterY() + 10 > returnMainY() - 5 && objectBox[i].returnBoxCenterY() - 10 < returnMainY() + 5) {
					if (objectBox[i].returnCheck() == 0) {
						tmpRect.zRate += 20;
						//objectBox[i].movingZ(1);
						objectBox[i].checkUpdate(1);
						saveBoxIndex[boxCheckCount] = i;
						boxCheckCount++;
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


		if (boxCheckCount < 3) {
			for (int o = 0; o < boxCheckCount; ++o)
				objectBox[saveBoxIndex[o]].movingZ(1);
		}
		else
			tmpRect.z -= 1;

		for (int k = 0; k < whatBox; ++k)
			objectBox[k].checkUpdate(0);


		check = FALSE;
		boxCheckCount = 0;
		cycle = 0;
		tmpRect.xRate = 0;
		tmpRect.yRate = 0;
		tmpRect.zRate = 0;
	}

	if (dPress == true) {
		angle = 90;
		tmpRect.x += 1;
		mainCharacter.movingX(1);
		boxCheckCount = 0;
		while (check == FALSE) {

			if (returnMainX() - 5 <= objectBox[i].returnBoxCenterX() + 10 && !(returnMainX() + 5 <= objectBox[i].returnBoxCenterX() - 10)) {
				if (objectBox[i].returnBoxCenterZ() - 10 < returnMainZ() + 5 && objectBox[i].returnBoxCenterZ() + 10 > returnMainZ() - 5 && objectBox[i].returnBoxCenterY() + 10 > returnMainY() - 5 && objectBox[i].returnBoxCenterY() - 10 < returnMainY() + 5) {
					if (objectBox[i].returnCheck() == 0) {
						tmpRect.xRate += 20;
						//objectBox[i].movingX(1);
						objectBox[i].checkUpdate(1);
						saveBoxIndex[boxCheckCount] = i;
						boxCheckCount++;
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


		if (boxCheckCount < 3) {
			for (int o = 0; o < boxCheckCount; ++o)
				objectBox[saveBoxIndex[o]].movingX(1);
		}
		else
			tmpRect.x -= 1;

		boxCheckCount = 0;
		check = FALSE;
		cycle = 0;
		tmpRect.xRate = 0;
		tmpRect.yRate = 0;
		tmpRect.zRate = 0;
	}

	//조명 낙하
	bool lightLanding = false;
	for (int light = 0; light < LightCount; ++light) {

		i = 0;
		check = FALSE;
		if (mapLight[light].returnYpos() - 3 > 0) {

			while (check == FALSE) {
				if ((objectBox[i].returnBoxCenterX() - 10 < mapLight[light].returnXpos() + 3 && objectBox[i].returnBoxCenterX() + 10 > mapLight[light].returnXpos() - 3 && objectBox[i].returnBoxCenterZ() + 10 > mapLight[light].returnZpos() - 3 && objectBox[i].returnBoxCenterZ() - 10 < mapLight[light].returnZpos() + 3)) {
					if (mapLight[light].returnYpos() - 3 <= objectBox[i].returnBoxCenterY() + 10 && (mapLight[light].returnYpos() + 10 > objectBox[i].returnBoxCenterY() - 10)) {
						lightLanding = true;
						//check = TRUE;
					}
				}

				i++;
				if (i == whatBox) {
					i = 0;
					check = TRUE;
				}

			}

			if (lightLanding != true)
				mapLight[light].moveY(-1);
		}
	}



	// 캐릭터 회전

	if (wPress == true)
		radian = 90;

	if (wPress == true && dPress == true)
		radian = 45;

	if (wPress == true && aPress == true)
		radian = 135;

	if (aPress == true)
		radian = 180;

	if (sPress == true)
		radian = 270;

	if (dPress == true)
		radian = 0;

	if (sPress == true && aPress == true)
		radian = 225;

	if (sPress == true && dPress == true)
		radian = 315;



}

void S02Main::DefaultBoxPosSetting()
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

void S02Main::LightSetting()
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