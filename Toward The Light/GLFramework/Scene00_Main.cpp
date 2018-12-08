#include "stdafx.h"
#include "Scene00_Main.h"
#include "GLFramework.h"
#include "LoadMap.h"

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

	Map1BoxCount = LoadMap(Map1objectBox, Map1Banana, 1);
	Map2BoxCount = LoadMap(Map2objectBox, Map2Banana, 2);
	
	Map1LightCount = LoadLight(Map1Light, 1, Map1RedColumn);
	Map2LightCount = LoadLight(Map2Light, 2, Map2RedColumn);

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
	
	print("Press any key to start", 0, 0, -150);

	drawHUD();
}

void S00Logo::reshape(int w, int h)
{

}

void S00Logo::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
		switch (key)
		{
		case '1': m_Framework->toScene("1"); break;
		case '2': m_Framework->toScene("2"); break;
		case '4': m_Framework->toScene("Ending");break;
		}
		
}

void S00Logo::mouse(int button, bool pressed, int x, int y)
{
}

void S00Logo::motion(bool pressed, int x, int y)
{
}

void S00Logo::update(float fDeltaTime)

{
}

void S00Logo::HUD()
{
	glColor3f(1.f, 1.f, 1.f);
	glPushMatrix();

	//a미니맵 그리기
	//미니맵 배경 그리

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//미니맵 출
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);

	glPushMatrix();
	glPushMatrix();
	glTranslated(500, 350, 0);
	glBegin(GL_QUADS);
	glColor4f(1.f, 1.f, 1.f, 0.5);
	//glColor4f((float)129 / 255, (float)207 / 255, (float)233 / 255, 0.f);
	glVertex3f(0, 0, 0);
	glVertex3f(120, 0, 0);
	glVertex3f(120, 140, 0);
	glVertex3f(0, 140, 0);
	glEnd();
	glPopMatrix();

	for (int i = 0; i < Map1BoxCount; i++) {

		//정규화를 시켜준다.
		//sqrt(pow(difference_new_old[0], 2) + pow(difference_new_old[1], 2));

		glPushMatrix();
		glTranslated(550 + Map1objectBox[i].returnBoxCenterX(), 450 + Map1objectBox[i].returnBoxCenterZ(), Map1objectBox[i].returnBoxCenterY() / 100);
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

	for (int i = 0; i < Map1LightCount; i++) {

		//정규화를 시켜준다.
		//sqrt(pow(difference_new_old[0], 2) + pow(difference_new_old[1], 2));

		glPushMatrix();
		glTranslated(100 + Map1Light[i].returnXpos(), 100 + Map1Light[i].returnZpos(), Map1Light[i].returnYpos() / 100);
		glBegin(GL_QUADS);
		glColor3f(1.f, 1.f, 1.f);
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
		glTranslated(100 + Map1Banana.x, 100 + Map1Banana.z, 1);
		glBegin(GL_QUADS);
		glColor4f(1.f, 0.f, 0.f, 1);
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
	//
	glDisable(GL_BLEND);
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