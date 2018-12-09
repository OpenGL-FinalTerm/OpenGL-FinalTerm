#pragma once
#pragma once
#include "GLScene.h"

/* UTILITIES */
#include "Camera.h"
#include "SoundPlayer.h"
#include "BoxObject.h"
#include "Light.h"
#include "BananaSetting.h"
#include "Character.h"
#include "camera_working.h"
/* ------------ */

class S05Setting :
	public GLScene
{
public:
	S05Setting();
	virtual ~S05Setting();

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
	//카메라
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

	bool		dep = false; // 시작할때 낙하하는것도 체크하여서 만들어둠
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

	float		difference_new_old[2] = {}; // between drag_old postion and drag new postion --> old - new
	float		difference_size = 1.f;
	float		difference_normal_pos[2] = {};
	float		result_degree[2] = {};
	float		assist_rotation = 1;
	int		view_rotate[2] = {};
	int view_at_size[2];
	//붉은 조명기둥
	Vector3 red_right_cylinder;
	//오프닝 시작
	bool opening_camera_working;
	float opening_bezier_t;
	Vector3 start_At;
	Vector3 end_At;

	Vector3			Eye;
	Vector3			At;
	Vector3			foward_move; //나아가야하는 방향
	Vector2			foward;//player move
	Camera			m_Camera;
	SoundPlayer		m_SoundPlayer;
	SoundPlayer		m_walkingSound;
	Box				objectBox[65];
	Box				mainCharacter;
	Light			mapLight[100];
	Shape			banana;
	tmp				tmpRect;
	Vector3			Destination;

	GLuint			texCord;
	GLubyte			*pBytes;
	BITMAPINFO		*info;
	GLuint			IDtmp[6];


	Vector2 select_map;

	#define scroll_num 4
	//Exit button
	Vector3			Exit_button;
	Vector3			Exit_button_size;
	bool Exit_button_b;
	//스크롤 관련된 함수
	Vector3 scroll_bar[scroll_num];
	Vector3 scroll_bar_size[scroll_num];

	Vector3 scroll_bt[scroll_num];
	Vector3 scroll_bt_size[scroll_num];
	bool scroll_bt_b[scroll_num];
	bool scroll_motion_b[scroll_num];
	Vector3 old_mouse_pos;
	float scroll_result[scroll_num];


	float			t;
	float			ControlPoint[3];
	float			startPos[3];

};

