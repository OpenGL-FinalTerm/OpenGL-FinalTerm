#pragma once
#include "GLScene.h"

/* UTILITIES */
#include "Model.h"
#include "Object.h"
#include "Camera.h"
/* ------------ */

class S00Logo :
	public GLScene
{
public:
	S00Logo();
	virtual ~S00Logo();

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

	Camera	m_Camera;
	Model	m_Model;
	Object	m_Title;
};

