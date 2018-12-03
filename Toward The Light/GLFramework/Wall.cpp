#include "Wall.h"

void wall()
{

	glColor3f(0.f, 0.f, 0.f);
	//왼쪽벽
	glBegin(GL_QUADS);
	glVertex3f(-60, 0, -70);
	glVertex3f(-60, 0, 70);
	glVertex3f(-60, 160, 70);
	glVertex3f(-60, 160, -70);
	glEnd();	

	//오른쪽벽
	glBegin(GL_QUADS);
	glVertex3f(60, 0, -70);
	glVertex3f(60, 0, 70);
	glVertex3f(60, 160, 70);
	glVertex3f(60, 160, -70);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-60, 0, -70);
	glVertex3f(-60, 160, -70);
	glVertex3f(60, 160, -70);
	glVertex3f(60, 0, -70);
	glEnd();
}