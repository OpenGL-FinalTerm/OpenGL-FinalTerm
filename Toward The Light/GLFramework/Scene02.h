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
	float			tX = 0, tY = 0;
	float			oX = 0, oY = 0;
	float			rY = 0;
	float			radian;
	int switch_sign = -1;
	int Time_count;
	Camera			m_Camera;
	NormalObject	m_Plane;
	NormalObject    m_Box[3];
	NormalObject    m_wBox[3];
	SoundPlayer		m_SoundPlayer;
	Box				objectBox[65];
	Box				mainCharacter;
	Light			mapLight[100];
	Shape			banana;
	tmp				tmpRect;
};
