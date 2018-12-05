#include "stdafx.h"
#include "HUD.h"
void HUD::Begin()
{
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_SMOOTH);
		int vPort[4];
		glGetIntegerv(GL_VIEWPORT, vPort);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
}

void HUD::End()
{
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glEnable(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
}

