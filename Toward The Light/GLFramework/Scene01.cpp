#include "stdafx.h"
#include "Scene01.h"
#include "GLFramework.h"
#include "banana_draw.h"// 애 이상한친구인데......................... 다른곳에 넣으면 안돌던데....
#include "LoadMap.h"
#include "Character.h"
#include "BananaSetting.h"
						// 11/30 오후 7시반 오지않는 바나나 클래스를 기다리며
#define whatBox 65
#define LightCount 4

static int angle = 0;
Vector3 Eye;
Vector3 At;
int move_Eye[3];
float camera_deree[3];


bool person_view_1 = false;
bool person_view_3 = true;

int change_person_view_count = 0;

S01Main::S01Main()
{
}

S01Main::~S01Main()
{
}

void S01Main::init()
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

	m_Camera.setEye(Eye);

	

	move_Eye[0] = tmpRect.x;
	move_Eye[1] = tmpRect.y + 100;
	move_Eye[2] = tmpRect.z;


}

void S01Main::exit()
{
	m_SoundPlayer.exit();
}

void S01Main::reset()
{
	m_SoundPlayer.play();
}

float S01Main::returnMainX()
{
	return tmpRect.x + tmpRect.xRate;
}

float S01Main::returnMainY()
{
	return tmpRect.y + tmpRect.yRate;
}

float S01Main::returnMainZ()
{
	return tmpRect.z + tmpRect.zRate;
}
int __t = 0;

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

	for (int i = 0; i < 65; ++i)
		objectBox[i].drawBox(20);

	for (int i = 0; i < LightCount; ++i)
		mapLight[i].drawLight(TRUE, i);

	//glPushMatrix();
	//glColor3f(1.f, 0.4f, 0.2f);
	//glutSolidCube(10);
	//glPopMatrix();

	glPushMatrix();
	banana_draw(tmpRect.x, tmpRect.y + 5, tmpRect.z, 0.5, IDLE, banana.rot.degree, radian);
	glPopMatrix();
	//카메라 정리 ---
	
	if(person_view_1){
		move_Eye[0] = tmpRect.x;
		//move_Eye[1] = tmpRect.y;
		move_Eye[2] = tmpRect.z;

		Eye.x = move_Eye[0];
		Eye.y = tmpRect.y + 20;
		Eye.z = move_Eye[2] - 20;

		//각도에 맞춰서 카메라를 돌려준다.
		At.x = move_Eye[0] + sin(radian  * 3.141592 / 180) * 50;
		At.z = move_Eye[2] + cos(radian  * 3.141592 / 180) * 50;
		At.y = tmpRect.y + 10;
	}
	else if (person_view_3) {
		move_Eye[0] = tmpRect.x;
		//move_Eye[1] = tmpRect.y;
		move_Eye[2] = tmpRect.z;

		Eye.x = move_Eye[0];
		Eye.y = tmpRect.y + 50;
		Eye.z = move_Eye[2] + 20;

		//각도에 맞춰서 카메라를 돌려준다.
		At.x = move_Eye[0] + sin(radian  * 3.141592 / 180) * 50;
		At.z = move_Eye[2] + cos(radian  * 3.141592 / 180) * 50;
		At.y = tmpRect.y + 20;
	}
	
	m_Camera.setEye(Eye);
	m_Camera.setTarget(At);

	glPushMatrix();

	glPopMatrix();


	glPopMatrix();
}


void S01Main::reshape(int w, int h)
{

}

static BOOL jump = FALSE;
static BOOL limited = FALSE;
static BOOL down = FALSE;
static bool wPress = false;
static bool aPress = false;
static bool sPress = false;
static bool dPress = false;



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
			wPress = true;
			break;

		case 'a':
			aPress = true;
			//camera_deree[0] = Eye.x * cos(radian * 3.14) + Eye.z * -sin(radian * 3.14);
			//camera_deree[2] = Eye.x * sin(radian * 3.14) + Eye.z * cos(radian * 3.14);

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
		case 'u':
			change_person_view_count += 1;
			if (change_person_view_count % 2 == 0) {
				person_view_1 = false;
				person_view_3 = true;
			}
			if (change_person_view_count % 2 == 1) {
				person_view_1 = true;
				person_view_3 = false;
			}

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

void S01Main::mouse(int button, bool pressed, int x, int y)
{
}

void S01Main::motion(bool pressed, int x, int y)
{
	m_Camera.rotate(x, y, pressed);
}



void S01Main::update(float fDeltaTime)
{
	__t += 1;

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


		tmpRect.z -= 1;
		angle = 180;
		mainCharacter.movingZ(-1);
		
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
		{
			tmpRect.z += 1;
	
		}

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
		{
			tmpRect.x += 1;
		}

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
		{
		
			tmpRect.z -= 1;

		}
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
		{
		
			tmpRect.x -= 1;

		}
		boxCheckCount = 0;
		check = FALSE;
		cycle = 0;
		tmpRect.xRate = 0;
		tmpRect.yRate = 0;
		tmpRect.zRate = 0;
	}


	// 조명의 낙하(상자위에 있을때)
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
		radian = 180;

	if (wPress == true && dPress == true)
		radian = (180 - 45);

	if (wPress == true && aPress == true)
		radian = 180+45;

	if (aPress == true)
		radian = 270;

	if (sPress == true)
		radian = 360;

	if (dPress == true)
		radian = 90;
	
	if (sPress == true && aPress == true)
		radian = 360-45;

	if (sPress == true && dPress == true)
		radian = 360+45;



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

void S01Main::camera_install(int x, int y) {
	printf("ok \n");

}
