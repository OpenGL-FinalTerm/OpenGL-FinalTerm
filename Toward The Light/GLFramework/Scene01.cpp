#include "stdafx.h"
#include "Scene01.h"
#include "GLFramework.h"
#include "banana_draw.h"// 애 이상한친구인데......................... 다른곳에 넣으면 안돌던데....
#include "LoadMap.h"
#include "Character.h"
#include "BananaSetting.h"

// 11/30 오후 7시반 오지않는 바나나 클래스를 
static int whatBox;
static int LightCount;

static int angle = 0;

//이동을 위함 임시 변수
bool go_front;
bool go_left;
bool go_right;
bool go_back;



//코딩 3일차 오프닝 엔딩 카메라까지 전부 구현했다 델몬트 바나나가 먹고싶다

#define d_Sensitivity  3 //감도 how many rotate camera

S01Main::S01Main()
{
}

S01Main::~S01Main()
{
}

void S01Main::init()
{
	ShowCursor(false);
	radian = 90;
	m_SoundPlayer.init();
	m_SoundPlayer.selectFolder("Resources\\BGM");

	m_Camera.setDistance(300.f);
	m_Camera.setPerspective(45.f, 0.125f, 7'000.f);
	m_Camera.setSensitivity(10.f);

	//for (int i = 0; i < 20; ++i) {
	//   objectBox[i].CreateBox(rand() % 120 - 60, 10, rand() % 140 - 70);
	//   objectBox[i].setColor(rand() % 255, rand() % 255, rand() % 255);
	//}
	tmpRect.x = -10;
	tmpRect.z = 60;
	tmpRect.y = 10;

	
	//LightSetting();
	//DefaultBoxPosSetting();
	whatBox = LoadMap(objectBox, tmpRect, 2);
	LightCount = LoadLight(mapLight, 2);

	m_Camera.setEye(Eye);
	result_degree[0] = 180;

	//붉은 조명기둥 위치 읽어오기
	red_right_cylinder.x = -50;
	red_right_cylinder.y = 100;
	red_right_cylinder.z = -100;

	//카메라 위치를 셋업합니다.
	//초기 카메라 위치를 설정합니다.
	Eye.x = red_right_cylinder.x;
	Eye.y = red_right_cylinder.y;
	Eye.z = red_right_cylinder.z;

	opening_camera_working = true;
	opening_bezier_t = 0;
	//
	end_At.x = tmpRect.x + sin(180 * 3.141592 / 180) * 100;
	end_At.z = tmpRect.z + cos(180 * 3.141592 / 180) * 100;
	start_At.x = 1;
	start_At.y = 1;

	view_rotate[0] = 60;
	view_rotate[1] = 50;

	view_at_size[0] = 100;
	view_at_size[1] = 10;
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

	//카메라 정리 ---
	if (opening_camera_working) {//오프닝 영상이 시작되면
		
		if (opening_bezier_t >= 1) {
			opening_camera_working = false;
		}
		opening_bezier_t += 0.01f;
	
		opening_camera_Eye(&red_right_cylinder.x, &red_right_cylinder.y, &red_right_cylinder.z, &tmpRect.x, &tmpRect.y, &tmpRect.z, &opening_bezier_t, 300, &Eye.x, &Eye.y, &Eye.z);
		opening_camera_At(&start_At.x, &start_At.y, &start_At.z, &end_At.x, &end_At.y, &end_At.z, &opening_bezier_t, &At.x, &At.y, &At.z);
	
		printf("opeing %f \n", Eye.y);
	}
	
	
	if (!opening_camera_working) { //오프닝 카메라 워킹이 false
		//eye 도 각도에 따라 바뀐다.
		camera_moving_Eye(&tmpRect.x, &tmpRect.y, &tmpRect.z, &result_degree[0], &view_rotate[0], &view_rotate[1], &Eye.x, &Eye.y, &Eye.z);
		camera_moving_At(&tmpRect.x, &tmpRect.y, &tmpRect.z, &result_degree[0], &view_at_size[0], &view_at_size[1], &At.x, &At.y, &At.z);
	}

	glPushMatrix();
	banana_draw(tmpRect.x, tmpRect.y + 5, tmpRect.z, 0.5, IDLE, banana.rot.degree, result_degree[0]);
	glPopMatrix();

	m_Camera.setEye(Eye);
	m_Camera.setTarget(At);

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
	bool beforePick = false;
	static int pickCount = 0;


	if (pressed)
	{
		switch (key)
		{
		case 'w':
			//위로 이동
			go_front = true;

			break;

		case 'a':
			//왼쪽 이동
			go_left = true;

			break;

		case 's':
			//뒤로 이동
			go_back = true;
			break;

		case 'd':
			//우측 이동
			go_right = true;
			
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
			//1인칭
			if (change_person_view_count % 2 == 0) {
				//view_rotate[0] => 최소 범위 (20) 카메라의 회전반경을 나타냅니다. 
				// view_rotate[1] => (20) 카메라의 높이를 나타냅니다. 
				view_rotate[0] = 80;
				view_rotate[1] = 50;

			}
			else if (change_person_view_count % 2 == 1) {	//3인칭

				view_rotate[0] = 0;
				view_rotate[1] = 20;

			}
			printf("%d \n", change_person_view_count % 2);
			break;

		case 'q':
			if (change_person_view_count % 3 == 2) {
				radian += 1;
			}
			break;
		case 'e':
			if (change_person_view_count % 3 == 2) {
				radian -= 1;
			}
			break;

		case 'f':
		case 'F':

			for (int i = 0; i < LightCount; ++i) {
				if (mapLight[i].returnPickCheck() == true)
					beforePick = true;
			}

			if (pickLightNumber != -1 && beforePick == false) {
				mapLight[pickLightNumber].pickUp(true);
				pickLight = true;
			}

			if (pickLight == true) {
				if (pickCount % 2 == 1) {
					mapLight[pickLightNumber].pickUp(false);
					pickCount = 0;
					pickLight = false;
					beforePick = false;
					pickLightNumber = -1;
				}
				else
					pickCount++;
			}
			beforePick = false;
			break;

		}

	}
	else {
		if (key == 'w') {
			if (wPress == true)
				wPress = false;
			if (aPress == true)
				aPress = false;
			if (sPress == true)
				sPress = false;
			if (dPress == true)
				dPress = false;
			
			//위치
			if (go_front)
				go_front = false;
			if (go_left)
				go_left = false;
			if (go_right)
				go_right = false;
			if (go_back)
				go_back = false;
		}
		else if (key == 'a') {
			if (wPress == true)
				wPress = false;
			if (aPress == true)
				aPress = false;
			if (sPress == true)
				sPress = false;
			if (dPress == true)
				dPress = false;

			//위치
			if (go_front)
				go_front = false;
			if (go_left)
				go_left = false;
			if (go_right)
				go_right = false;
			if (go_back)
				go_back = false;
		}
		else if (key == 's') {
			if (wPress == true)
				wPress = false;
			if (aPress == true)
				aPress = false;
			if (sPress == true)
				sPress = false;
			if (dPress == true)
				dPress = false;

			//위치
			if (go_front)
				go_front = false;
			if (go_left)
				go_left = false;
			if (go_right)
				go_right = false;
			if (go_back)
				go_back = false;
		}
		else if (key == 'd') {
			if (wPress == true)
				wPress = false;
			if (aPress == true)
				aPress = false;
			if (sPress == true)
				sPress = false;
			if (dPress == true)
				dPress = false;

			//위치
			if (go_front)
				go_front = false;
			if (go_left)
				go_left = false;
			if (go_right)
				go_right = false;
			if (go_back)
				go_back = false;
		}
	}

}

void S01Main::mouse(int button, bool pressed, int x, int y)
{
	if (pressed) {
		if (button == GLUT_LEFT_BUTTON && pickLight == true) {
			pickLight = false;
			mapLight[pickLightNumber].throwLightUpdate(true);
			Destination[0] = At[0];
			Destination[1] = At[1];
			Destination[2] = At[2];

			startPos[0] = mapLight[pickLightNumber].returnXpos();
			startPos[1] = mapLight[pickLightNumber].returnYpos();
			startPos[2] = mapLight[pickLightNumber].returnZpos();

			ControlPoint[0] = (At[0] - tmpRect.x) / 2;
			ControlPoint[1] = startPos[1] + 40;
			ControlPoint[2] = (At[2] - tmpRect.z) / 2;
		}
	}
}

void S01Main::motion(bool pressed, int x, int y)
{
	if (!opening_camera_working) {
		//m_Camera.rotate(x, y, true);
		//get return motion pos
		drag_new_postion[0] = x;
		drag_new_postion[1] = y;

		if (pressed == false) {
			//   printf("old x : %f, old y : %f // new x : %f, new y : %f\n", drag_old_postion[0], drag_old_postion[1], drag_new_postion[0], drag_new_postion[1]);

			difference_new_old[0] = drag_old_postion[0] - drag_new_postion[0];
			difference_new_old[1] = drag_old_postion[1] - drag_new_postion[1];

			//difference_new_old nomalized
			//step 1 diffrence vetor size compute
			difference_size = sqrt(pow(difference_new_old[0], 2) + pow(difference_new_old[1], 2));

			//step2 re compute diffrence pos / vector size
			if (difference_size == 0) {
				difference_size = 0.0001;
			}
			difference_normal_pos[0] = difference_new_old[0] / difference_size;
			difference_normal_pos[1] = difference_new_old[1] / difference_size;

			//step3 nomal add to radian range 360
			result_degree[0] += difference_normal_pos[0];
			//if(result_degree[1] < 180)
			result_degree[1] -= difference_normal_pos[1];

			if ((result_degree[0] > 360) || (result_degree[0] < 0)) {
				result_degree[0] = 0;
			}
			if ((result_degree[1] > 180) || (result_degree[1] < 0)) {
				result_degree[1] = 0;
			}

			printf("normal: %f %f   size : %f \n", difference_new_old[0], difference_new_old[1], difference_size);
			printf("normal: %f %f   ", difference_normal_pos[0], difference_normal_pos[1]);
			printf("degree: %f %f \n \n", result_degree[0], result_degree[1]);
		}
		//연산이 끝난 후에 저장한다.
		drag_old_postion[0] = drag_new_postion[0];
		drag_old_postion[1] = drag_new_postion[1];

	}
}



void S01Main::update(float fDeltaTime)
{
	__t += 1;
	//camera at --> player going foward pos update
	// banana pos add
	
	//캐릭터 이동
	if (go_back) {

		tmpRect.x -= (sin((result_degree[0]) * 3.141592 / 180));
		tmpRect.z -= (cos((result_degree[0]) * 3.141592 / 180));

	}
	if (go_front) {
		tmpRect.x += (sin(result_degree[0] * 3.141592 / 180));
		tmpRect.z += (cos(result_degree[0] * 3.141592 / 180));
	}
	if (go_left) {

		tmpRect.x += (sin((result_degree[0] + 90) * 3.141592 / 180));
		tmpRect.z += (cos((result_degree[0] + 90) * 3.141592 / 180));
	}
	if (go_right) {

		tmpRect.x += (sin((result_degree[0] - 90) * 3.141592 / 180));
		tmpRect.z += (cos((result_degree[0] - 90) * 3.141592 / 180));
	}


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
				objectBox[saveBoxIndex[o]].movingZ((cos(result_degree[0] * 3.141592 / 180)));
		}
		else
		{
			tmpRect.z += (cos(result_degree[0] * 3.141592 / 180));

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
		mainCharacter.movingX(-(sin((result_degree[0] + 90) * 3.141592 / 180)));
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
				objectBox[saveBoxIndex[o]].movingX(-(sin((result_degree[0] + 90) * 3.141592 / 180)));
		}
		else
		{
			tmpRect.x += (sin((result_degree[0] + 90) * 3.141592 / 180));
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
		mainCharacter.movingZ((cos((result_degree[0]) * 3.141592 / 180)));
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
				objectBox[saveBoxIndex[o]].movingZ((cos((result_degree[0]) * 3.141592 / 180)));
		}
		else
		{

			tmpRect.z -= (cos((result_degree[0]) * 3.141592 / 180));

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
		mainCharacter.movingX((sin((result_degree[0] - 90) * 3.141592 / 180)));
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
				objectBox[saveBoxIndex[o]].movingX((sin((result_degree[0] - 90) * 3.141592 / 180)));
		}
		else
		{

			tmpRect.x -= (sin((result_degree[0] - 90) * 3.141592 / 180));

		}
		boxCheckCount = 0;
		check = FALSE;
		cycle = 0;
		tmpRect.xRate = 0;
		tmpRect.yRate = 0;
		tmpRect.zRate = 0;
	}


	bool lightLanding = false;
	for (int light = 0; light < LightCount; ++light) {
		lightLanding = false;
		i = 0;
		check = FALSE;
		if (mapLight[light].returnYpos() - 3 > 0 && mapLight[light].returnPickCheck() == false) {

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

	//조명을 집기 위한 공간

	for (int light = 0; light < LightCount; ++light) {
		if (pickLight == false && mapLight[light].returnThrowCheck() == false) {
			if (mapLight[light].returnXpos() - 10 < tmpRect.x && mapLight[light].returnXpos() + 10 > tmpRect.x
				&& mapLight[light].returnZpos() - 10 < tmpRect.z && mapLight[light].returnZpos() + 10 > tmpRect.z) {
				print("press 'E' you can pick up this light", 0, 100, 0);
				pickLightNumber = light;
				break;
			}
			else
				pickLightNumber = -1;

		}
	}

	for (int light = 0; light < LightCount; ++light) {
		if (mapLight[light].returnPickCheck() == true) {
			mapLight[light].pickSetPos(tmpRect.x, tmpRect.y + 15, tmpRect.z);
		}
	}

	//조명 던지는 공간

	for (int light = 0; light < LightCount; ++light) {
		if (mapLight[light].returnThrowCheck() == true) {
			float tmpx;
			float tmpy;
			float tmpz;

			tmpx = mapLight[light].returnXpos();
			tmpy = mapLight[light].returnYpos();
			tmpz = mapLight[light].returnZpos();

			opening_camera_Eye(&startPos[0], &startPos[1], &startPos[2], &Destination[0], &Destination[1], &Destination[2], &t, startPos[1] + 60, &tmpx, &tmpy, &tmpz);
			mapLight[light].settingPos(tmpx, tmpy, tmpz);
			t += 0.01f;
			if (t >= 1.f) {
				mapLight[light].throwLightUpdate(false);
				mapLight[light].pickUp(false);
				t = 0;
			}

			for (int k = 0; k < whatBox; ++k) {
				if (mapLight[light].returnXpos() >= objectBox[k].returnBoxCenterX() - 15 && mapLight[light].returnXpos() <= objectBox[k].returnBoxCenterX() + 15
					&& mapLight[light].returnYpos() >= objectBox[k].returnBoxCenterY() - 15 && mapLight[light].returnYpos() <= objectBox[k].returnBoxCenterY() + 15
					&& mapLight[light].returnZpos() >= objectBox[k].returnBoxCenterZ() - 15 && mapLight[light].returnZpos() <= objectBox[k].returnBoxCenterZ() + 15) {
					mapLight[light].throwLightUpdate(false);
					mapLight[light].pickUp(false);
					t = 0;
				}

				if (mapLight[light].returnXpos() - 3 < -60
					|| mapLight[light].returnXpos() + 3 > 60
					|| mapLight[light].returnZpos() - 3 < -70
					|| mapLight[light].returnZpos() + 3 > 70) {
					mapLight[light].throwLightUpdate(false);
					mapLight[light].pickUp(false);
					t = 0;
				}

			}
		}
	}



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
