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

	float		difference_new_old[2] = {}; // between drag_old postion and drag new postion --> old - new
	float		difference_size = 1.f;
	float		difference_normal_pos[2] = {};
	float		result_degree[2] = {};
	float		assist_rotation = 1;
	float		view_rotate[2] = {};


private:
	int switch_sign = -1;
	int Time_count;

	float camera_size[3];//회전반경
	float camera_degree[3];//회전 각도
	float camera_pos[3];
	bool ending_animation_bool = true;

	Vector3	Eye;
	Vector3	At;
	Camera	m_Camera_end;
	Model	m_Model;
	Object	m_Title;
	tmp		tmpRect;
	Shape	banana;
};

