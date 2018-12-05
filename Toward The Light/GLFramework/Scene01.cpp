#include "stdafx.h"
#include "Scene01.h"
#include "GLFramework.h"
#include "banana_draw.h"// �� �̻���ģ���ε�......................... �ٸ����� ������ �ȵ�����....
#include "LoadMap.h"
#include "Character.h"
#include "BananaSetting.h"
#include "camera_working.h"
// 11/30 ���� 7�ù� �����ʴ� �ٳ��� Ŭ������ 
static int whatBox;
static int LightCount;

static int angle = 0;

//�̵��� ���� �ӽ� ����
bool go_front;
bool go_left;
bool go_right;
bool go_back;

//�ڵ� 3���� ������ ���� ī�޶���� ���� �����ߴ� ����Ʈ �ٳ����� �԰�ʹ�

#define d_Sensitivity  3 //���� how many rotate camera

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

	//���� ������ ��ġ �о����
	red_right_cylinder.x = -50;
	red_right_cylinder.y = 100;
	red_right_cylinder.z = -100;

	//ī�޶� ��ġ�� �¾��մϴ�.
	//�ʱ� ī�޶� ��ġ�� �����մϴ�.
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

	dep = false;
	pickLight = false;
	pickLightNumber = -1;
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

	//ī�޶� ���� ---
	if (opening_camera_working) {//������ ������ ���۵Ǹ�
		
		if (opening_bezier_t >= 1) {
			opening_camera_working = false;
		}
		opening_bezier_t += 0.01f;
	
		opening_camera_Eye(&red_right_cylinder.x, &red_right_cylinder.y, &red_right_cylinder.z, &tmpRect.x, &tmpRect.y, &tmpRect.z, &opening_bezier_t, &Eye.x, &Eye.y, &Eye.z);
		opening_camera_At(&start_At.x, &start_At.y, &start_At.z, &end_At.x, &end_At.y, &end_At.z, &opening_bezier_t, &At.x, &At.y, &At.z);
	
		printf("opeing %f \n", Eye.y);
	}
	
	
	if (!opening_camera_working) { //������ ī�޶� ��ŷ�� false
		//eye �� ������ ���� �ٲ��.
		camera_moving_Eye(&tmpRect.x, &tmpRect.y, &tmpRect.z, &result_degree[0], &view_rotate[0], &view_rotate[1], &Eye.x, &Eye.y, &Eye.z);
		camera_moving_At(&tmpRect.x, &tmpRect.y, &tmpRect.z, &result_degree[0], &view_rotate[0], &view_rotate[1], &At.x, &At.y, &At.z);
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
			change_person_view_count++;
			if (change_person_view_count % 2 == 0) {
				//view_rotate[0] => �ּ� ���� (20) ī�޶��� ȸ���ݰ��� ��Ÿ���ϴ�. 
				// view_rotate[1] => (20) ī�޶��� ���̸� ��Ÿ���ϴ�. 
				view_rotate[0] = 60;
				view_rotate[1] = 50;

			}
			else if (change_person_view_count % 2 == 1) {         //3��Ī

				view_rotate[0] = -20;
				view_rotate[1] = 20;

			}
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
		//������ ���� �Ŀ� �����Ѵ�.
		drag_old_postion[0] = drag_new_postion[0];
		drag_old_postion[1] = drag_new_postion[1];

	}
}



void S01Main::update(float fDeltaTime)
{
	//camera at --> player going foward pos update
	// banana pos add
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
	printf("%f \n", result_degree[0]);
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

	if (keyA == true) {
		if (result_degree[0] >= 90 && result_degree[0] < 180) {
			//tmpRect.x += (sin(result_degree[0] * 3.141592 / 180));
			//tmpRect.z += (cos(result_degree[0] * 3.141592 / 180));
			dPress = false;
			sPress = false;
			wPress = true;
			aPress = true;
		}

		else if (result_degree[0] >= 180 && result_degree[0] < 270) {
			//tmpRect.x += (sin(result_degree[0] * 3.141592 / 180));
			//tmpRect.z += (cos(result_degree[0] * 3.141592 / 180));
			wPress = false;
			dPress = false;
			sPress = true;
			aPress = true;
		}
		else if (result_degree[0] >= 270 && result_degree[0] < 360) {
			//tmpRect.x += (sin(result_degree[0] * 3.141592 / 180));
			//tmpRect.z += (cos(result_degree[0] * 3.141592 / 180));
			wPress = false;
			aPress = false;
			sPress = true;
			dPress = true;
		}
		else if (result_degree[0] >= 0 && result_degree[0] < 90) {
			//tmpRect.x += (sin(result_degree[0] * 3.141592 / 180));
			//tmpRect.z += (cos(result_degree[0] * 3.141592 / 180));
			wPress = false;
			aPress = false;
			wPress = true;
			dPress = true;
		}
	}


	if (keyS == true) {
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

	if (keyD == true) {
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

	if (keyW == false && keyA == false && keyS == false && keyD == false) {
		wPress = false;
		aPress = false;
		sPress = false;
		dPress = false;
	}
	// ĳ���� ���� �̵�
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

	//���� ����
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

	//������ ���� ���� ����

	for (int light = 0; light < LightCount; ++light) {
		if (pickLight == false) {
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


	//���� �׸��� shadowMapping

	// ĳ���� ȸ��

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


void S01Main::LightSetting()
{
	//���� ����
	mapLight[0].DefaultLightPosSetting(30, 5, 60, 1);
	mapLight[1].DefaultLightPosSetting(-30, 45, 20, 1);

	mapLight[2].DefaultLightPosSetting(30, 5, 0, 0);
	mapLight[3].DefaultLightPosSetting(-30, 5, -40, 0);

	// ������ ���� ����

	mapLight[0].settingDiffuse(1.f, 0.f, 0.f, 0.6f);
	mapLight[1].settingDiffuse(1.f, 0.f, 0.f, 0.6f);

	mapLight[2].settingDiffuse(0.f, 0.f, 1.f, 0.6f);
	mapLight[2].settingDiffuse(0.f, 0.f, 1.f, 0.6f);

	//������ �ſ�ݻ� ���� ����
	mapLight[0].settingSpecu(1.f, 0.f, 0.f, 1.f);
	mapLight[1].settingSpecu(1.f, 0.f, 0.f, 1.f);

	mapLight[2].settingSpecu(0.f, 0.f, 1.f, 1.f);
	mapLight[3].settingSpecu(0.f, 0.f, 1.f, 1.f);


	// �ֺ���
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
