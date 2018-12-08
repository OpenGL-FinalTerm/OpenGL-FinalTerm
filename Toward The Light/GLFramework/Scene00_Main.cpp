#include "stdafx.h"
#include "Scene00_Main.h"
#include "GLFramework.h"

S00Logo::S00Logo()
{
}

S00Logo::~S00Logo()
{
}

void S00Logo::init()
{

	m_Camera.setDistance(200.f);
	m_Camera.setPerspective(30.f, 0.125f, 3500.f);
	m_Camera.setSensitivity(1.f);

	for (int i = 0; i < 2; i++) {
		choose_map_box[i].x = DEF_WIN_WIDTH / 2 - 100 + (200 * i);
		choose_map_box[i].y = DEF_WIN_HEIGHT / 2;
		choose_map_box[i].z = 100;
	}

	Setting_button.x = 100;
	Setting_button.y = 100;
	Setting_button.z = 50;

	Setting_bt_color[0] = 0.f;
	Setting_bt_color[1] = 0.f;
	Setting_bt_color[2] = 0.5f;

	//사각형 읽어오기
	LoadMap(objectBox, tmpRect, 1);
	LoadMap(objectBox2, tmpRect, 2);


	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			color[i][j] = 0.8f;
		}
	}
	choose = 10;

}

void S00Logo::exit()
{
}

void S00Logo::reset()
{
}

void S00Logo::render()
{
	m_Camera.ready();
	//이미지 드로우
	//선택된건 확대해서 돌고있다.

		for (int i = 0; i < 65; ++i)
		{
				glPushMatrix();
				{
					glScalef(0.2, 0.2, 0.2);
					glTranslated(-300 + (600 * choose), -50, 0);
					glRotated(degree, 0.1, 1, 0);
				if (choose == 0) {
						objectBox[i].drawBox(20);
				}
				else if (choose == 1) {
					objectBox2[i].drawBox(20);
				}


					glTranslated(0, 50, 0);
					glBegin(GL_QUADS);
					glVertex3f(-choose_map_box[choose].z, 0, -choose_map_box[choose].z);
					glVertex3f(choose_map_box[choose].z, 0, -choose_map_box[choose].z);
					glVertex3f(choose_map_box[choose].z, 0, choose_map_box[choose].z);
					glVertex3f(-choose_map_box[choose].z, 0, choose_map_box[choose].z);
					glEnd();

				
				}
				glPopMatrix();
	
				//버튼 위 미니맵
				glPushMatrix();
				{
				
					glScaled(0.1, 0.1, 0.1);	
					glTranslated(-100 + objectBox[i].returnBoxCenterX(),  objectBox[i].returnBoxCenterZ(), objectBox[i].returnBoxCenterY() / 100);
					//glScaled(10, 10, 0);
					glColor3f(color[0][0], color[0][1], color[0][2]);
					glBegin(GL_QUADS);
					//glColor4f((float)129 / 255, (float)207 / 255, (float)233 / 255, 0.f);
					glVertex3f(0, 0, 0);
					glVertex3f(20, 0, 0);
					glVertex3f(20, 20, 0);
					glVertex3f(0, 20, 0);
					glEnd();
				}
				glPopMatrix();

				//버튼 위 미니맵
				glPushMatrix();
				{

					glScaled(0.1, 0.1, 0.1);
					glTranslated(100 + objectBox2[i].returnBoxCenterX(), objectBox2[i].returnBoxCenterZ(), objectBox2[i].returnBoxCenterY() / 100);
					//glScaled(10, 10, 0);
					glColor3f(color[1][0], color[1][1], color[1][2]);
					glBegin(GL_QUADS);
					//glColor4f((float)129 / 255, (float)207 / 255, (float)233 / 255, 0.f);
					glVertex3f(0, 0, 0);
					glVertex3f(20, 0, 0);
					glVertex3f(20, 20, 0);
					glVertex3f(0, 20, 0);
					glEnd();
				}
				glPopMatrix();

		}
	//일단 출력할 사각형 출력
	glPushMatrix();

	drawHUD();

	glPopMatrix();
}
void S00Logo::HUD()
{
	glColor3f(1.f, 1.f, 1.f);
	glPushMatrix();

	glDisable(GL_CULL_FACE);
	
	////첫번째 사각형
	//for (int i = 0; i < 2; i++) {
	//	glPushMatrix();
	//	glTranslated(choose_map_box[i].x, choose_map_box[i].y, 0);
	//	glColor3f(0.f + i, 1.f, 1.f);

	//	glBegin(GL_QUADS);
	//	glVertex3f(-choose_map_box[i].z / 2, -choose_map_box[i].z / 2, 0);
	//	glVertex3f(choose_map_box[i].z / 2, -choose_map_box[i].z / 2, 0);
	//	glVertex3f(choose_map_box[i].z / 2, choose_map_box[i].z / 2, 0);
	//	glVertex3f(-choose_map_box[i].z / 2, choose_map_box[i].z / 2, 0);
	//	glEnd();

	//	glPopMatrix();

	//}
	//선택
	print("Select Stage!", DEF_WIN_WIDTH / 2 - 35, DEF_WIN_HEIGHT - 100, 0);
	if (choose == 0) {
		print("Map 1", DEF_WIN_WIDTH / 2, DEF_WIN_HEIGHT - 600, 0);


	}
	else if (choose == 1) {
		print("Map 2", DEF_WIN_WIDTH / 2, DEF_WIN_HEIGHT - 600, 0);
	}
	else if (choose == 3) {
		print("Setting", DEF_WIN_WIDTH / 2, DEF_WIN_HEIGHT - 600, 0);
	}

	

	//셋팅창 선택 버튼
	glPushMatrix();
	glColor3f(Setting_bt_color[0], Setting_bt_color[1], Setting_bt_color[2]);
	glTranslatef(Setting_button.x, Setting_button.y, 0);
	
	glBegin(GL_QUADS);
	glVertex3f(-Setting_button.z/ 2, -Setting_button.z / 2, 0);
	glVertex3f(Setting_button.z / 2, -Setting_button.z / 2, 0);
	glVertex3f(Setting_button.z / 2, Setting_button.z / 2, 0);
	glVertex3f(-Setting_button.z / 2, Setting_button.z / 2, 0);
	glEnd();

	glPopMatrix();

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
}

