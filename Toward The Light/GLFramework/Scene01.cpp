#include "stdafx.h"
#include "Scene01.h"
#include "GLFramework.h"
#include "banana_draw.h"// 애 이상한친구인데......................... 다른곳에 넣으면 안돌던데....
#include "LoadMap.h"
#include "Character.h"
#include "BananaSetting.h"


//코딩 3일차 오프닝 엔딩 카메라까지 전부 구현했다 델몬트 바나나가 먹고싶다

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

	////-----------------------------------------------------------
	//LightSetting();
	//DefaultBoxPosSetting();
	whatBox = LoadMap(objectBox, tmpRect, 1);
	LightCount = LoadLight(mapLight, 1, RedColumn);
	dep = false;
	glEnable(GL_LIGHTING);
	keyW = false;
	keyS = false;
	wPress = false;
	aPress = false;
	sPress = false;
	dPress = false;

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
	m_walkingSound.exit();
	//	glDisable(GL_LIGHT0);
	//	glDisable(GL_LIGHT1);
	//	glDisable(GL_LIGHT2);
	//	glDisable(GL_LIGHT3);
	////	glDisable(GL_LIGHT4);
	////	glDisable(GL_LIGHT5);
	////	glDisable(GL_LIGHT6);
	//	glDisable(GL_LIGHT7);
	glDisable(GL_LIGHTING);
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

	for (int i = 0; i < LightCount - 1; ++i)
		mapLight[i].drawLight(TRUE, i);

	mapLight[LightCount - 1].drawRedColunm();
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

	drawHUD();

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
			keyW = true;
			/*	if (result_degree[0] > 90 && result_degree[0] < 180) {
					aPress = false;
					sPress = false;
					wPress = true;
					dPress = true;
				}

				else if (result_degree[0] > 180 && result_degree[0] < 270) {
					sPress = false;
					dPress = false;
					wPress = true;
					aPress = true;
				}
				else if (result_degree[0] > 270 && result_degree[0] < 360) {
					wPress = false;
					dPress = false;
					sPress = true;
					aPress = true;
				}
				else if (result_degree[0] > 0 && result_degree[0] < 90) {
					wPress = false;
					aPress = false;
					sPress = true;
					dPress = true;
				}
	*/
			keyDown = true;
			break;

		case 'a':
			keyA = true;
			//aPress = true;
			////camera_deree[0] = Eye.x * cos(radian * 3.14) + Eye.z * -sin(radian * 3.14);
			////camera_deree[2] = Eye.x * sin(radian * 3.14) + Eye.z * cos(radian * 3.14);
			//keyDown = true;
			break;

		case 's':
			keyS = true;
			//sPress = true;
			//keyDown = true;
			break;

		case 'd':
			keyD = true;
			//dPress = true;
			//keyDown = true;
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
			if (catchBox == false && pickLight == false) {
				if (result_degree[0] >= 135 && result_degree[0] < 225) { //앞에있는거 wPress
					for (int i = 0; i < whatBox; ++i) {
						if (objectBox[i].returnBoxCenterX() - 10 < tmpRect.x + 5 && objectBox[i].returnBoxCenterX() + 10 > tmpRect.x - 5
							&& objectBox[i].returnBoxCenterZ() + 10 > tmpRect.z - 5 - 20 && objectBox[i].returnBoxCenterZ() - 10 < tmpRect.z + 5 - 20
							&& objectBox[i].returnBoxCenterY() - 10 < tmpRect.y + 5 && objectBox[i].returnBoxCenterY() + 10 > tmpRect.y - 5) {
							catchBox = true;
							boxIndex = i;
							objectBox[i].updateCatch(true);
							objectBox[i].catchBoxPos(tmpRect.x, tmpRect.y + 30, tmpRect.z);
							break;
						}
					}
				}
				else if (result_degree[0] >= 225 && result_degree[0] < 315) { // 왼쪽에 있는거 aPress
					for (int i = 0; i < whatBox; ++i) {
						if (objectBox[i].returnBoxCenterX() - 10 < tmpRect.x + 5 - 20 && objectBox[i].returnBoxCenterX() + 10 > tmpRect.x - 5 - 20
							&& objectBox[i].returnBoxCenterZ() + 10 > tmpRect.z - 5 && objectBox[i].returnBoxCenterZ() - 10 < tmpRect.z + 5
							&& objectBox[i].returnBoxCenterY() - 10 < tmpRect.y + 5 && objectBox[i].returnBoxCenterY() + 10 > tmpRect.y - 5) {
							catchBox = true;
							boxIndex = i;
							objectBox[i].updateCatch(true);
							objectBox[i].catchBoxPos(tmpRect.x, tmpRect.y + 20, tmpRect.z);
							break;
						}
					}
				}
				else if ((result_degree[0] >= 315 && result_degree[0] < 360) || (result_degree[0] >= 0 && result_degree[0] < 45)) {  // 뒤에있는거 sPress
					for (int i = 0; i < whatBox; ++i) {
						if (objectBox[i].returnBoxCenterX() - 10 < tmpRect.x + 5 && objectBox[i].returnBoxCenterX() + 10 > tmpRect.x - 5
							&& objectBox[i].returnBoxCenterZ() + 10 > tmpRect.z - 5 + 20 && objectBox[i].returnBoxCenterZ() - 10 < tmpRect.z + 5 + 20
							&& objectBox[i].returnBoxCenterY() - 10 < tmpRect.y + 5 && objectBox[i].returnBoxCenterY() + 10 > tmpRect.y - 5) {
							catchBox = true;
							boxIndex = i;
							objectBox[i].updateCatch(true);
							objectBox[i].catchBoxPos(tmpRect.x, tmpRect.y + 20, tmpRect.z);
							break;
						}
					}
				}
				else if (result_degree[0] >= 45 && result_degree[0] < 135) {  // 오른쪽에 있는거 dPress
					for (int i = 0; i < whatBox; ++i) {
						if (objectBox[i].returnBoxCenterX() - 10 < tmpRect.x + 5 + 20 && objectBox[i].returnBoxCenterX() + 10 > tmpRect.x - 5 + 20
							&& objectBox[i].returnBoxCenterZ() + 10 > tmpRect.z - 5 && objectBox[i].returnBoxCenterZ() - 10 < tmpRect.z + 5
							&& objectBox[i].returnBoxCenterY() - 10 < tmpRect.y + 5 && objectBox[i].returnBoxCenterY() + 10 > tmpRect.y - 5) {
							catchBox = true;
							boxIndex = i;
							objectBox[i].updateCatch(true);
							objectBox[i].catchBoxPos(tmpRect.x, tmpRect.y + 20, tmpRect.z);
							break;
						}
					}
				}
			}
			break;

		case 'e':
			if (change_person_view_count % 3 == 2) {
				radian -= 1;
			}
			break;

		case 'f':
		case 'F':
			if (catchBox != true) {
				for (int i = 0; i < LightCount - 1; ++i) {
					if (mapLight[i].returnPickCheck() == true)
						beforePick = true;
				}
			}

			if (pickLightNumber != -1 && beforePick == false) {
				mapLight[pickLightNumber].pickUp(true);
				pickLight = true;
			}

			if (catchBox != true) {
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
			}
			beforePick = false;
			break;

		}

	}
	else {
		if (key == 'w') {
			keyW = false;
			if (wPress == true)
				wPress = false;
			else if (aPress == true)
				aPress = false;
			else if (sPress == true)
				sPress = false;
			else if (dPress == true)
				dPress = false;
		}
		else if (key == 'a') {
			keyA = false;
			if (wPress == true)
				wPress = false;
			else if (aPress == true)
				aPress = false;
			else if (sPress == true)
				sPress = false;
			else if (dPress == true)
				dPress = false;
		}
		else if (key == 's') {
			keyS = false;
			if (wPress == true)
				wPress = false;
			else if (aPress == true)
				aPress = false;
			else if (sPress == true)
				sPress = false;
			else if (dPress == true)
				dPress = false;
		}
		else if (key == 'd') {
			keyD = false;
			if (wPress == true)
				wPress = false;
			else if (aPress == true)
				aPress = false;
			else if (sPress == true)
				sPress = false;
			else if (dPress == true)
				dPress = false;
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

		if (button == GLUT_LEFT_BUTTON && catchBox == true) {
			catchBox = false;
			objectBox[boxIndex].updateCatch(false);
			if (result_degree[0] >= 135 && result_degree[0] < 225)
				objectBox[boxIndex].catchBoxPos(tmpRect.x, tmpRect.y + 50, tmpRect.z - 20);
			else if (result_degree[0] >= 225 && result_degree[0] < 315)
				objectBox[boxIndex].catchBoxPos(tmpRect.x - 20, tmpRect.y + 50, tmpRect.z);
			else if (result_degree[0] >= 315 || result_degree[0] < 45)
				objectBox[boxIndex].catchBoxPos(tmpRect.x, tmpRect.y + 50, tmpRect.z + 20);
			else if (result_degree[0] >= 45 && result_degree[0] < 135)
				objectBox[boxIndex].catchBoxPos(tmpRect.x + 20, tmpRect.y + 50, tmpRect.z);
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

			if ((result_degree[0] < 360) && (result_degree[0] >= 0)) {
				result_degree[0] += int(difference_normal_pos[0] * 3);
			}
			else if (result_degree[0] >= 360)
				result_degree[0] = 0;
			else
				result_degree[0] = 359;

			if ((result_degree[1] > 360) || (result_degree[1] < -360)) {
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
	//camera at --> player going foward pos update
// banana pos add

	// 박스와 빨간 기둥이 충돌(?) 체크 해야함
	// 대략적인 위치 -> 모든 충돌이 일어난후(혹은 그냥 겹치기)

	__t += 1;
	foward_move.x = (sin(result_degree[0] * 3.141592 / 180));
	foward_move.z = (cos(result_degree[0] * 3.141592 / 180));

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
			if (objectBox[i].returnCatch() == false) {
				if (objectBox[i].returnBoxCenterX() - 10 < returnMainX() + 5 && objectBox[i].returnBoxCenterX() + 10 > returnMainX() - 5
					&& objectBox[i].returnBoxCenterZ() + 10 > returnMainZ() - 5 && objectBox[i].returnBoxCenterZ() - 10 < returnMainZ() + 5
					&& returnMainY() + 5 > objectBox[i].returnBoxCenterY() - 10 && returnMainY() - 5 < objectBox[i].returnBoxCenterY() + 10) {
					down = TRUE;
					jump = FALSE;
					tmpRect.jumpCount = 0;
					tmpRect.y -= 1;
				}
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
			if (objectBox[i].returnCatch() == false) {
				if (objectBox[i].returnBoxCenterX() - 10 < returnMainX() + 5 && objectBox[i].returnBoxCenterX() + 10 > returnMainX() - 5
					&& objectBox[i].returnBoxCenterZ() + 10 > returnMainZ() - 5 && objectBox[i].returnBoxCenterZ() - 10 < returnMainZ() + 5
					&& tmpRect.y - 5 < objectBox[i].returnBoxCenterY() + 20 && !(tmpRect.y + 5 < objectBox[i].returnBoxCenterY())) {
					down = FALSE;
					tmpcheck = true;

					if (depthCheck >= 60) {
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
		}

		if (tmpRect.y > 10 && tmpcheck == false) {
			tmpRect.y -= 1;
			depthCheck++;
		}

		if (tmpRect.y <= 10 && tmpcheck == false) {
			down = FALSE;
			if (depthCheck >= 60) {
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
	//printf("%f \n", result_degree[0]);
	if (keyW == true) {
		if (result_degree[0] >= 90 && result_degree[0] < 180) {
			//tmpRect.x += (sin(result_degree[0] * 3.141592 / 180));
			//tmpRect.z += (cos(result_degree[0] * 3.141592 / 180));
			aPress = false;
			sPress = false;
			wPress = true;
			dPress = true;
		}

		else if (result_degree[0] >= 180 && result_degree[0] < 270) {
			//tmpRect.x += (sin(result_degree[0] * 3.141592 / 180));
			//tmpRect.z += (cos(result_degree[0] * 3.141592 / 180));
			sPress = false;
			dPress = false;
			wPress = true;
			aPress = true;
		}
		else if (result_degree[0] >= 270 && result_degree[0] < 360) {
			//tmpRect.x += (sin(result_degree[0] * 3.141592 / 180));
			//tmpRect.z += (cos(result_degree[0] * 3.141592 / 180));
			wPress = false;
			dPress = false;
			sPress = true;
			aPress = true;
		}
		else if (result_degree[0] >= 0 && result_degree[0] < 90) {
			//tmpRect.x += (sin(result_degree[0] * 3.141592 / 180));
			//tmpRect.z += (cos(result_degree[0] * 3.141592 / 180));
			wPress = false;
			aPress = false;
			sPress = true;
			dPress = true;
		}
	}

	if (keyS == true) {
		foward_move.x *= -1;
		foward_move.z *= -1;
		if (result_degree[0] >= 90 && result_degree[0] < 180) {
			//tmpRect.x += (sin(result_degree[0] * 3.141592 / 180));
			//tmpRect.z += (cos(result_degree[0] * 3.141592 / 180));
			aPress = true;
			sPress = true;
			wPress = false;
			dPress = false;
		}

		else if (result_degree[0] >= 180 && result_degree[0] < 270) {
			//tmpRect.x += (sin(result_degree[0] * 3.141592 / 180));
			//tmpRect.z += (cos(result_degree[0] * 3.141592 / 180));
			sPress = true;
			dPress = true;
			wPress = false;
			aPress = false;
		}
		else if (result_degree[0] >= 270 && result_degree[0] < 360) {
			//tmpRect.x += (sin(result_degree[0] * 3.141592 / 180));
			//tmpRect.z += (cos(result_degree[0] * 3.141592 / 180));
			wPress = true;
			dPress = true;
			sPress = false;
			aPress = false;
		}
		else if (result_degree[0] >= 0 && result_degree[0] < 90) {
			//tmpRect.x += (sin(result_degree[0] * 3.141592 / 180));
			//tmpRect.z += (cos(result_degree[0] * 3.141592 / 180));
			wPress = true;
			aPress = true;
			sPress = false;
			dPress = false;
		}
	}

	if (keyW == false && keyA == false && keyS == false && keyD == false) {
		wPress = false;
		aPress = false;
		sPress = false;
		dPress = false;
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
		if (objectBox[k].returnCatch() == false) {
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
	}

	if (catchBox == true) {
		objectBox[boxIndex].catchBoxPos(tmpRect.x, tmpRect.y + 30, tmpRect.z);
	}

	check = FALSE;
	if (wPress == true) {
		cycle = 0;
		count = 0;
		boxCheckCount = 0;
		i = 0;
		angle = 180;
		mainCharacter.movingZ(foward_move.z);
		tmpRect.z += foward_move.z;
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
					objectBox[saveBoxIndex[o]].movingZ(foward_move.z);
			}
			else
				tmpRect.z -= foward_move.z;
		}
		else
			tmpRect.z -= foward_move.z;


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
		tmpRect.x += foward_move.x;
		mainCharacter.movingX(foward_move.x);
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
					objectBox[saveBoxIndex[o]].movingX(foward_move.x);
			}

			else
				tmpRect.x -= foward_move.x;
		}
		else
			tmpRect.x -= foward_move.x;

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
		tmpRect.z += foward_move.z;
		mainCharacter.movingZ(foward_move.z);
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
					objectBox[saveBoxIndex[o]].movingZ(foward_move.z);
			}
			else
				tmpRect.z -= foward_move.z;
		}
		else
			tmpRect.z -= foward_move.z;

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
		tmpRect.x += foward_move.x;
		mainCharacter.movingX(foward_move.x);
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

			if (m_walkingSound.playing() == false)
				m_walkingSound.play();
			if (boxCheckCount < 3) {
				for (int o = 0; o < boxCheckCount; ++o)
					objectBox[saveBoxIndex[o]].movingX(foward_move.x);
			}
			else
				tmpRect.x -= foward_move.x;
		}
		else
			tmpRect.x -= foward_move.x;

		boxCheckCount = 0;
		check = FALSE;
		cycle = 0;
		tmpRect.xRate = 0;
		tmpRect.yRate = 0;
		tmpRect.zRate = 0;
	}

	//조명 낙하
	bool lightLanding = false;
	for (int light = 0; light < LightCount - 1; ++light) {
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

	for (int light = 0; light < LightCount - 1; ++light) {
		if (pickLight == false && mapLight[light].returnThrowCheck() == false) {
			if (mapLight[light].returnXpos() - 10 < tmpRect.x && mapLight[light].returnXpos() + 10 > tmpRect.x
				&& mapLight[light].returnZpos() - 10 < tmpRect.z && mapLight[light].returnZpos() + 10 > tmpRect.z) {
				print("press 'F' you can pick up this light", 0, 100, 0);
				messageOn = true;
				pickLightNumber = light;
				break;
			}
			else {
				pickLightNumber = -1;
				messageOn = false;
			}
		}
	}

	for (int light = 0; light < LightCount - 1; ++light) {
		if (mapLight[light].returnPickCheck() == true) {
			messageOn = false;
			mapLight[light].pickSetPos(tmpRect.x, tmpRect.y + 15, tmpRect.z);
		}
	}

	//조명 던지는 공간

	for (int light = 0; light < LightCount - 1; ++light) {
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


	//조명 그림자 shadowMapping

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

void S01Main::HUD()
{
	//GLuint tex;


		//IDtmp[0] = LoadTexture("Test.bmp", 150, 150);
	glColor3f(1.f, 1.f, 1.f);
	glPushMatrix();

	if (messageOn == true)
		print("press 'F' you can pick up this light", 630, 900 / 2, 0);

	//a미니맵 그리기
	//미니맵 배경 그리

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//미니맵 출
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);

	glPushMatrix();
	glTranslated(50, 40, 0);
	glBegin(GL_QUADS);
	glColor4f(1.f, 1.f, 1.f, 0.5);
	//glColor4f((float)129 / 255, (float)207 / 255, (float)233 / 255, 0.f);
	glVertex3f(0, 0, 0);
	glVertex3f(120, 0, 0);
	glVertex3f(120, 140, 0);
	glVertex3f(0, 140, 0);
	glEnd();
	glPopMatrix();

	for (int i = 0; i < whatBox; i++) {

		//정규화를 시켜준다.
		//sqrt(pow(difference_new_old[0], 2) + pow(difference_new_old[1], 2));

		glPushMatrix();
		glTranslated(100 + objectBox[i].returnBoxCenterX(), 100 + objectBox[i].returnBoxCenterZ(), objectBox[i].returnBoxCenterY() / 100);
		glBegin(GL_QUADS);
		//glColor4f((float)129 / 255, (float)207 / 255, (float)233 / 255, 0.f);
		glColor4f(1.f, 1.f, 1.f, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(20, 0, 0);
		glVertex3f(20, 20, 0);
		glVertex3f(0, 20, 0);
		glEnd();
		glPopMatrix();
	}

	for (int i = 0; i < LightCount - 1; i++) {

		//정규화를 시켜준다.
		//sqrt(pow(difference_new_old[0], 2) + pow(difference_new_old[1], 2));

		glPushMatrix();
		glTranslated(100 + mapLight[i].returnXpos(), 100 + mapLight[i].returnZpos(), mapLight[i].returnYpos() / 100);
		glBegin(GL_QUADS);
		if (mapLight[i].returnType() == 1)
			glColor3f(1.f, 0.f, 0.f);
		else
			glColor3f(0.f, 0.f, 1.f);
		//glColor4f((float)129 / 255, (float)207 / 255, (float)233 / 255, 0.f);
		glVertex3f(0, 0, 0);
		glVertex3f(10, 0, 0);
		glVertex3f(10, 10, 0);
		glVertex3f(0, 10, 0);
		glEnd();
		glPopMatrix();
	}
	//바나나 출력
	glPushMatrix();
	{
		glTranslated(100 + tmpRect.x, 100 + tmpRect.z, 1);
		glBegin(GL_QUADS);
		glColor3f((float)129 / 255, (float)207 / 255, (float)233 / 255);
		//glColor4f((float)129 / 255, (float)207 / 255, (float)233 / 255, 0.f);
		glVertex3f(0, 0, 0);
		glVertex3f(10, 0, 0);
		glVertex3f(10, 10, 0);
		glVertex3f(0, 10, 0);
		glEnd();
	}
	glPopMatrix();
	//	printf("%d \n",mapLight[0].returnYpos());
	glPopMatrix();//그리기 끝
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	//
	glDisable(GL_BLEND);
	glPopMatrix();
}

void S01Main::drawHUD()
{
	glMatrixMode(GL_PROJECTION);
	//glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 1500.0, 900.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	glLoadIdentity();

	HUD();
	glDisable(GL_TEXTURE_2D);
	//glMatrixMode(GL_PROJECTION);
	//glPopMatrix();
	//glMatrixMode(GL_MODELVIEW);
	//glPopMatrix();
}

GLuint S01Main::LoadTexture(const char * filename, int width_1, int height_1)
{
	GLuint texture;
	int width, height;
	unsigned char * data;
	FILE * file;

	// 파일 열기
	fopen_s(&file, filename, "rb");
	if (file == NULL) return 0;
	width = width_1;
	height = height_1;
	data = (unsigned char *)malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	// 색상결정
	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;
	}

	// 이후 PDF동일
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Modulate로 함
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	// 나는 밉맵으로 만듬
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}