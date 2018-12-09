#include "stdafx.h"
#include "Scene04_Ending.h"
#include "GLFramework.h"
#include "banana_draw.h"
#include "Character.h"
#include "camera_working.h"


S04End::S04End()
{
}

S04End::~S04End()
{
}

void S04End::init()
{
	m_Camera_end.init();
	m_Camera_end.setDistance(200.f);
	m_Camera_end.setPerspective(30.f, 0.125f, 3500.f);
	m_Camera_end.setSensitivity(1.f);
	rotate = 0;
	camera_size[0] = 500;


	tmpRect.x = 0;
	tmpRect.y = 0;
	tmpRect.z = 0;
	ending_animation_bool = false;

	banana_cl[0] = 50;
	banana_cl[1] = 20;
	banana_cl[2] = 50;


	//버튼
	return_button.x = 600;
	return_button.y = DEF_WIN_HEIGHT - 200;
	return_button_size.x = 50;
	return_button_size.y = 50;

}

void S04End::exit()
{
}

void S04End::reset()
{
}


void S04End::render()
{
	m_Camera_end.ready();
	

	//카메라 연산
	ending_camera_Eye(&tmpRect.x, &tmpRect.y, &tmpRect.z, &camera_degree[0], &camera_size[0], &camera_size[1], &Eye.x, &Eye.y, &Eye.z);
	ending_camera_At(&old_At_pos.x ,&old_At_pos.y , &old_At_pos.z, &tmpRect.x, &tmpRect.y, &tmpRect.z, &ttt, &At.x, &At.y, &At.z);

	glPushMatrix();
	banana_draw(tmpRect.x, tmpRect.y + 5, tmpRect.z, 0.5, IDLE, banana.rot.degree, result_degree[0], banana_cl[0], banana_cl[1], banana_cl[2]);
	glPopMatrix();

	//카메라 렌더링
	m_Camera_end.setEye(Eye);
	m_Camera_end.setTarget(At);
	drawHUD();
	glColor3f(1.f, 1.f, 1.f);
	print("Banana is Dead", 0, 40, 0);

}

void S04End::reshape(int w, int h)
{

}

void S04End::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
		switch (key)
		{
		case 'r': m_Framework->toScene("Main"); break;
		case 'R': m_Framework->toScene("Main"); break;
		}

}

void S04End::mouse(int button, bool pressed, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && return_button_b == TRUE && pressed == true) {
		m_Framework->toScene("Main");
	}
}

void S04End::motion(bool pressed, int x, int y)
{
	select_map.x = x;
	select_map.y = y;

	if (((return_button.x - (return_button_size.x / 2)) < select_map.x) && (select_map.x < ((return_button.x + (return_button_size.x / 2)))) &&
		((return_button.y - (return_button_size.y / 2)) < select_map.y) && (select_map.y < ((return_button.y + (return_button_size.y / 2))))) {
		return_button_b = true;
		printf("true \n");
	}
	else {
		return_button_b = false;
	}

}

void S04End::update(float fDeltaTime)
{
	//엔딩이 나올때는 줌인 한 후에 회전하면서 바나나 가르기키 
	camera_degree[0] += 1;
	if (ending_animation_bool) {
		
		if (camera_size[0] >= 100) {
			camera_size[0] -= 1;
		}
		if (camera_size[0] == 100) {
			ending_animation_bool = true;
		}
	}
	else {
		if (camera_size[0] >= 50) {
			camera_size[0] -= 1;
			camera_pos[1] += 1;
		}
		if (camera_size[0] == 50) {
			ending_animation_bool = false;
		}
	}

	Time_count++;
	if (Time_count % 20 == 0)
	{
		switch_sign *= -1;
	}
	banana.rot.degree += 0.1f * switch_sign;
}

void S04End::HUD()
{
	glColor3f(1.f, 1.f, 1.f);
	glPushMatrix();

	glPushMatrix();
	glTranslatef(return_button.x, return_button.y, -0.5);
	glBegin(GL_QUADS);
	glVertex3f(-return_button_size.x / 2, -return_button_size.y / 2, 0);
	glVertex3f(return_button_size.x / 2, -return_button_size.y / 2, 0);
	glVertex3f(return_button_size.x / 2, return_button_size.y / 2, 0);
	glVertex3f(-return_button_size.x / 2, return_button_size.y / 2, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(-return_button_size.x, 0, 0);
	glVertex3f(return_button_size.x, 0, 0);
	glVertex3f(0, -return_button_size.y, 0);
	glEnd();

	glPopMatrix();


	

	//HUD를 그린다.
	glPushMatrix();
	glTranslatef(select_map.x, select_map.y, 1);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex3f(-10, -10, 0);
	glVertex3f(10, -10, 0);
	glVertex3f(10, 10, 0);
	glVertex3f(-10, 10, 0);
	glEnd();
	glPopMatrix();



	glPopMatrix();


	
}

void S04End::drawHUD()
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
