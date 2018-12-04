#include "stdafx.h"
#include "Scene02.h"
#include "GLFramework.h"
#include "banana_draw.h"// 애 이상한친구인데......................... 다른곳에 넣으면 안돌던데....
#include "LoadMap.h"
#include "Character.h"
#include "BananaSetting.h"

static int whatBox;
static int LightCount = 4;

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

	//인게임 bgm 재생초기화
	m_SoundPlayer.init();
	m_SoundPlayer.selectFolder("Resources\\BGM");

	//걷기 효과음 재생 초기화
	m_walkingSound.init();
	m_walkingSound.selectFolder("Resources\\Sound");

	m_Camera.setDistance(300.f);
	m_Camera.setPerspective(45.f, 0.125f, 7'000.f);
	m_Camera.setSensitivity(10.f);

	//for (int i = 0; i < 20; ++i) {
	//	objectBox[i].CreateBox(rand() % 120 - 60, 10, rand() % 140 - 70);
	//	objectBox[i].setColor(rand() % 255, rand() % 255, rand() % 255);
	//}
	//tmpRect.x = -10;
	//tmpRect.y = 10;
	//tmpRect.z = 60;
	//LightSetting();
	//DefaultBoxPosSetting();
	dep = false;
	whatBox = LoadMap(objectBox, tmpRect, 2);
	LightCount = LoadLight(mapLight, 2);
	for (int i = 0; i < 4; ++i)
		mapLight[i].LightOn(true, i);
}

