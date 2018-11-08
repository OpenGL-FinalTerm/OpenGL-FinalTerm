#include <GL/freeglut.h> 
#include <random>
#include <time.h>
#include <math.h>
#include "banana_draw.h"
#include "camera.h"
#include "box.h"
GLvoid Reshape(int w, int h);

#define whatBox 4
//�ػ� ����
#define WideSize 800
#define HighSize 600
#define Z_Size 400

//�׸��� ����
GLvoid drawScene(GLvoid);
BOOL draw_Act_On;

//Ÿ�̸� ����
void Timerfunction(int value);
BOOL Time_Act_On; //Ÿ�̸� Ȱ��ȭ ����
int move_count; //Ÿ�̸� ī��Ʈ

				//���콺 ����
void Mouse(int button, int state, int x, int y);
void SpecialKeys(int key, int x, int y);
POINT ms_click; //���콺 ��ǥ
BOOL Mouse_Act_On; //���콺 Ȱ��ȭ ����

				   //Ű���� ����
void Keyboard(unsigned char key, int x, int y);
BOOL Keyboard_Act_On; //Ű���� Ȱ��ȭ ����

					  //�� ����

#define PT 20//���� ���� ����
#define PI 3.141592 //����

typedef struct Shape
{
	Color cl;//����
	Translate_pos sp_pos[36];
	Translate_pos pos;
	Translate_pos move;
	Translate_pos scale;
	Translate_pos rot;

	int size;
	int select;
	int height;
	int slice;
	int stacks;
	BOOL b;
	BOOL any;

};


int change_count;
int next_rot;
int st_help;
BOOL Save = false;
BOOL ani = FALSE;
BOOL Look = FALSE;


//ī�޶�-----------------

Translate_pos EYE;
Translate_pos AT;
Translate_pos UP;

static int __x;
static int __y;
static int __z;

//ī�޶�
Cam camera;
Box box;
Box otherBox;
Box smallBox[4];

//��������
BOOL depth;
int depth_count;
//�ø�
BOOL culling;
int culling_count;
//���̵�
BOOL shade;
int shade_count;
//��
Shape ball[10];
//������

int index_box_size;
#define BALL_NUM 5

void SetupRC()
{
	index_box_size = 100;
	depth = true;
	smallBox[1].movingX(-50);
	smallBox[0].movingX(-50);
	smallBox[1].movingZ(-50);

	smallBox[2].movingX(-100);
	smallBox[2].movingZ(-100);

	smallBox[3].movingX(100);
	smallBox[3].movingZ(50);
	otherBox.movingX(-90);
	//-------------
}
void main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);//������ ���� ��ǥ
	glutInitWindowSize(WideSize, HighSize); //������ ���� ũ��
	glutCreateWindow("ex16");
	// - �������� ���� ���� �����ϱ�
	//���� �׸���
	SetupRC();
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, Timerfunction, 1);
	srand(time(NULL));
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{

	glFrontFace(GL_CCW);

	//���� ����
	if (depth) {
		glEnable(GL_DEPTH_TEST);
	}
	else {
		glDisable(GL_DEPTH_TEST);
	}

	//�ø� ����
	if (culling) {
		//glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);

	}
	else {
		//glFrontFace(GL_CCW);
		glDisable(GL_CULL_FACE);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();//-----------------------------------
	{
		camera.drawCamera();

		smallBox[0].drawBox(29, 100, 255, 100);
		smallBox[1].drawBox(29, 50, 100, 255);
		smallBox[2].drawBox(29, 20, 100, 255);
		smallBox[3].drawBox(29, 255, 255, 0);
		box.drawBox(30, 255, 255, 0);
	}
	glPopMatrix();
	glutSwapBuffers();
}

void Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}
	glutPostRedisplay();

}
void Motion(int x, int y, BOOL state) {

}

