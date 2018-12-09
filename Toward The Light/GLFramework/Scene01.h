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
#include "camera_working.h"
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
	virtual void drawHUD();
	virtual void HUD();
	//ī�޶�
	virtual void camera_install(int x, int y);
	virtual void LightSetting();
	virtual float returnMainX();
	virtual float returnMainY();
	virtual float returnMainZ();

	virtual GLuint LoadTexture(const char * filename, int width_1, int height_1);


private:
	float		rX, rY, rZ;
	float		radian;
	float		camera_deree[3];

	int			whatBox;
	int			LightCount = 4;
	int			angle = 0;
	int			depthCheck = 0;
	int			switch_sign = -1;
	int			Time_count;
	int			tX, tY;
	int			move_Eye[3];
	int			change_person_view_count = 0;
	int			drag_old_postion[2] = {};
	int			drag_new_postion[2] = {};
	int			__t = 0;
	int			pickLightNumber = -1;

	bool		dep = false; // �����Ҷ� �����ϴ°͵� üũ�Ͽ��� ������
	bool		person_view_1 = false;
	bool		person_view_3 = false;
	bool		person_view_mouse = true;
	bool		s;
	bool		keyW = false;
	bool		keyA = false;
	bool		keyS = false;
	bool		keyD = false;
	bool		keyDown = false;
	bool		pickLight = false;
	bool		messageOn = false;
	bool		wPress = false;
	bool		aPress = false;
	bool		sPress = false;
	bool		dPress = false;

	bool catchBox = false;
	int boxIndex;

	float		difference_new_old[2] = {}; // between drag_old postion and drag new postion --> old - new
	float		difference_size = 1.f;
	float		difference_normal_pos[2] = {};
	float		result_degree[2] = {};
	float		assist_rotation = 1;
	int		view_rotate[2] = {};
	int view_at_size[2];
	//���� ������
	Vector3 red_right_cylinder;
	//������ ����
	bool opening_camera_working;
	float opening_bezier_t;
	Vector3 start_At;
	Vector3 end_At;

	Vector3			Eye;
	Vector3			At;
	Vector3			foward_move; //���ư����ϴ� ����
	Vector2			foward;//player move
	Camera			m_Camera;
	NormalObject	m_Plane;
	NormalObject    m_Sphere;
	SoundPlayer		m_SoundPlayer;
	SoundPlayer		m_walkingSound;
	Box				objectBox[100];
	Box				mainCharacter;
	Light			mapLight[100];
	Shape			banana;
	tmp				tmpRect;
	Vector3			Destination;

	GLuint			texCord;
	GLubyte			*pBytes;
	BITMAPINFO		*info;
	GLuint			IDtmp[6];

	Light			RedColumn;
	float			t;
	float			ControlPoint[3];
	float			startPos[3];


	GLfloat spotPos[4] = { 0,0,0, 1.0f };
	GLfloat spotDiffuse[4] = { 1.f ,1.f, 1.f, 1.f };
	GLfloat spotSpecu[4] = { 1.f, 1.f, 1.f, 1.f };
};

