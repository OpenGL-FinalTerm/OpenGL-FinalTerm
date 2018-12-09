#include "stdafx.h"
#include "Scene05_clear.h"
#include "GLFramework.h"
#include "banana_draw.h"
#include "Character.h"
#include "camera_working.h"


S05End::S05End()
{
}

S05End::~S05End()
{
}

void S05End::init()
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

	banana_cl[0] = 3;
	banana_cl[1] = 40;
	banana_cl[2] = 255;

	//버튼
	return_button.x = 600;
	return_button.y = DEF_WIN_HEIGHT - 200;
	return_button_size.x = 50;
	return_button_size.y = 50;


	//버튼
	main_button.x = 900;
	main_button.y = DEF_WIN_HEIGHT - 200;
	main_button_size.x = 50;
	main_button_size.y = 50;
}

void S05End::exit()
{
}

void S05End::reset()
{
}


void S05End::render()
{
	m_Camera_end.ready();


	//카메라 연산
	ending_camera_Eye(&tmpRect.x, &tmpRect.y, &tmpRect.z, &camera_degree[0], &camera_size[0], &camera_size[1], &Eye.x, &Eye.y, &Eye.z);
	ending_camera_At(&old_At_pos.x, &old_At_pos.y, &old_At_pos.z, &tmpRect.x, &tmpRect.y, &tmpRect.z, &ttt, &At.x, &At.y, &At.z);

	glPushMatrix();
	banana_draw(tmpRect.x, tmpRect.y + 5, tmpRect.z, 0.5, IDLE, banana.rot.degree, result_degree[0], banana_cl[0], banana_cl[1], banana_cl[2]);
	glPopMatrix();

	//카메라 렌더링
	m_Camera_end.setEye(Eye);
	m_Camera_end.setTarget(At);
	
	drawHUD();

	glColor3f(1.f, 1.f, 1.f);
	print("Clear!", 0, 40, 0);

}

void S05End::reshape(int w, int h)
{

}

void S05End::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
		switch (key)
		{
		case 'r': m_Framework->toScene("Main"); break;
		case 'R': m_Framework->toScene("Main"); break;
		}

}

void S05End::mouse(int button, bool pressed, int x, int y)
{
	//선택하면 바로 넘어간다.
	if (button == GLUT_LEFT_BUTTON && return_button_b == TRUE && pressed == true) {
		m_Framework->toScene("Main");
	}
	/*else if (button == GLUT_LEFT_BUTTON && main_button_b == TRUE && pressed == true) {
		m_Framework->toScene("Main");
	}*/
}

void S05End::motion(bool pressed, int x, int y)
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

	/*if (((main_button.x - (main_button_size.x / 2)) < select_map.x) && (select_map.x < ((main_button.x + (main_button_size.x / 2)))) &&
		((main_button.y - (main_button_size.y / 2)) < select_map.y) && (select_map.y < ((main_button.y + (main_button_size.y / 2))))) {
		main_button_b = true;
		printf("true \n");
	}
	else {
		main_button_b = false;
	}*/
}

void S05End::update(float fDeltaTime)
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

void S05End::HUD()
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

	//glPushMatrix();
	//glTranslatef(main_button.x, main_button.y, -0.5);
	////선그리기
	//glLineWidth(10);
	//glBegin(GL_LINE_STRIP);
	//glVertex3f(main_button_size.x / 2, main_button_size.y / 2, 0);
	//glVertex3f(-main_button_size.x / 2, main_button_size.y / 2, 0);
	//glVertex3f(-main_button_size.x / 2, -main_button_size.y / 2, 0);
	//glVertex3f(main_button_size.x / 2, -main_button_size.y / 2, 0);
	//glVertex3f(main_button_size.x / 2, 0, 0);
	//glEnd();

	//glBegin(GL_TRIANGLES);
	//glVertex3f(-main_button_size.x / 4 + 20, -main_button_size.y / 2, 0);
	//glVertex3f(main_button_size.x / 4 + 20, -main_button_size.y / 2, 0);
	//glVertex3f(20, -main_button_size.y/ 2, 0);
	//glEnd();

	//glPopMatrix();



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

void S05End::drawHUD()
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