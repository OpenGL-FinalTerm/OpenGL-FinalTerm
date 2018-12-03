#pragma once
#include "GLScene.h"

/* UTILITIES */
#include "Model.h"
#include "Object.h"
#include "Camera.h"
#include "Character.h"
#include "BananaSetting.h"
/* ------------ */

class S04End :
	public GLScene
{
public:
	S04End();
	virtual ~S04End();

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
	int switch_sign = -1;
	int Time_count;

	Camera	m_Camera_end;
	Model	m_Model;
	Object	m_Title;
	tmp		tmpRect;
	Shape	banana;
};

