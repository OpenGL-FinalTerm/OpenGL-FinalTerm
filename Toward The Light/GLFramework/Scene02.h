#pragma once
//#pragma comment (lib,"SDL2")
//#pragma comment (lib,"SDL2main")
//#pragma comment (lib,"SDL2_image")
//#pragma comment (lib,"opengl32.lib")
#include "GLScene.h"

/* UTILITIES */
#include "Camera.h"
#include "SoundPlayer.h"
#include "BoxObject.h"
#include "Light.h"
#include "BananaSetting.h"
#include "Character.h"
#include "Wall.h"
#include "LoadBitmap.h"
#include <Windows.h>
#include "camera_working.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm")

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
	virtual void drawHUD();
	virtual void HUD();
	virtual float returnMainX();
	virtual float returnMainY();
	virtual float returnMainZ();

	virtual GLuint LoadTexture(const char * filename, int width_1, int height_1);
	DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave);
	void LoadSound(int i, bool check);

private:
	float		tX = 0, tY = 0;
	float		oX = 0, oY = 0;
	float		rY = 0;
	float		radian;
	float		banana_cl[3];//banana color

	
	int			whatBox;
	int			LightCount = 4;
	int			angle = 0;
	int			switch_sign = -1;
	int			Time_count;
	int			depthCheck = 0;
	
	bool		dep = false; // �����Ҷ� �����ϴ°͵� üũ�Ͽ��� ������
	bool		person_view_1 = false;
	bool		person_view_3 = false;
	bool		person_view_mouse = true;
	bool		keyW = false;
	bool		keyA = false;
	bool		keyS = false;
	bool		keyD = false;
	bool		keyDown = false;
	bool		pickLight = false;
	bool		messageOn = false;

	int			pickLightNumber = -1;
	int			drag_old_postion[2] = {};
	int			drag_new_postion[2] = {};
	int			change_person_view_count = 0;
	int			move_Eye[3];
	int			__t = 0;
	int			w = 150;
	int			h = 150;

	float			t;
	float		camera_deree[3];
	float		difference_new_old[2] = {}; // between drag_old postion and drag new postion --> old - new
	float		difference_size = 1.f;
	float		difference_normal_pos[2] = {};
	float		result_degree[2] = {};
	float		assist_rotation = 1;
	int		view_rotate[2] = {};
	int			view_at_size[2];
	bool		wPress = false;
	bool		aPress = false;
	bool		sPress = false;
	bool		dPress = false;
	
	int			stepSound = 0;
	GLuint			texCord;
	GLubyte			*pBytes;
	BITMAPINFO		*info;
	GLuint			IDtmp[6];
	Vector2			foward;//player move
	Vector3			Eye;
	Vector3			At;
	Vector3			foward_move; //���ư����ϴ� ����
	Vector3			Destination;
	float			ControlPoint[3];
	float			startPos[3];

	// ���ڸ� ������ �������� üũ
	bool			catchBox;
	int				boxIndex;
	//���� ���� ��ġ
	Vector3 red_right_cylinder;

	//ī�޶� ���� �ִϸ��̼�
	bool opening_camera_working;
	float opening_bezier_t;
	Vector3 start_At;
	Vector3 end_At;

	Camera			m_Camera;
	BITMAPINFO		*texture;
	//Texture			textures;
	SoundPlayer		m_map2BGM;
	SoundPlayer		m_map2Walk;
	Box				objectBox[100];
	Box				mainCharacter;

	Light			mapLight[100];
	Light			RedColumn;
	
	Shape			banana;
	tmp				tmpRect;
	//GLubyte *map = (GLubyte*)image->pixels;


	//����Ʈ ����Ʈ �����
	GLfloat spotPos[4] = { 0,0,0, 1.0f };
	GLfloat spotDiffuse[4] = { 1.f ,1.f, 1.f, 1.f };
	GLfloat spotSpecu[4] = { 1.f, 1.f, 1.f, 1.f };


	// �����ӿ�ũ BGM �������� �ٸ��ɷ� ��ü��
	MCI_OPEN_PARMS      mciOpenParms;
	MCI_PLAY_PARMS       mciPlayParms;
	MCI_STATUS_PARMS   mciStatus;
	UINT wDeviceID = 0;
};
