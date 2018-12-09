#include "stdafx.h"
#include "GLFramework.h"
#include "banana_draw.h"// 애 이상한친구인데......................... 다른곳에 넣으면 안돌던데....
#include "LoadMap.h"
#include "Character.h"
#include "BananaSetting.h"
#include "Scene_Setting.h"

//날름 포인터 다이스키

S05Setting::S05Setting()
{
}

S05Setting::~S05Setting()
{
}

void S05Setting::init()
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
	
	whatBox = LoadMap(objectBox, tmpRect, 2);
	//LightCount = LoadLight(mapLight, 2);
	Exit_button.x = 300;
	Exit_button.y = DEF_WIN_HEIGHT - 200;
	Exit_button_size.x = 200;
	Exit_button_size.y = 50;
	for (int i = 0; i < scroll_num; ++i) {
		if( i >= 2)
			scroll_bar[i].x = 700 + 400;
		else
			scroll_bar[i].x = 700;
		scroll_bar[i].y = DEF_WIN_HEIGHT  - (i%2)*100 - 200;
		scroll_bar_size[i].x = 200;
		scroll_bar_size[i].y = 10;

		scroll_bt[i].x = 0.1;
		scroll_bt[i].y = 0.1;

		scroll_bt_size[i].x = 20;
		scroll_bt_size[i].y = 40;

		scroll_bt_b[i] = false;
		scroll_motion_b[i] = false;

	}
	
}

void S05Setting::exit()
{
	select_map.x = 1000;
	select_map.y = 0;
	
	m_SoundPlayer.exit();
}

void S05Setting::reset()
{
	m_SoundPlayer.play();
}

float S05Setting::returnMainX()
{
	return tmpRect.x + tmpRect.xRate;
}

float S05Setting::returnMainY()
{
	return tmpRect.y + tmpRect.yRate;
}

float S05Setting::returnMainZ()
{
	return tmpRect.z + tmpRect.zRate;
}

void S05Setting::render()
{
	glPushMatrix();
	

	drawHUD();

	glPopMatrix();
}


void S05Setting::reshape(int w, int h)
{

}




void S05Setting::keyboard(int key, bool pressed, int x, int y, bool special)
{
	

	if (pressed)
	{
		switch (key)
		{
		case 'w':
			break;

		case 'a':
		
			break;

		case 's':
		
			break;

		case 'd':
	
			break;
		//환경설정 나오기
		case VK_ESCAPE: m_Framework->toScene("Main"); break;
		}

	}
	
}

void S05Setting::mouse(int button, bool pressed, int x, int y)
{
	if (pressed) {
		if (button == GLUT_LEFT_BUTTON && Exit_button_b == TRUE && pressed == true) {
			m_Framework->toScene("Main");
		}
		for (int i = 0; i < scroll_num; ++i) {
			if (button == GLUT_LEFT_BUTTON && pressed == TRUE) {
				if (
					(((scroll_bt[i].x + scroll_bar[i].x - (scroll_bt_size[i].x)) < select_map.x) && (select_map.x < ((scroll_bt[i].x + scroll_bar[i].x + (scroll_bt_size[i].x)))) &&
					((scroll_bt[i].y + scroll_bar[i].y - (scroll_bt_size[i].y)) < select_map.y) && (select_map.y < ((scroll_bt[i].y + scroll_bar[i].y + (scroll_bt_size[i].y)))))
					) {
					scroll_bt_b[i] = true;
					
				}
				else {
					scroll_bt_b[i] = false;
				}
			}
			
		}


	}
}

void S05Setting::motion(bool pressed, int x, int y)
{
	select_map.x = x;
	select_map.y = y;

	if (((Exit_button.x -(Exit_button_size.x / 2)) < select_map.x) && (select_map.x < ((Exit_button.x + (Exit_button_size.x / 2)))) &&
		((Exit_button.y - (Exit_button_size.y / 2)) < select_map.y) &&( select_map.y < ((Exit_button.y + (Exit_button_size.y / 2))))) {
		Exit_button_b = true;
	
	}
	else {
		Exit_button_b = false;
	}
	//스크롤바
	for (int i = 0; i < scroll_num; ++i) {
		if (scroll_bt_b[i] && pressed == true) {
			if ((-scroll_bar_size[i].x / 2 <= scroll_bt[i].x) && (scroll_bt[i].x <= scroll_bar_size[i].x / 2))
			{
				if (old_mouse_pos.x < select_map.x)
				{
					scroll_bt[i].x += 1;
				}
				else
				{
					scroll_bt[i].x -= 1;
				}
			}
		}
		if (
			(((scroll_bt[i].x + scroll_bar[i].x - (scroll_bt_size[i].x)) < select_map.x) && (select_map.x < ((scroll_bt[i].x + scroll_bar[i].x + (scroll_bt_size[i].x)))) &&
			((scroll_bt[i].y + scroll_bar[i].y - (scroll_bt_size[i].y)) < select_map.y) && (select_map.y < ((scroll_bt[i].y + scroll_bar[i].y + (scroll_bt_size[i].y)))))
			) {
			scroll_motion_b[i] = true;
			
		}
		else {
			scroll_motion_b[i] = false;
		}

		//정규화 시킨 다음에 값을 얻어낸다.
		scroll_result[i] = 1 + scroll_bt[i].x / (sqrt(pow(scroll_bar_size[i].x, 2) + pow(1, 2)));
	
	}
	
	//old 좌표에 다시 저장한다
	old_mouse_pos.x = select_map.x;
	old_mouse_pos.y = select_map.y;

}


