#include "stdafx.h"
#include "GLScene.h"
#include "GLFramework.h"

GLFramework * m_Framework = nullptr;

void GLScene::print(std::string str, float x, float y, float z) const
{
	glPushMatrix();
	float sz = static_cast<float>(str.size());
	glRasterPos3f(x - sz*(5.f / 6.f), y, z);
	for (size_t s = 0; s < str.size(); s++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[s]);
	glPopMatrix();
}

void GLScene::drawLoadingScreen()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	loading();

	glutSwapBuffers();
}

void GLScene::loading()
{
	print("Loading...", 0, 0, -250);	
}