void Timerfunction(int value) {


	glutPostRedisplay(); //Ÿ�̸ӿ� �ִ´�.
	glutTimerFunc(100, Timerfunction, 1); //Ÿ�̸� �ٽ� ���

}
int ttt;
int ani_count;
void Keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
		//---------ī�޶�
		//rotate
	case ' ':
		box.movingY(1);
	
		if (box.returnBoxCenterY() + 15 >= smallBox[0].returnBoxCenterY() - 12.5 && !(box.returnBoxCenterY() - 15 >= smallBox[0].returnBoxCenterY() + 12.5)) {
			if (smallBox[0].returnBoxCenterX() - 12.5 < box.returnBoxCenterX() + 15 && smallBox[0].returnBoxCenterX() + 12.5 > box.returnBoxCenterX() - 15 && smallBox[0].returnBoxCenterZ() + 12.5 > box.returnBoxCenterZ() - 15 && smallBox[0].returnBoxCenterZ() - 12.5 < box.returnBoxCenterZ() + 15)
				smallBox[0].movingY(1);
		}

		break;

	case '/':
		box.movingY(-1);
		if (box.returnBoxCenterY() - 15 <= smallBox[0].returnBoxCenterY() + 12.5 && !(box.returnBoxCenterY() + 15 <= smallBox[0].returnBoxCenterY() - 12.5)) {
			if (smallBox[0].returnBoxCenterX() - 12.5 < box.returnBoxCenterX() + 15 && smallBox[0].returnBoxCenterX() + 12.5 > box.returnBoxCenterX() - 15 && smallBox[0].returnBoxCenterZ() + 12.5 > box.returnBoxCenterZ() - 15 && smallBox[0].returnBoxCenterZ() - 12.5 < box.returnBoxCenterZ() + 15)
				smallBox[0].movingY(-1);
		}
		break;

	case 'x':
		camera.rotateEye(1, 0, 0);
		break;
	case 'X':
		camera.rotateEye(-1, 0, 0);
		break;

	case 'y':
		camera.rotateEye(0, 1, 0);
		break;
	case 'Y':
		camera.rotateEye(0, -1, 0);
		break;

	case 'z':
		camera.rotateEye(0, 0, 1);
		break;
	case 'Z':
		camera.rotateEye(0, 0, -1);
		break;

		//move
	case 'w':
		camera.moveEye(0, 1, 0);
		break;
	case 'a':
		camera.moveEye(-1, 0, 0);
		break;

	case 's':
		camera.moveEye(0, -1, 0);
		break;

	case 'd':
		camera.moveEye(1, 0, 0);
		break;
	case '+':
		camera.moveEye(0, 0, 1);

		break;
	case '-':
		camera.moveEye(0, 0, -1);
		break;
	case 'i':
		camera.Init();
		break;

		// z�� �״�� camera.z 

		//-----------ī�޶� �� --------

	case '2'://�������� ����
		ani_count++;
		if (ani_count % 2 == 1) {
			ani = TRUE;//ȸ���ϴ°� Ʈ���
			Reshape(WideSize, HighSize);
		}
		else {
			ani = FALSE;//ȸ���ϴ°� Ʈ���
			Reshape(WideSize, HighSize);
		}
		break;

		//------------���� ��

	case '3'://��������
		depth_count++;
		if (depth_count % 2 == 1) {
			depth = true;
			printf("���� On \n");
		}
		else {
			printf("���� Off \n");
			depth = false;
		}

		break;
	case '4'://�ø�
		culling_count++;
		if (culling_count % 2 == 1) {
			culling = true;
			printf("�ø� On \n");
		}
		else {
			printf("�ø� Off \n");
			culling = false;
		}

		break;
	case '5'://���̵�
		shade_count++;
		if (shade_count % 2 == 1) {
			shade = true;
			printf("���̵� On \n");
		}
		else {
			printf("���̵� Off \n");
			shade = false;
		}

		break;


	default:
		;
		break;
	}
	glutPostRedisplay();

}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (!ani) {
		//glRotatef(30, 0, 1, 0);
		gluPerspective(60.0f, w / h, 1.0, 1000.0);

		glTranslated(0.0, 0.0, -300.0);     // ���� ������ ȭ�� �������� �̵��Ͽ� �þ߸� Ȯ���Ѵ�.
	}
	else {
		glOrtho(0, WideSize, HighSize, 0, -Z_Size / 2, Z_Size / 2); //�����츦 �ʱ�ȭ �ϴ� �Լ��Դϴ�!
		glTranslated(WideSize / 2, HighSize / 2, 0);
		//glRotatef(-60, 1, 0, 0);

	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
BOOL check = FALSE;

void SpecialKeys(int key, int x, int y) {
	
	int cycle = 0;
	if (key == GLUT_KEY_UP) {
		int i = 0;
		box.movingZ(-1);
		int count = 0;
		while (check == FALSE) {
	
			if (box.returnBoxCenterZ() - 15 <= smallBox[i].returnBoxCenterZ() + 12.5 && !(box.returnBoxCenterZ() + 15 <= smallBox[i].returnBoxCenterZ() - 12.5)) {
				if (smallBox[i].returnBoxCenterX() - 12.5 < box.returnBoxCenterX() + 15 && smallBox[i].returnBoxCenterX() + 12.5 > box.returnBoxCenterX() - 15 && smallBox[i].returnBoxCenterY() + 12.5 > box.returnBoxCenterY() - 15 && smallBox[i].returnBoxCenterY() - 12.5 < box.returnBoxCenterY() + 15) {
					if (smallBox[i].returnCheck() == 0) {
						box.addZrate(-29);
						smallBox[i].movingZ(-1);
						smallBox[i].checkUpdate(1);
					}
				}
			}

			if (i == whatBox - 1) {
				cycle++;
				for (int j = 0; j < whatBox; ++j) {
					if (smallBox[j].returnCheck()) {
						count++;
					}
				}
				if (count == whatBox || count == 0 || cycle == whatBox)
					check = TRUE;
				else
					i = 0;

				count = 0;
			}
			else {
				i++;

			}

		}

		for (int k = 0; k < whatBox; ++k)
			smallBox[k].checkUpdate(0);
		check = FALSE;
		cycle = 0;
		box.clearAdd();
	}

	if (key == GLUT_KEY_DOWN) {
		int i = 0;
		box.movingZ(1);
		int count = 0;
		while (check == FALSE) {

			if (box.returnBoxCenterZ() + 15 >= smallBox[i].returnBoxCenterZ() - 12.5 && !(box.returnBoxCenterZ() - 15 >= smallBox[i].returnBoxCenterZ() + 12.5)) {
				if (smallBox[i].returnBoxCenterX() - 12.5 < box.returnBoxCenterX() + 15 && smallBox[i].returnBoxCenterX() + 12.5 > box.returnBoxCenterX() - 15 && smallBox[i].returnBoxCenterY() + 12.5 > box.returnBoxCenterY() - 15 && smallBox[i].returnBoxCenterY() - 12.5 < box.returnBoxCenterY() + 15) {
					if (smallBox[i].returnCheck() == 0) {
						box.addZrate(29);
						smallBox[i].movingZ(1);
						smallBox[i].checkUpdate(1);
					}
				}
			}

			if (i == whatBox - 1) {
				cycle++;
				for (int j = 0; j < whatBox; ++j) {
					if (smallBox[j].returnCheck()) {
						count++;
					}
				}
				if (count == whatBox || count == 0 || cycle == whatBox)
					check = TRUE;
				else
					i = 0;

				count = 0;
			}
			else {
				i++;
			}
		}

		for (int k = 0; k < whatBox; ++k)
			smallBox[k].checkUpdate(0);
		check = FALSE;
		cycle = 0;
		box.clearAdd();

	}

	if (key == GLUT_KEY_LEFT) {
		int i = 0;
		box.movingX(-1);
		int count = 0;
		while (check == FALSE) {
			
			if (box.returnBoxCenterX() - 15 <= smallBox[i].returnBoxCenterX() + 12.5 && !(box.returnBoxCenterX() + 15 <= smallBox[i].returnBoxCenterX() - 12.5)) {
				if (smallBox[i].returnBoxCenterZ() - 12.5 < box.returnBoxCenterZ() + 15 && smallBox[i].returnBoxCenterZ() + 12.5 > box.returnBoxCenterZ() - 15 && smallBox[i].returnBoxCenterY() + 12.5 > box.returnBoxCenterY() - 15 && smallBox[i].returnBoxCenterY() - 12.5 < box.returnBoxCenterY() + 15) {
					if (smallBox[i].returnCheck() == 0) {
						box.addXrate(-29);
						smallBox[i].movingX(-1);
						smallBox[i].checkUpdate(1);
					}
				}
			}

			if (i >= whatBox - 1) {
				cycle++;
				for (int j = 0; j < whatBox; ++j) {
					if (smallBox[j].returnCheck()) {
						count++;
					}
				}

				if (count == whatBox || count == 0 || cycle == whatBox)
					check = TRUE;
				else
					i = 0;
				
				count = 0;
			}

			else {
				i++;

			}
		}

		for (int k = 0; k < whatBox; ++k)
			smallBox[k].checkUpdate(0);
		check = FALSE;
		cycle = 0;
		box.clearAdd();

	}

	if (key == GLUT_KEY_RIGHT) {
		int i = 0;
		box.movingX(1);

		int count = 0;

		while (check == FALSE) {
			if (box.returnBoxCenterX() + 15 >= smallBox[i].returnBoxCenterX() - 12.5 && !(box.returnBoxCenterX() - 15 >= smallBox[i].returnBoxCenterX() + 12.5)) {
				if (smallBox[i].returnBoxCenterZ() - 12.5 < box.returnBoxCenterZ() + 15 && smallBox[i].returnBoxCenterZ() + 12.5 > box.returnBoxCenterZ() - 15 && smallBox[i].returnBoxCenterY() + 12.5 > box.returnBoxCenterY() - 15 && smallBox[i].returnBoxCenterY() - 12.5 < box.returnBoxCenterY() + 15) {
					if (smallBox[i].returnCheck() == 0) {
						box.addXrate(29);
						smallBox[i].movingX(1);
						smallBox[i].checkUpdate(1);
					}
				}
			}

			if (i == whatBox - 1) {
				cycle++;
				for (int j = 0; j < whatBox; ++j) {
					if (smallBox[j].returnCheck()) {
						count++;
					}
				}
				if (count == whatBox || count == 0 || cycle == whatBox)
					check = TRUE;
				else
					i = 0;

				count = 0;
			}
			else {
				i++;

			}
		}

		for (int k = 0; k < whatBox; ++k)
			smallBox[k].checkUpdate(0);
		check = FALSE;
		cycle = 0;
		box.clearAdd();
	}
	glutPostRedisplay();
}