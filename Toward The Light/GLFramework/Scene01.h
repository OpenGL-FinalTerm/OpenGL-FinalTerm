#pragma once
#include "GLScene.h"

/* UTILITIES */
#include "Model.h"
#include "NormalObject.h"
#include "Camera.h"
#include "SoundPlayer.h"
/* ------------ */

class S01Main :
	public GLScene
{
public:
	S01Main();
	virtual ~S01Main();

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
	float			rX, rY, rZ;
	int				tX, tY;
	Camera			m_Camera;
	NormalObject	m_Plane;
	NormalObject    m_Sphere;

	bool s;
};