#pragma once
#include "GLScene.h"

/* UTILITIES */
#include "Model.h"
#include "NormalObject.h"
#include "Camera.h"
#include "SoundPlayer.h"
#include "BoxObject.h"
#include "Light.h"
#include "BananaSetting.h"
#include "Character.h"
#include "Wall.h"

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
	virtual void DefaultBoxPosSetting();
	virtual void LightSetting();
	virtual float returnMainX();
	virtual float returnMainY();
	virtual float returnMainZ();

private:
	float		tX = 0, tY = 0;
	float		oX = 0, oY = 0;
	float		rY = 0;
	float		radian;
	
	int			switch_sign = -1;
	int			Time_count;
	int			depthCheck = 0;
	
	bool		dep = false; // 시작할때 낙하하는것도 체크하여서 만들어둠
	bool		person_view_1 = false;
	bool		person_view_3 = false;
	bool		person_view_mouse = true;
	bool		keyW = false;
	bool		keyA = false;
	bool		keyS = false;
	bool		keyD = false;
	bool		keyDown = false;
	bool		pickLight = false;

	int			pickLightNumber = -1;
	int			drag_old_postion[2] = {};
	int			drag_new_postion[2] = {};
	int			change_person_view_count = 0;
	int			move_Eye[3];
	int			__t = 0;
	
	float		camera_deree[3];
	float		difference_new_old[2] = {}; // between drag_old postion and drag new postion --> old - new
	float		difference_size = 1.f;
	float		difference_normal_pos[2] = {};
	float		result_degree[2] = {};
	float		assist_rotation = 1;
	float		view_rotate[2] = {};

	bool		wPress = false;
	bool		aPress = false;
	bool		sPress = false;
	bool		dPress = false;
	
	Vector2			foward;//player move
	Vector3			Eye;
	Vector3			At;
	Vector3			foward_move; //나아가야하는 방향
	Camera			m_Camera;
	NormalObject	m_Plane;
	NormalObject    m_Box[3];
	NormalObject    m_wBox[3];
	SoundPlayer		m_SoundPlayer;
	SoundPlayer		m_walkingSound;
	Box				objectBox[65];
	Box				mainCharacter;
	Light			mapLight[100];
	Shape			banana;
	tmp				tmpRect;
};