void S00Logo::drawHUD()
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


void S00Logo::reshape(int w, int h)
{

}

void S00Logo::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
		switch (key)
		{
			//바로가기 
		case '1': m_Framework->toScene("1"); break;
		case '2': m_Framework->toScene("2"); break;
		case '3': m_Framework->toScene("3"); break;
		case '4': m_Framework->toScene("Ending"); break;
		case '5': m_Framework->toScene("Setting"); break;
		}
		
}

void S00Logo::mouse(int button, bool pressed, int x, int y)
{
	//선택하면 바로 넘어간다.
	if (button == GLUT_LEFT_BUTTON && choose == 0) {
		m_Framework->toScene("1");
	}
	else if (button == GLUT_LEFT_BUTTON && choose == 1){
			m_Framework->toScene("2");
	}
	else if (button == GLUT_LEFT_BUTTON && choose == 3) {
		m_Framework->toScene("Setting");
	}

}

void S00Logo::motion(bool pressed, int x, int y)
{
	//printf("%d , %d \n", x, y);
	select_map.x = x;
	select_map.y = y;

		if ((choose_map_box[0].x - (choose_map_box[0].z / 2) < select_map.x) && (select_map.x < (choose_map_box[0].x + choose_map_box[0].z / 2))
			&& (choose_map_box[0].y - (choose_map_box[0].z / 2) < select_map.y) && (select_map.y < (choose_map_box[0].y + choose_map_box[0].z / 2))) {
			choose = 0;
		
			color[0][0] = 1.f;
			color[0][1] = 1.f;
			color[0][2] = 1.f;

			color[1][0] = 0.5f;
			color[1][1] = 0.5f;
			color[1][2] = 0.5f;
		}
		else if ((choose_map_box[1].x - (choose_map_box[1].z / 2) < select_map.x) && (select_map.x < (choose_map_box[1].x + choose_map_box[1].z / 2))
			&& (choose_map_box[1].y - (choose_map_box[1].z / 2) < select_map.y) && (select_map.y < (choose_map_box[1].y + choose_map_box[1].z / 2))) {
			choose = 1;
			color[1][0] = 1.f;
			color[1][1] = 1.f;
			color[1][2] = 1.f;

			color[0][0] = 0.5f;
			color[0][1] = 0.5f;
			color[0][2] = 0.5f;

		}
		else {
			choose = 10;
			color[0][0] = 0.5f;
			color[0][1] = 0.5f;
			color[0][2] = 0.5f;

			color[1][0] = 0.5f;
			color[1][1] = 0.5f;
			color[1][2] = 0.5f;
		}
//	
		if (
			((Setting_button.x - (Setting_button.z / 2)) < select_map.x) && (select_map.x < (Setting_button.x + (Setting_button.z / 2))) &&
			((Setting_button.y - (Setting_button.z / 2)) < select_map.y) && (select_map.y < (Setting_button.y + (Setting_button.z / 2)))
			) {
			choose = 3;
			Setting_bt_color[0] = 1.f;
		}
		else {
			Setting_bt_color[0] = 0.f;
		}
		
//	printf("%f  c %d\n", select_map.y, choose);
	
}

void S00Logo::update(float fDeltaTime)

{
	degree = (degree + 1) % 360;
}