void S02Main::exit()
{
	m_SoundPlayer.exit();
	m_walkingSound.exit();
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

	for (int i = 0; i < whatBox; ++i)
		objectBox[i].drawBox(20);

	for (int i = 0; i < LightCount; ++i)
		mapLight[i].drawLight(TRUE, i);

	//glPushMatrix();
	//glTranslatef(tmpRect.x, tmpRect.y, tmpRect.z);
	//glColor3f(1.f, 0.4f, 0.2f);
	//glutSolidCube(10);
	//glPopMatrix();
	wall();
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
			//m_walkingSound.play();
			break;

		case 'a':
			aPress = true;
			//m_walkingSound.play();
			break;

		case 's':
			sPress = true;
			//m_walkingSound.play();
			break;

		case 'd':
			dPress = true;
			//m_walkingSound.play();
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
		bool tmpcheck = false;
		for (int i = 0; i < whatBox; ++i) {
			if (objectBox[i].returnBoxCenterX() - 10 < returnMainX() + 5 && objectBox[i].returnBoxCenterX() + 10 > returnMainX() - 5 && objectBox[i].returnBoxCenterZ() + 10 > returnMainZ() - 5 && objectBox[i].returnBoxCenterZ() - 10 < returnMainZ() + 5 && returnMainY() > objectBox[i].returnBoxCenterY() - 20 && returnMainY() < objectBox[i].returnBoxCenterY() + 20) {
				down = TRUE;
				jump = FALSE;
				tmpRect.jumpCount = 0;
				tmpRect.y -= 1;
			}
		}

		tmpcheck = false;

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

				if (depthCheck >= 50) {
					if (dep == false) {
						dep = true;
						depthCheck = 0;
					}
					else {
						wPress = false;
						aPress = false;
						sPress = false;
						dPress = false;
						dep = false;
						depthCheck = 0;
						m_Framework->toScene("Ending");
					}
				}
				depthCheck = 0;
			}
		}

		if (tmpRect.y > 10 && tmpcheck == false) {
			tmpRect.y -= 1;
			depthCheck++;
		}

		if (tmpRect.y <= 10 && tmpcheck == false) {
			down = FALSE;
			if (depthCheck >= 50) {
				if (dep == false) {
					dep = true;
					depthCheck = 0;
				}
				else {
					wPress = false;
					aPress = false;
					sPress = false;
					dPress = false;
					dep = false;
					depthCheck = 0;
					m_Framework->toScene("Ending");
				}
			}
			depthCheck = 0;
		}

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

			if (boxLanding != true) {
				objectBox[k].movingY(-1);
				if (objectBox[k].returnBoxCenterX() - 10 < returnMainX() + 5 && objectBox[k].returnBoxCenterX() + 10 > returnMainX() - 5 && objectBox[k].returnBoxCenterZ() + 10 > returnMainZ() - 5 && objectBox[k].returnBoxCenterZ() - 10 < returnMainZ() + 5 && returnMainY() > objectBox[k].returnBoxCenterY() - 20 && returnMainY() < objectBox[k].returnBoxCenterY() + 20) {
					m_Camera.init();
					wPress = false;
					aPress = false;
					sPress = false;
					dPress = false; 
					m_Framework->toScene("Ending");
				}
			}
		}

	}

	check = FALSE;
	if (wPress == true) {
		cycle = 0;
		count = 0;
		boxCheckCount = 0;
		i = 0;
		angle = 180;
		mainCharacter.movingZ(-1);
		tmpRect.z -= 1;
		boxCheckCount = 0;
		while (check == FALSE) {

			if (returnMainZ() - 6 <= objectBox[i].returnBoxCenterZ() + 10 && !(returnMainZ() + 6 <= objectBox[i].returnBoxCenterZ() - 10)) {
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

		if (returnMainZ() > -60) {
			if (m_walkingSound.playing() == false)
				m_walkingSound.play();
			if (boxCheckCount < 3) {
				for (int o = 0; o < boxCheckCount; ++o)
					objectBox[saveBoxIndex[o]].movingZ(-1);
			}
			else
				tmpRect.z += 1;
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
		cycle = 0;
		count = 0;
		boxCheckCount = 0;
		i = 0;
		angle = 270;
		tmpRect.x -= 1;
		mainCharacter.movingX(-1);
		boxCheckCount = 0;
		while (check == FALSE) {

			if (returnMainX() - 6 <= objectBox[i].returnBoxCenterX() + 10 && !(returnMainX() + 6 <= objectBox[i].returnBoxCenterX() - 10)) {
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

		if (returnMainX() > -55) {
			if (m_walkingSound.playing() == false)
				m_walkingSound.play();
			if (boxCheckCount < 3) {
				for (int o = 0; o < boxCheckCount; ++o)
					objectBox[saveBoxIndex[o]].movingX(-1);
			}

			else
				tmpRect.x += 1;
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
		cycle = 0;
		count = 0;
		boxCheckCount = 0;
		i = 0;
		angle = 180;
		tmpRect.z += 1;
		mainCharacter.movingZ(1);
		boxCheckCount = 0;
		while (check == FALSE) {

			if (returnMainZ() - 6 <= objectBox[i].returnBoxCenterZ() + 10 && !(returnMainZ() + 6 <= objectBox[i].returnBoxCenterZ() - 10)) {
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

		if (returnMainZ() < 60) {
			if (m_walkingSound.playing() == false)
				m_walkingSound.play();
			if (boxCheckCount < 3) {
				for (int o = 0; o < boxCheckCount; ++o)
					objectBox[saveBoxIndex[o]].movingZ(1);
			}
			else
				tmpRect.z -= 1;
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
		cycle = 0;
		count = 0;
		boxCheckCount = 0;
		i = 0;
		angle = 90;
		tmpRect.x += 1;
		mainCharacter.movingX(1);
		boxCheckCount = 0;
		while (check == FALSE) {

			if (returnMainX() - 6 <= objectBox[i].returnBoxCenterX() + 10 && !(returnMainX() + 6 <= objectBox[i].returnBoxCenterX() - 10)) {
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


		if (returnMainX() < 55) {

			if(m_walkingSound.playing() == false)
				m_walkingSound.play();
			if (boxCheckCount < 3) {
				for (int o = 0; o < boxCheckCount; ++o)
					objectBox[saveBoxIndex[o]].movingX(1);
			}
			else
				tmpRect.x -= 1;
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
		lightLanding = false;
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

	if (aPress == true)
		radian = 180;

	if (sPress == true)
		radian = 270;

	if (dPress == true)
		radian = 0;

	if (wPress == true && dPress == true)
		radian = 45;

	if (wPress == true && aPress == true)
		radian = 135;


	if (sPress == true && aPress == true)
		radian = 225;

	if (sPress == true && dPress == true)
		radian = 315;



}

void S02Main::DefaultBoxPosSetting()
{
	// Scene01 카메라는 언제쯤 제대로 돌까.....
	// 이젠 진짜 6일 남았는데....
	// 이상태로 게임은 나오긴 할까....
	// 일단 버리는 함수는 일기장
	// 하루만 더 믿어본다.....................
	// if(day == 5 && camera == false)
	//		exit(1);


}

void S02Main::LightSetting()
{
	//조명 설정
	mapLight[0].DefaultLightPosSetting(30, 5, 60, 1);
	mapLight[1].DefaultLightPosSetting(-30, 45, 20, 1);

	mapLight[2].DefaultLightPosSetting(30, 5, 0, 0);
	mapLight[3].DefaultLightPosSetting(-30, 5, -40, 0);

	// 조명의 색상 지정

	mapLight[0].settingDiffuse(1.f, 0.f, 0.f, 1.f);
	mapLight[1].settingDiffuse(1.f, 0.f, 0.f, 1.f);

	mapLight[2].settingDiffuse(0.f, 0.f, 1.f, 1.f);
	mapLight[2].settingDiffuse(0.f, 0.f, 1.f, 1.f);

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