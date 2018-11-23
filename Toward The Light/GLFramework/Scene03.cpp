#include "stdafx.h"
#include "Scene03.h"
#include "GLFramework.h"

S03Main::S03Main()
{
}

S03Main::~S03Main()
{
}

void S03Main::init()
{
	m_Camera.setDistance(4000.f);
	m_Camera.setPerspective(45.f, 0.125f, 7'000.f);
	m_Camera.setSensitivity(10.f);

	m_Plane.setModel("Cube", 3000, false);
	m_Plane.setColor(Vector3(0.8f, 0.8f, 0.8f));
	m_Plane.move(0.f, -700.f, 0.f);
	m_Plane.scale(1.f, 0.01f, 1.f);

	Air.setModel(200);
	Air.setColor({ 0.f,0.f,0.f });
	Air.m_qrRotation.rotate(-180.f / (3.14 * 36),Air.m_qrRotation.rotatePoint({ 0.f,1.f,0.f }));
	for (int i = 0; i < 3; i++)
	{
		m_Box[i].setModel("Cube", 500, false);
		m_Box[i].setColor(Vector3(0.1f * (i + 1), 0.2f * (i + 1), 0.3f * (i + 1)));
	}
	m_Box[0].move(0.f, -500.f, 0.f);
	m_Box[0].scale(1.5f, 0.9f, 1.f);
	m_Box[1].move(0.f, -130.f, 0.f);
	m_Box[1].scale(0.2f, 0.7f, 0.2f);
	m_Box[2].move(0.f, +150.f, 0.f);
	m_Box[2].scale(0.1f, 0.6f, 0.1f);

	m_Sphere.setModel("Sphere", 200, true);
	m_Sphere.move(0.f, -500.f, -500.f);

	Tree[0].setModel("Cube", 230, false);
	Tree[1].setModel("Cube", 230, false);
	Tree[0].move(-1000.f, -565.f, -1000.f);
	Tree[1].move(-1000.f, -335.f, -1000.f);
	Tree[0].setColor({ 0.4f,0.25f,0.08f });
	Tree[1].setColor({ 0.2f,0.8f,0.12f });


	_rX = 0, _rY = 0, _rZ = 0;
	_tX = 0, _tY = 0;

	anim = 0;
	spin = 0;
	ad = true;
	s = 0;

	onair = false;
	reverse = false;
}

void S03Main::exit()
{
	m_Plane.move(0.f, 700.f, 0.f);

	m_Box[0].setPosition(0.f, 0.f, 0.f);

	m_Box[1].setPosition(0.f, 0.f, 0.f);

	m_Box[2].setPosition(0.f, 0.f, 0.f);

	m_Sphere.setPosition(0.f, 0.f, 0.f);
	Tree[0].setPosition(0.f, 0.f, 0.f);
	Tree[1].setPosition(0.f, 0.f, 0.f);

	Air.m_qrRotation.resetQuaternion();

	tX = 0, tY = 0;
	oX = 0, oY = 0;
	rY = 0;
	secX = 0, secY = 0;
	thdX = 0, thdZ = 0;
	direction = 0;
	_direction = 0;
}

void S03Main::reset()
{
}

void S03Main::Triangles()
{
	glColor3f(0.7f, 0.2f, 0.f);
	glBegin(GL_TRIANGLES);						//tree
	{
		glVertex3f(-1500.f, -660.f, -1500.f);
		glVertex3f(-1500.f, -660.f, -200.f);
		glVertex3f(-200.f, -660.f, -1500.f);
	}
	glEnd();
	glColor3f(0.f, 0.7f, 0.2f);
	glBegin(GL_TRIANGLES);						//press
	{
		glVertex3f(1500.f, -660.f, -1500.f);
		glVertex3f(1500.f, -660.f, -200.f);
		glVertex3f(200.f, -660.f, -1500.f);
	}
	glEnd();
	glColor3f(0.2f, 0.f, 0.7f);
	glBegin(GL_TRIANGLES);						//running
	{
		glVertex3f(-1500.f, -660.f, 1500.f);
		glVertex3f(-1500.f, -660.f, 200.f);
		glVertex3f(-200.f, -660.f, 1500.f);
	}
	glEnd();
	glColor3f(0.7f, 0.2f, 0.7f);
	glBegin(GL_TRIANGLES);						//iron
	{
		glVertex3f(1500.f, -660.f, 1500.f);
		glVertex3f(1500.f, -660.f, 200.f);
		glVertex3f(200.f, -660.f, 1500.f);
	}
	glEnd();
	glColor3f(1.f, 1.f, 1.f);
}

void S03Main::Treez()
{
	Tree[0].render();
	Tree[1].render();
}

void S03Main::Pressz()
{
	glColor3f(0.f, 0.f, 1.f);
	glPushMatrix();
	{
		glTranslatef(1100.f, -650.f, -1100.f);
		glScalef(1.f, 0.1f, 1.f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(1100.f, -650.f, -1100.f);
		glScalef(0.4f, 0.4f, 0.7f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(1300.f, -500.f, -1300.f);
		glScalef(0.1f, 1.f, 0.1f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(900.f, -500.f, -1300.f);
		glScalef(0.1f, 1.f, 0.1f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(1100.f, -470.f + (20 - anim) * 10, -1250.f);
		glScalef(1.5f, 0.1f, 0.1f);
		glColor3f(0.4f, 0.4f, 0.4f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(1400.f, -470.f + (20 - anim) * 10, -1250.f);
		glScalef(0.1f, 0.3f, 0.3f);
		glColor3f(1.f, 0.f, 0.f);
		glutSolidSphere(350, 8, 8);
		glColor3f(1.f, 1.f, 1.f);
		glutWireSphere(350, 8, 8);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(800.f, -470.f + (20 - anim) * 10, -1250.f);
		glScalef(0.1f, 0.3f, 0.3f);
		glColor3f(1.f, 0.f, 0.f);
		glutSolidSphere(350, 8, 8);
		glColor3f(1.f, 1.f, 1.f);
		glutWireSphere(350, 8, 8);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();

}

void S03Main::Runningz()
{
	glColor3f(1.f, 0.f, 0.f);

	glPushMatrix();
	{
		glTranslatef(-1100.f, -600.f, 1100.f);
		glRotatef(90, 0.f, 1.f, 0.f);
		glScalef(0.7f, 0.1f, 2.4f);
		glRotatef(-spin, 0.f, 0.f, 1.f);
		glutSolidTorus(50, 350, 18, 18);
		glColor3f(1.f, 1.f, 1.f);
		glutWireTorus(60, 370, 18, 18);
		glColor3f(1.f, 0.f, 0.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-1300.f, -500.f, 1300.f);
		glScalef(0.1f, 1.f, 0.1f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(1.f, 0.f, 0.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-900.f, -500.f, 1300.f);
		glScalef(0.1f, 1.f, 0.1f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-1130.f, -430.f, 1150.f);
		glTranslatef(0.f, 100.f, 0.f);
		glRotatef(anim - 20, 1.f, 0.f, 0.f);
		glTranslatef(0.f, -100.f, 0.f);
		glScalef(0.1f, 1.f, 0.1f);
		glutSolidCube(200);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(205);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-1030.f, -430.f, 1150.f);
		glTranslatef(0.f, 100.f, 0.f);
		glRotatef(40 - anim - 20, 1.f, 0.f, 0.f);
		glTranslatef(0.f, -100.f, 0.f);
		glScalef(0.1f, 1.f, 0.1f);
		glutSolidCube(200);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(205);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
}

void S03Main::Ironz()
{
	glPushMatrix();
	{
		glTranslatef(1300.f, -500.f, 1100.f);
		glScalef(0.1f, 1.f, 0.1f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(900.f, -500.f, 1100.f);
		glScalef(0.1f, 1.f, 0.1f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(1100.f, -320.f, 1100.f);
		glScalef(1.2f, 0.1f, 0.1f);
		glColor3f(0.4f, 0.4f, 0.4f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(1150.f, -430.f, 1100.f);
		glTranslatef(0.f, 100.f, 0.f);
		glRotatef(spin, 1.f, 0.f, 0.f);
		glTranslatef(0.f, -100.f, 0.f);
		glScalef(0.07f, 0.7f, 0.07f);
		glutSolidCube(200);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(205);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(1050.f, -430.f, 1100.f);
		glTranslatef(0.f, 100.f, 0.f);
		glRotatef(spin, 1.f, 0.f, 0.f);
		glTranslatef(0.f, -100.f, 0.f);
		glScalef(0.07f, 0.7f, 0.07f);
		glutSolidCube(200);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(205);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(1100.f, -530.f, 1100.f);
		glTranslatef(0.f, 200.f, 0.f);
		glRotatef(spin, 1.f, 0.f, 0.f);
		glTranslatef(0.f, -200.f, 0.f);
		glScalef(1.f, 1.f, 0.3f);
		glutSolidCube(100);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(105);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
}

void S03Main::Circlez()
{
	int sic[3];
	int cic[3];
	for (int i = 0; i < 3; i++)
	{
		if (reverse)
		{
			sic[i] = sin(((spin / 12) * 12 + (i + 1) * 10) / 360.f * 3.1415) * 1400.f;
			cic[i] = cos(((spin / 12) * 12 + (i + 1) * 10) / 360.f * 3.1415) * 1400.f;

		}
		else
		{
			sic[i] = sin(((spin / 12) * 12 - (i + 1) * 10) / 360.f * 3.1415) * 1400.f;
			cic[i] = cos(((spin / 12) * 12 - (i + 1) * 10) / 360.f * 3.1415) * 1400.f;
		}
		glPushMatrix();
		{
			glTranslatef(sic[i], 0.f, cic[i]);
			glRotatef(1.0, 0.f, 1.f, 0.f);
			glTranslatef(-70.f*sin(spin), 0.f, -70.f*cos(spin));
			glColor3f(0.25f, 0.25f, 0.25f);
			glutSolidSphere((3 - i) * 15,12,12);
			glTranslatef(140.f*sin(spin), 0.f, 140.f*cos(spin));
			glColor3f(0.25f, 0.25f, 0.25f);
			glutSolidSphere((3 - i) * 15, 12, 12);
			glRotatef(-1.0, 0.f, 1.f, 0.f);
		}glPopMatrix();
	}
}

void S03Main::render()
{
	m_Camera.ready();

	glTranslatef(0.f, 20.f * tY, 0.f);
	glTranslatef(20.f * tX, 0.f, 0.f);

	if (onair)
	{
		m_Camera.setEye({ si,-50.f,co });
		m_Camera.setTarget({ 0.f,-400.f,0.f });
	}

	m_Plane.render();
	//
	//오브젝트들(원래는 클래스로 빼야댐)
	Triangles();
	Treez();
	Pressz();
	Runningz();
	Ironz();

	Air.render();
	Circlez();
	//

	m_Sphere.render();

	glPushMatrix();
	{
		glTranslatef(oX*0.4, -1020.f*0.4, (2000.f + oY)*0.4);
		glScalef(0.4, 0.4, 0.4);


		//충돌처리?

		//glRotatef(rY, 0.f, 1.f, 0.f);
		m_Box[0].render();
		glTranslatef(0.f, -300.f, 0.f);
		//glRotatef(secX, 1.f, 0.f, 0.f);
		glTranslatef(0.f, 300.f, 0.f);
		//glRotatef(secY, 0.f, 1.f, 0.f);
		m_Box[1].render();
		//glRotatef(thdX, 1.f, 0.f, 0.f);
		//glRotatef(thdZ, 0.f, 0.f, 1.f);
		m_Box[2].render();
	}glPopMatrix();
}

void S03Main::reshape(int w, int h)
{
}

void S03Main::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
	{
		switch (key)
		{
		case 'w':direction = 3; break;
		case 'a':direction = 2; break;
		case 's':direction = 1; break;
		case 'd':direction = 0; break;

		case 'i':_direction = 1; break;
		case 'j':_direction = 2; break;
		case 'k':_direction = 3; break;
		case 'l':_direction = 0; break;

		case ' ': m_Framework->toScene("Main"); break;
		case 'o': break;
		case '+': m_Camera.setDistance(m_Camera.getDistance() - 5); break;
		case '-': m_Camera.setDistance(m_Camera.getDistance() + 5); break;
		case 'z': tY++; break;
		case 'x': tX--; break;
		case 'c': tY--; break;
		case 'v': tX++; break;
		case '0': s = (s + 1) % 2; break;
		case '/': reverse = (reverse + 1) % 2;
			Air.m_qrRotation.rotate(-360.f / (3.14 * 36), Air.m_qrRotation.rotatePoint({ 0.f,1.f,0.f })); break;
		case '\\':
			if (onair)
			{
				onair = false;
				m_Camera.init();
				m_Camera.setDistance(4000.f);
				m_Camera.setPerspective(45.f, 0.125f, 7'000.f);
				m_Camera.setSensitivity(10.f);
			}
			else
			{
				onair = true;
				m_Camera.resetRotation();
			}
			break;
		}
	}
}

void S03Main::mouse(int button, bool pressed, int x, int y)
{

}

void S03Main::motion(bool pressed, int x, int y)
{
	if (!onair)
	{
		if (s)
			m_Camera.rotate(x, 0.f, pressed);
		else
			m_Camera.rotate(0.f, y, pressed);
	}
}

void S03Main::clap()
{
	if (abs(m_Sphere.m_v3Position.x) > 600 && abs(m_Sphere.m_v3Position.z) > 600)
	{
		switch (_direction)
		{
		case 0:_direction = 2; break;
		case 1:_direction = 3; break;
		case 2:_direction = 0; break;
		case 3:_direction = 1; break;
		}
	}

	if (abs(oX*0.4) > 550 && abs((2000.f + oY)*0.4) > 550)
	{
		switch (direction)
		{
		case 0:direction = 2; break;
		case 1:direction = 3; break;
		case 2:direction = 0; break;
		case 3:direction = 1; break;
		}
	}
	if (sqrt(
		(abs(m_Sphere.m_v3Position.x - 1500.f) - abs(oX*0.4 - 1500.f)) * (abs(m_Sphere.m_v3Position.x - 1500.f) - abs(oX*0.4 - 1500.f))
		+
		(abs(m_Sphere.m_v3Position.z - 1500.f) - abs((2000.f + oY)*0.4 - 1500.f)) * (abs(m_Sphere.m_v3Position.z - 1500.f) - abs((2000.f + oY)*0.4 - 1500.f)))
		< 300)
	{
		switch (_direction)
		{
		case 0:_direction = 2; direction = 0; break;
		case 1:_direction = 3; direction = 3; break;
		case 2:_direction = 0; direction = 2; break;
		case 3:_direction = 1; direction = 1; break;
		}
	}
}

void S03Main::update(float fDeltaTime)
{
	clap();

	si = sin(spin / 360.f * 3.1415) * 1400.f;
	co = cos(spin / 360.f * 3.1415) * 1400.f;
	if (onair)
	{
		m_Camera.setEye({ si*2.f,1500.f,co*2.f });
		m_Camera.setTarget({ si,0.f,co });
	}
	Air.update(fDeltaTime);
	Air.setPosition({ si,0.f,co });
	if (spin == 720)
	{
		spin = 0;
		Air.m_qrRotation.resetQuaternion();
		Air.m_qrRotation.rotate(-180.f / (3.14 * 36), Air.m_qrRotation.rotatePoint({ 0.f,1.f,0.f }));

	}
	if (reverse)
		Air.m_qrRotation.rotate(1.f / (3.1415 * 36), Air.m_qrRotation.rotatePoint({ 0.f,1.f,0.f }));
	else
		Air.m_qrRotation.rotate(-1.f / (3.1415 * 36), Air.m_qrRotation.rotatePoint({ 0.f,1.f,0.f }));
	switch (direction)
	{
	case 0:
		oX += 1000 * fDeltaTime;
		if (oX > 3300)
			direction = 2;
		break;
	case 1:
		oY += 1000 * fDeltaTime;
		if (oY > 1500)
			direction = 3;
		break;
	case 2:
		oX -= 1000 * fDeltaTime;
		if (oX < -3300)
			direction = 0;
		break;
	case 3:
		oY -= 1000 * fDeltaTime;
		if (oY < -5000)
			direction = 1;
		break;
	}

	switch (_direction)
	{
	case 0:
		if (_rZ > -255) { m_Sphere.move(2.7076 * 200 / 36, 0.f, 0.f); _rZ -= 2.707; }
		m_Sphere.m_qrRotation.rotate(0.1, m_Sphere.m_qrRotation.rotatePoint({ 0, 0, 1 }));
		if (_rZ < -252)
			_direction = 2;
		break;
	case 1:
		if (_rX < 200) { _rX += 2.7076; m_Sphere.move(0.f, 0.f, -2.707 * 200 / 36); }
		m_Sphere.m_qrRotation.rotate(0.1, m_Sphere.m_qrRotation.rotatePoint({ 1, 0, 0 }));
		if (_rX > 197)
			_direction = 3;
		break;
	case 2:
		if (_rZ < 255) { m_Sphere.move(-2.7076 * 200 / 36, 0.f, 0.f); _rZ += 2.707; }
		m_Sphere.m_qrRotation.rotate(-0.1, m_Sphere.m_qrRotation.rotatePoint({ 0, 0, 1 }));
		if (_rZ > 252)
			_direction = 0;
		break;
	case 3:
		if (_rX > -310) { _rX -= 2.7076; m_Sphere.move(0.f, 0.f, 2.707 * 200 / 36); }
		m_Sphere.m_qrRotation.rotate(-0.1, m_Sphere.m_qrRotation.rotatePoint({ 1, 0, 0 }));
		if (_rX < -307)
			_direction = 1;
		break;
	}
	if (ad)
		anim += 1;
	else
		anim -= 1;
	if (anim >= 40)
		ad = false;
	else if (anim < 1)
		ad = true;
	if (reverse)
		spin--;
	else
		spin++;
	Tree[1].scale(1.f + (anim / 60.f), 1.f + (anim / 60.f), 1.f + (anim / 60.f));

}
