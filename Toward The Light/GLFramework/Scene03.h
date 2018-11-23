#pragma once
#include "GLScene.h"

/* UTILITIES */
#include "Model.h"
#include "NormalObject.h"
#include "Camera.h"
#include "AirPlane.h"

class S03Main : public GLScene
{
public:
	S03Main();
	virtual ~S03Main();

	virtual void init();
	virtual void exit();
	virtual void reset();
			void Triangles();
			void Treez();
			void Pressz();
			void Runningz();
			void Ironz();
			void Circlez();
			virtual void render();
	virtual void reshape(int w, int h);
	virtual void keyboard(int key, bool pressed, int x, int y, bool special);
	virtual void mouse(int button, bool pressed, int x, int y);
	virtual void motion(bool pressed, int x, int y);
	void clap();
	virtual void update(float fDeltaTime);

private:
	Camera			m_Camera;
	NormalObject	m_Plane;
	NormalObject    m_Sphere;
	NormalObject    m_Box[3];

	NormalObject	Tree[2];

	float			tX = 0, tY = 0;

	//
	float			oX = 0, oY = 0;
	float			rY = 0;
	float			secX = 0, secY = 0;
	float			thdX = 0, thdZ = 0;
	int direction = 0;
	//
	float			_rX, _rY, _rZ;
	int				_tX, _tY;
	int _direction = 0;
	//
	bool ad;
	bool s;
	float anim;
	int spin;

	AirPlane Air;
	float si, co;
	bool onair = false;
	bool reverse = false;
};

