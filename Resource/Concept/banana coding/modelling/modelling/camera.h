#pragma once
#pragma once
#include <GL/freeglut.h> 
#include <math.h>
#include <stdio.h>

#define PT 20//���� ���� ����
#define PI 3.141592 //����



struct DOUBLE_3D_POS
{
	double x, y, z;
};

class Cam
{
private:
	DOUBLE_3D_POS m_Eye = {};
	DOUBLE_3D_POS m_Center = {};
	DOUBLE_3D_POS m_Up = {};
	DOUBLE_3D_POS m_MoveEye = {};
	DOUBLE_3D_POS m_Angle = {};

public:
	Cam() // ������
	{
		m_Eye = { 0.0, 0.0, 60.0 };
		m_Center = { 0.0, 0.0, 0.0 };
		m_Up = { 0.0, 1.0, 0.0 };
		m_MoveEye = { 0.0, 0.0, 0.0 };
		m_Angle = { 0.0, 0.0, 0.0 };
	}
	void Init() // �ʱ�ȭ �Լ�
	{
		m_Eye = { 0.0, 0.0, 60.0 };
		m_Center = { 0.0, 0.0, 0.0 };
		m_Up = { 0.0, 1.0, 0.0 };
		m_MoveEye = { 0.0, 0.0, 0.0 };
		m_Angle = { 0.0, 0.0, 0.0 };
	}

	void drawCamera() // ī�޶� ��ġ�ϴ� �Լ�
	{
		//glPushMatrix();
		//glLoadIdentity(); // ������ ��ȯ ����� ������ķ� �ʱ�ȭ - �ð� ��ǥ�踦 �������� �ʱ�ȭ
		// ���� ��ȯ: ī�޶��� ��ġ ���� (�ʿ��� ���, �ٸ� ���� ���� ����)
		gluLookAt(m_Eye.x, m_Eye.y, m_Eye.z, m_Center.x, m_Center.y, m_Center.z, m_Up.x, m_Up.y, m_Up.z);
		glRotated(-m_Angle.x, 0.0, 1.0, 0.0);
		glRotated(m_Angle.y, 1.0, 0.0, 0.0);
		glRotated(m_Angle.z, 0.0, 0.0, 1.0);
		glTranslated(-m_MoveEye.x, -m_MoveEye.y, m_MoveEye.z);
		//glPopMatrix();
	}

public:
	void rotateEye(double x, double y, double z) // ī�޶� ȸ�� �Լ�
	{
		m_Angle.x += x;
		m_Angle.y += y;
		m_Angle.z += z;
		printf("%lf \n", m_Angle.x);
	}
	void moveEye(double x, double y, double z) // ī�޶� �̵� �Լ�
	{
		m_MoveEye.x += x;
		m_MoveEye.y += y;
		m_MoveEye.z += z;
	}
};