void S05Setting::update(float fDeltaTime)
{
	//camera at --> player going foward pos update
// banana pos add


}



void S05Setting::LightSetting()
{
	
}

void S05Setting::camera_install(int x, int y) {


}

void S05Setting::HUD()
{
	glColor3f(1.f, 1.f, 1.f);
	glPushMatrix();
	glPushMatrix();
	glTranslatef(Exit_button.x, Exit_button.y, -0.5);
	glBegin(GL_QUADS);
	glVertex3f(-Exit_button_size.x / 2, -Exit_button_size.y / 2, 0);
	glVertex3f(Exit_button_size.x / 2, -Exit_button_size.y / 2, 0);
	glVertex3f(Exit_button_size.x / 2, Exit_button_size.y / 2, 0);
	glVertex3f(-Exit_button_size.x / 2, Exit_button_size.y / 2, 0);
	glEnd();

	glColor3f(1.f, 0.f, 0.f);
	print("EXIT", 200, DEF_WIN_HEIGHT - 100 / 2, 0);

	//HUD를 그린다.
	glPushMatrix();
	glTranslatef(select_map.x, select_map.y, 1);
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(-10, -10, 0);
	glVertex3f(10, -10, 0);
	glVertex3f(10, 10, 0);
	glVertex3f(-10, 10, 0);
	glEnd();
	glPopMatrix();

	glPopMatrix();



	//스크롤 바
	//스크롤바 문구
	for (int i = 0; i < scroll_num; ++i) {
		glColor3f(1, 0, 0);
		print("Dellmonte", scroll_bar[i].x - scroll_bar_size[i].x, scroll_bar[i].y, 0);
		glPushMatrix();
		glTranslatef(scroll_bar[i].x, scroll_bar[i].y, -0.5);
		glBegin(GL_QUADS);
		glVertex3f(-scroll_bar_size[i].x / 2, -scroll_bar_size[i].y / 2, 0);
		glVertex3f(scroll_bar_size[i].x / 2, -scroll_bar_size[i].y / 2, 0);
		glVertex3f(scroll_bar_size[i].x / 2, scroll_bar_size[i].y / 2, 0);
		glVertex3f(-scroll_bar_size[i].x / 2, scroll_bar_size[i].y / 2, 0);
		glEnd();
		//스크롤 버튼
		glPushMatrix();
		glTranslatef(scroll_bt[i].x, scroll_bt[i].y, -0.2);
		glBegin(GL_QUADS);
		glVertex3f(-scroll_bt_size[i].x / 2, -scroll_bt_size[i].y / 2, 0);
		glVertex3f(scroll_bt_size[i].x / 2, -scroll_bt_size[i].y / 2, 0);
		glVertex3f(scroll_bt_size[i].x / 2, scroll_bt_size[i].y / 2, 0);
		glVertex3f(-scroll_bt_size[i].x / 2, scroll_bt_size[i].y / 2, 0);
		glEnd();
		glPopMatrix();
		glPopMatrix();

		if (scroll_motion_b[i]) {
			glPushMatrix();
			glColor3f(1, 1, 1);
			glTranslatef(scroll_bar[i].x, scroll_bar[i].y, -0.5);
			glBegin(GL_LINES);
			glVertex3f(-scroll_bar_size[i].x / 2 - 10, -scroll_bar_size[i].y - 20, 0);
			glVertex3f(scroll_bar_size[i].x / 2 + 10, -scroll_bar_size[i].y - 20, 0);
			glVertex3f(scroll_bar_size[i].x / 2 + 10, scroll_bar_size[i].y + 20, 0);
			glVertex3f(-scroll_bar_size[i].x / 2 - 10, scroll_bar_size[i].y + 20, 0);
			glEnd();
			glPopMatrix();
		}
	}
	
}

void S05Setting::drawHUD()
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

GLuint S05Setting::LoadTexture(const char * filename, int width_1, int height_1)
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