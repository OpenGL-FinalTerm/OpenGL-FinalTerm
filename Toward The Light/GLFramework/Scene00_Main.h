#pragma once
#include "GLScene.h"

/* UTILITIES */
#include "Model.h"
#include "Object.h"
#include "Camera.h"
#include "Model.h"
#include "NormalObject.h"
#include "Camera.h"
#include "SoundPlayer.h"
#include "BoxObject.h"
#include "Light.h"
#include "BananaSetting.h"
#include "Character.h"
#include "camera_working.h"
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

	Camera			m_Camera;
	Model			m_Model;
	Object			m_Title;

	Box				Map1objectBox[100];
	Box				Map2objectBox[100];

	tmp				Map1Banana;
	tmp				Map2Banana;

	Light			Map1RedColumn;
	Light			Map2RedColumn;

	Light			Map1Light[10];
	Light			Map2Light[10];

	int				Map1BoxCount;
	int				Map2BoxCount;

	int				Map1LightCount;
	int				Map2LightCount;
};

