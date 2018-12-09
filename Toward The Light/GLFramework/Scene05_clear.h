#pragma once
#pragma once
#include "GLScene.h"

/* UTILITIES */
#include "Camera.h"
#include "Character.h"
#include "BananaSetting.h"
/* ------------ */

class S05End :
	public GLScene
{
public:
	S05End();
	virtual ~S05End();

	virtual void init();
	virtual void exit();
	virtual void reset();
	virtual void render();
	virtual void reshape(int w, int h);
	virtual void keyboard(int key, bool pressed, int x, int y, bool special);
	virtual void mouse(int button, bool pressed, int x, int y);
	virtual void motion(bool pressed, int x, int y);
	virtual void update(float fDeltaTime);
	virtual void drawHUD();
	virtual void HUD();

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

	float banana_cl[3];//banana color


	Vector3	Eye;
	Vector3	At;
	Camera	m_Camera_end;
	tmp		tmpRect;
	Shape	banana;

	int rotate;
	float ttt;
	Vector3 old_At_pos;
};

