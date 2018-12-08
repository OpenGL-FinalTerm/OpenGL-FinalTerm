#include "stdafx.h"
#include "GLFramework.h"
#include "banana_draw.h"// 애 이상한친구인데......................... 다른곳에 넣으면 안돌던데....
#include "LoadMap.h"
#include "Character.h"
#include "BananaSetting.h"
#include "Scene_Start.h"

//날름 포인터 다이스키

//해야할거 로고 이미지 넣기

S06Start::S06Start()
{
}

S06Start::~S06Start()
{
}

void S06Start::init()
{
	ShowCursor(false);
	radian = 90;
	m_SoundPlayer.init();
	m_SoundPlayer.selectFolder("Resources\\BGM");

	m_Camera.setDistance(300.f);
	m_Camera.setPerspective(45.f, 0.125f, 7'000.f);
	m_Camera.setSensitivity(10.f);

	//for (int i = 0; i < 20; ++i) {
	//   objectBox[i].CreateBox(rand() % 120 - 60, 10, rand() % 140 - 70);
	//   objectBox[i].setColor(rand() % 255, rand() % 255, rand() % 255);
	//}

	whatBox = LoadMap(objectBox, tmpRect, 2);
	//LightCount = LoadLight(mapLight, 2);


	glGenTextures(6, IDtmp);
	glBindTexture(GL_TEXTURE_2D, IDtmp[0]);
	pBytes = LoadDIBitmap("toward_that_light_V_logo2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1140, 682, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


}

void S06Start::exit()
{
	m_SoundPlayer.exit();
}

void S06Start::reset()
{
	m_SoundPlayer.play();
}

float S06Start::returnMainX()
{
	return tmpRect.x + tmpRect.xRate;
}

float S06Start::returnMainY()
{
	return tmpRect.y + tmpRect.yRate;
}

float S06Start::returnMainZ()
{
	return tmpRect.z + tmpRect.zRate;
}

void S06Start::render()
{
	glPushMatrix();
	//m_Camera.ready();
	//glColor3f(1.0f, 1.0f, 1.0f);
	//glBegin(GL_QUADS);
	//glNormal3f(0, 1, 0);
	//glVertex3f(-60, 0, -70);
	//glVertex3f(-60, 0, 70);
	//glVertex3f(60, 0, 70);
	//glVertex3f(60, 0, -70);
	//glEnd();

	//for (int i = 0; i < 65; ++i)
	//	objectBox[i].drawBox(20);

	//for (int i = 0; i < LightCount; ++i)
	//	mapLight[i].drawLight(TRUE, i);

	////카메라 정리 ---
	//if (opening_camera_working) {//오프닝 영상이 시작되면

	//	if (opening_bezier_t >= 1) {
	//		opening_camera_working = false;
	//	}
	//	opening_bezier_t += 0.01f;

	//	opening_camera_Eye(&red_right_cylinder.x, &red_right_cylinder.y, &red_right_cylinder.z, &tmpRect.x, &tmpRect.y, &tmpRect.z, &opening_bezier_t, 300, &Eye.x, &Eye.y, &Eye.z);
	//	opening_camera_At(&start_At.x, &start_At.y, &start_At.z, &end_At.x, &end_At.y, &end_At.z, &opening_bezier_t, &At.x, &At.y, &At.z);

	//	printf("opeing %f \n", Eye.y);
	//}


	//if (!opening_camera_working) { //오프닝 카메라 워킹이 false
	//	//eye 도 각도에 따라 바뀐다.
	//	camera_moving_Eye(&tmpRect.x, &tmpRect.y, &tmpRect.z, &result_degree[0], &view_rotate[0], &view_rotate[1], &Eye.x, &Eye.y, &Eye.z);
	//	camera_moving_At(&tmpRect.x, &tmpRect.y, &tmpRect.z, &result_degree[0], &view_at_size[0], &view_at_size[1], &At.x, &At.y, &At.z);
	//}

	//glPushMatrix();
	//banana_draw(tmpRect.x, tmpRect.y + 5, tmpRect.z, 0.5, IDLE, banana.rot.degree, result_degree[0]);
	//glPopMatrix();

	//m_Camera.setEye(Eye);
	//m_Camera.setTarget(At);
		//일단 출력할 사각형 출력
	glPushMatrix();


	drawHUD();

	glPopMatrix();
}


void S06Start::reshape(int w, int h)
{

}




void S06Start::keyboard(int key, bool pressed, int x, int y, bool special)
{

	if (pressed)
	{
		switch (key)
		{
		case ' ':
			m_Framework->toScene("Main");
			break;
			//환경설정 나오기


		//바로가기 
		case '1': m_Framework->toScene("1"); break;
		case '2': m_Framework->toScene("2"); break;
		case '3': m_Framework->toScene("3"); break;
		case '4': m_Framework->toScene("Ending"); break;
		case '5': m_Framework->toScene("Setting"); break;
		}
	}

}

void S06Start::mouse(int button, bool pressed, int x, int y)
{
	if (pressed) {
		if (button == GLUT_LEFT_BUTTON && pickLight == true) {

		}
	}
}

void S06Start::motion(bool pressed, int x, int y)
{

}



void S06Start::update(float fDeltaTime)
{
	//camera at --> player going foward pos update
// banana pos add


}



void S06Start::LightSetting()
{

}

void S06Start::camera_install(int x, int y) {
	printf("ok \n");

}

void S06Start::HUD()
{
	glColor3f(1.f, 1.f, 1.f);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, IDtmp[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex2f(0, 0);
	glTexCoord2f(0, 0);
	glVertex2f(0, 900);
	glTexCoord2f(1, 0);
	glVertex2f(1500, 900);
	glTexCoord2f(1, 1);
	glVertex2f(1500, 0);
	glEnd();

	glColor3f(1.f, 1.f, 1.f);
	print("press 'Space' Game Start", 630, 900 / 2, 0);

	glPopMatrix();
}

void S06Start::drawHUD()
{
	glMatrixMode(GL_PROJECTION);
	//glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 1500.0, 900.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	glLoadIdentity();

	HUD();
	glDisable(GL_TEXTURE_2D);
	//glMatrixMode(GL_PROJECTION);
	//glPopMatrix();
	//glMatrixMode(GL_MODELVIEW);
	//glPopMatrix();
}

GLuint S06Start::LoadTexture(const char * filename, int width_1, int height_1)
{
	GLuint texture;
	int width, height;
	unsigned char * data;
	FILE * file;

	// 파일 열기
	fopen_s(&file, filename, "rb");
	if (file == NULL) return 0;
	width = width_1;
	height = height_1;
	data = (unsigned char *)malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	// 색상결정
	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;
	}

	// 이후 PDF동일
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Modulate로 함
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	// 나는 밉맵으로 만듬
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}