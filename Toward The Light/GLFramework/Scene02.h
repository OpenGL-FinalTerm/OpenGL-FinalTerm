#pragma once
#include "GLScene.h"

/* UTILITIES */
#include "Model.h"
#include "NormalObject.h"
#include "Camera.h"

class S02Main : public GLScene
{
public:
	S02Main();
	virtual ~S02Main();

	virtual void init();
	virtual void exit();
	virtual void reset();
	virtual void render();
	virtual void reshape(int w, int h);
	virtual void keyboard(int key, bool pressed, int x, int y, bool special);
	virtual void mouse(int button, bool pressed, int x, int y);
	virtual void motion(bool pressed, int x, int y);
	virtual void update(float fDeltaTime);

private:
	float			tX = 0, tY = 0;
	float			oX = 0, oY = 0;
	float			rY = 0;
	Camera			m_Camera;
	NormalObject	m_Plane;
	NormalObject    m_Box[3];NormalObject    m_wBox[3];

	float			secX = 0, secY = 0;
	float			thdX = 0, thdZ = 0;
	bool direction = false;
};
