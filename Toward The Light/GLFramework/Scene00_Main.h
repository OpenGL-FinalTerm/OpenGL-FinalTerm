#pragma once
#include "GLScene.h"

/* UTILITIES */
//#include "Model.h"
//#include "Object.h"
//#include "Camera.h"
//#include "BoxObject.h"

#include "Object.h"

#include "NormalObject.h"
#include "Camera.h"
//#include "SoundPlayer.h"

#include "BoxObject.h"
#include "Character.h"
#include "LoadMap.h"

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
	virtual void drawHUD();
	virtual void HUD();

private:

	Camera	m_Camera;
	Object	m_Title;

	//박스 로딩 함수
	Box	objectBox[500];
	Box	objectBox2[500];
	tmp	tmpRect;
	int		whatBox;


	Vector2 select_map;
	int choose = 10;
	float color[2][3];
	Vector3 choose_map_box[2];
	//이거 함수로 따로 있나...으악
	Vector3 Setting_button;
	float Setting_bt_color[3];
	int degree;
};

