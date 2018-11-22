#include "stdafx.h"
#include "Robot.h"

Robot::Robot()
{
	spin = 180;
	dir = false;

	robotX = 0; robotY = -300; robotZ = 0;
	rotateDir = 0;
	jump = false;
	jumpdir = false;
}

Robot::~Robot()
{

}

void Robot::setPosition(float x, float y, float z)
{

}

void Robot::move(float fDistanceX, float fDistanceY, float fDistanceZ)
{
	if (abs(robotZ) + abs(robotX) > 1800)
	{
		robotX /= 1.01f;
		robotZ /= 1.01f;
		jump = true;
	}
	if (jump == false)
	{
		switch (rotateDir)
		{
		case 0:
			if (robotZ < 1300)
				robotZ += fDistanceZ;
			break;
		case 1:
			if (robotX < 1300)
				robotX += fDistanceZ;
			break;
		case 2:
			if (robotZ > -1300)
				robotZ -= fDistanceZ;
			break;
		case 3:
			if (robotX > -1300)
				robotX -= fDistanceZ;
			break;
		}
	}
}

void Robot::update(float fDeltaTime)
{
	if (dir)
	{
		if (spin < 220)
		{
			spin++;
		}
		else
			dir = false;
	}
	else
	{
		if (spin > 140)
		{
			spin--;
			
		}
		else
			dir = true;
	}
	if (jump)
	{
		if (jumpdir == false)
		{
			robotY += 500 * fDeltaTime;
		}
		else
		{
			robotY -= 500 * fDeltaTime;
		}
		if (robotY > 0)
			jumpdir = true;
		if (robotY < -300)
		{
			jump = false; jumpdir = false;
		}
	}
	move(0.f,0.f,200 * fDeltaTime);
}

void Robot::render()
{
	glPushMatrix();
	{
		glTranslatef(robotX, robotY, robotZ);
		glRotatef(90.f * rotateDir, 0.f, 1.f, 0.f);
		//个烹
		glPushMatrix();
		{
			glTranslatef(0.f, -100.0f, 0.f);
			glColor3f(1.f, 0.f, 1.f);
			glutSolidCube(200);
			glColor3f(1.f, 1.f, 1.f);
			glutWireCube(200);
		}glPopMatrix();
		//赣府
		glPushMatrix();
		{
			glColor3f(1.f, 1.f, 0.f);
			glTranslatef(0.f, 50.0f, 0.f);
			glutSolidCube(100);
		}glPopMatrix();
		//内
		glPushMatrix();
		{
			glColor3f(0.f, 1.f, 1.f);
			glTranslatef(0.f, 50.0f, 50.f);
			glutSolidCube(30);
		}glPopMatrix();

		//8
		glPushMatrix();
		{

			glColor3f(1.f, 0.f, 0.f);
			glTranslatef(-125.f, 50.0f, 0.f);

			glTranslatef(0.f, -100.f, 0.f);
			glRotatef(spin, 1.f, 0.f, 0.f);
			glTranslatef(0.f, 100.f, 0.f);

			glScalef(0.2f, 2.f, 0.2f);
			glutSolidCube(100);
		}glPopMatrix();
		glPushMatrix();
		{
			glColor3f(0.f, 1.f, 0.f);
			glTranslatef(125.f, 50.0f, 0.f);

			glTranslatef(0.f, -100.f, 0.f);
			glRotatef(360 - spin, 1.f, 0.f, 0.f);
			glTranslatef(0.f, 100.f, 0.f);

			glScalef(0.2f, 2.f, 0.2f);
			glutSolidCube(100);
		}glPopMatrix();

		//促府
		glPushMatrix();
		{
			glColor3f(0.f, 0.f, 1.f);
			glTranslatef(-45.f, -125.0f, 0.f);


			glTranslatef(0.f, -100.f, 0.f);
			glRotatef(360 - spin, 1.f, 0.f, 0.f);
			glTranslatef(0.f, 100.f, 0.f);

			glScalef(0.2f, 2.f, 0.2f);
			glutSolidCube(100);
		}glPopMatrix();
		glPushMatrix();
		{
			glColor3f(0.f, 0.5f, 0.5f);
			glTranslatef(45.f, -125.0f, 0.f);

			glTranslatef(0.f, -100.f, 0.f);
			glRotatef(spin, 1.f, 0.f, 0.f);
			glTranslatef(0.f, 100.f, 0.f);

			glScalef(0.2f, 2.f, 0.2f);
			glutSolidCube(100);
		}glPopMatrix();
	}glPopMatrix();
}

void Robot::setDir(int set)
{
	rotateDir = set;
}
