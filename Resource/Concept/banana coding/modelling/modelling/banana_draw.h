#pragma once
#pragma once
#pragma once
#include <GL/freeglut.h> 

typedef struct Color
{
	int R;
	int G;
	int B;
};
typedef struct Translate_pos {
	float x;
	float y;
	float z;
	float degree;
};


typedef struct BoOL
{
	int b_x;
	int b_y;
	int b_z;
};

typedef struct QUAD
{
	Color cl[50];//색상
	Translate_pos pos[50];//총 정점 수 74 / 2
	Translate_pos move;
	Translate_pos scale;
	Translate_pos rot;

	int size;
	int select;
	int height;
	int slice;
	int stacks;
	BoOL b;
	BOOL any;

};

//머리 3

QUAD index;

void Swap(float a, float b) {
	float temp;
	temp = a;
	a = b;
	b = temp;
}

void banana_head(int head_x, int pivot_y, int pivot_z, int size) {
	//인덱스 버퍼 저장
	//바나나 헤드
	//머리 1
	index.pos[0].x = 0.0f;
	index.pos[0].y = -2.761;
	index.pos[0].z = 17.274;

	index.pos[1].x = 0.0f;
	index.pos[1].y = -4.338;
	index.pos[1].z = 13.761;

	index.pos[2].x = -3.034;
	index.pos[2].y = -2.825;
	index.pos[2].z = 14.274;

	index.pos[3].x = -4.181;
	index.pos[3].y = -0.4f;
	index.pos[3].z = 15.601;

	index.pos[4].x = -2.728;
	index.pos[4].y = 1.37f;
	index.pos[4].z = 17.539;

	index.pos[5].x = 0.0f;
	index.pos[5].y = 1.842;
	index.pos[5].z = 18.588f;

	//머리 2
	index.pos[1 + 1 * 5].x = 0.0f;
	index.pos[1 + 1 * 5].y = 1.258;
	index.pos[1 + 1 * 5].z = 9.247;

	index.pos[2 + 1 * 5].x = -1.233;
	index.pos[2 + 1 * 5].y = 1.589;
	index.pos[2 + 1 * 5].z = 9.635;

	index.pos[3 + 1 * 5].x = -2.411;
	index.pos[3 + 1 * 5].y = 2.686;
	index.pos[3 + 1 * 5].z = 10.71;

	index.pos[4 + 1 * 5].x = -2.004;
	index.pos[4 + 1 * 5].y = 3.312;
	index.pos[4 + 1 * 5].z = 11.909;

	index.pos[5 + 1 * 5].x = 0.0f;
	index.pos[5 + 1 * 5].y = 3.927;
	index.pos[5 + 1 * 5].z = 12.576;

	//머리 3
	index.pos[1 + 2 * 5].x = 0.0f;
	index.pos[1 + 2 * 5].y = 1.568;
	index.pos[1 + 2 * 5].z = 8.439;

	index.pos[2 + 2 * 5].x = -1.597;
	index.pos[2 + 2 * 5].y = 2.119;
	index.pos[2 + 2 * 5].z = 9.078;

	index.pos[3 + 2 * 5].x = -3.043;
	index.pos[3 + 2 * 5].y = 3.312;
	index.pos[3 + 2 * 5].z = 10.247;

	index.pos[4 + 2 * 5].x = -2.419;
	index.pos[4 + 2 * 5].y = 3.843;
	index.pos[4 + 2 * 5].z = 12.241;

	index.pos[5 + 2 * 5].x = 0.0f;
	index.pos[5 + 2 * 5].y = 4.318;
	index.pos[5 + 2 * 5].z = 12.241;

	//머리 4
	index.pos[1 + 3 * 5].x = 0.0f;
	index.pos[1 + 3 * 5].y = 0.745;
	index.pos[1 + 3 * 5].z = 3.886;

	index.pos[2 + 3 * 5].x = -3.824;
	index.pos[2 + 3 * 5].y = 2.21f;
	index.pos[2 + 3 * 5].z = 4.066;

	index.pos[3 + 3 * 5].x = -5.822;
	index.pos[3 + 3 * 5].y = 6.151;
	index.pos[3 + 3 * 5].z = 5.761;

	index.pos[4 + 3 * 5].x = -4.158;
	index.pos[4 + 3 * 5].y = 8.571;
	index.pos[4 + 3 * 5].z = 7.546;

	index.pos[5 + 3 * 5].x = 0.0f;
	index.pos[5 + 3 * 5].y = 9.382;
	index.pos[5 + 3 * 5].z = 9.133;

	//머리 5
	index.pos[1 + 4 * 5].x = 0.0f;
	index.pos[1 + 4 * 5].y = -1.533;
	index.pos[1 + 4 * 5].z = -3.874;

	index.pos[2 + 4 * 5].x = -4.595;
	index.pos[2 + 4 * 5].y = -0.013;
	index.pos[2 + 4 * 5].z = -4.006;

	index.pos[3 + 4 * 5].x = -7.523;
	index.pos[3 + 4 * 5].y = 4.756;
	index.pos[3 + 4 * 5].z = -3.643;

	index.pos[4 + 4 * 5].x = -4.945;
	index.pos[4 + 4 * 5].y = 9.724;
	index.pos[4 + 4 * 5].z = -2.282;

	index.pos[5 + 4 * 5].x = 0.0f;
	index.pos[5 + 4 * 5].y = 12.002;
	index.pos[5 + 4 * 5].z = -0.415;

	//머리 6
	index.pos[1 + 5 * 5].x = 0.0f;
	index.pos[1 + 5 * 5].y = -4.107;
	index.pos[1 + 5 * 5].z = -7.083;

	index.pos[2 + 5 * 5].x = -3.583;
	index.pos[2 + 5 * 5].y = -3.629;
	index.pos[2 + 5 * 5].z = -7.564;

	index.pos[3 + 5 * 5].x = -6.663;
	index.pos[3 + 5 * 5].y = 1.631;
	index.pos[3 + 5 * 5].z = -11.123;

	index.pos[4 + 5 * 5].x = -4.551;
	index.pos[4 + 5 * 5].y = 5.834;
	index.pos[4 + 5 * 5].z = -13.475;

	index.pos[5 + 5 * 5].x = 0.0f;
	index.pos[5 + 5 * 5].y = 8.641;
	index.pos[5 + 5 * 5].z = -13.97f;

	//머리 7
	index.pos[1 + 6 * 5].x = 0.0f;
	index.pos[1 + 6 * 5].y = -6.58f;
	index.pos[1 + 6 * 5].z = -9.429;

	index.pos[2 + 6 * 5].x = -3.009;
	index.pos[2 + 6 * 5].y = -6.078;
	index.pos[2 + 6 * 5].z = -9.795;

	index.pos[3 + 6 * 5].x = -5.603;
	index.pos[3 + 6 * 5].y = -2.576;
	index.pos[3 + 6 * 5].z = -13.82f;

	index.pos[4 + 6 * 5].x = -3.29f;
	index.pos[4 + 6 * 5].y = 0.417;
	index.pos[4 + 6 * 5].z = -18.421;

	index.pos[5 + 6 * 5].x = 0.0f;
	index.pos[5 + 6 * 5].y = -1.075;
	index.pos[5 + 6 * 5].z = -20.255;

	//머리 8
	index.pos[1 + 7 * 5].x = 0.0f;
	index.pos[1 + 7 * 5].y = -10.789;
	index.pos[1 + 7 * 5].z = -12.458;

	index.pos[2 + 7 * 5].x = -1.923;
	index.pos[2 + 7 * 5].y = -10.509;
	index.pos[2 + 7 * 5].z = -12.608;

	index.pos[3 + 7 * 5].x = -3.847;
	index.pos[3 + 7 * 5].y = -9.577;
	index.pos[3 + 7 * 5].z = -16.107;

	index.pos[4 + 7 * 5].x = -2.627;
	index.pos[4 + 7 * 5].y = -9.781;
	index.pos[4 + 7 * 5].z = -18.481;

	index.pos[5 + 7 * 5].x = 0.0f;
	index.pos[5 + 7 * 5].y = -10.456;
	index.pos[5 + 7 * 5].z = -19.459;

	//머리 9
	index.pos[1 + 8 * 5].x = 0.0f;
	index.pos[1 + 8 * 5].y = -12.017;
	index.pos[1 + 8 * 5].z = -14.961;

	for (int i = 0; i < (1 + 8 * 5) + 1; i++) {

		index.cl[i].R = (i + 10) % 255;
		index.cl[i].G = (i + 10) % 255;


		Swap(index.pos[i].y, -index.pos[i].z);
	}
	// x z -y
	for (int i = 0; i <= (1 + 8 * 5 + 1); i++) {
		int tmp;
		tmp = index.pos[i].y;
		index.pos[i].y = index.pos[i].z;
		index.pos[i].z = -tmp;
	}

	glPushMatrix(); {

		glTranslated(head_x, pivot_y, pivot_z);
		glScaled(5, 5, 5);

		glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_POLYGON); {//아래

			glVertex3f(index.pos[0].x, index.pos[0].y, index.pos[0].z);//중심

			glVertex3f(index.pos[1].x, index.pos[1].y, index.pos[1].z);//그외

			glVertex3f(index.pos[2].x, index.pos[2].y, index.pos[2].z);//그외

		}
		glEnd();

		glBegin(GL_POLYGON); {//아래

			glVertex3f(index.pos[0].x, index.pos[0].y, index.pos[0].z);//중심

			glVertex3f(index.pos[2].x, index.pos[2].y, index.pos[2].z);//그외

			glVertex3f(index.pos[3].x, index.pos[3].y, index.pos[3].z);//그외
		}
		glEnd();

		glBegin(GL_POLYGON); {//아래

			glVertex3f(index.pos[0].x, index.pos[0].y, index.pos[0].z);//중심

			glVertex3f(index.pos[3].x, index.pos[3].y, index.pos[3].z);//그외

			glVertex3f(index.pos[4].x, index.pos[4].y, index.pos[4].z);//그외
		}
		glEnd();

		glBegin(GL_POLYGON); {//아래

			glVertex3f(index.pos[0].x, index.pos[0].y, index.pos[0].z);//중심

			glVertex3f(index.pos[4].x, index.pos[4].y, index.pos[4].z);//그외

			glVertex3f(index.pos[5].x, index.pos[5].y, index.pos[5].z);//그외
		}
		glEnd();
		
		glColor3f(0.0f, 1.0f, 1.0f);

		for (int j = 0; j < 8; j++) {
			for (int i = 1; i < 5; i++) {
				
				
				glBegin(GL_POLYGON); {//아래

					glVertex3f(index.pos[i + j * 5].x, index.pos[i + j * 5].y, index.pos[i + j * 5].z);//중심

					glVertex3f(index.pos[(i + 1) + j * 5].x, index.pos[(i + 1) + j * 5].y, index.pos[(i+ 1) + j * 5].z);//그외

					glVertex3f(index.pos[(i + 1) + (j + 1) * 5].x, index.pos[(i + 1) + (j + 1) * 5].y, index.pos[(i + 1) + (j + 1 )* 5].z);//그외

					glVertex3f(index.pos[(i) + (j + 1) * 5].x, index.pos[(i) + (j + 1) * 5].y, index.pos[(i) + (j + 1) * 5].z);//그외

				}
				glEnd();
			}
		}
	
		for (int i = 0; i <= (1 + 8 * 5 + 1); i++) {

			if (index.pos[i].x != 0.0f)
			{
				index.pos[i].x = -index.pos[i].x;
				index.pos[i].y = index.pos[i].y;
				index.pos[i].z = index.pos[i].z;
			}
		}
		glColor3f(1.0f, 1.0f, 0.0f);

		glBegin(GL_POLYGON); {//아래

			glVertex3f(index.pos[0].x, index.pos[0].y, index.pos[0].z);//중심

			glVertex3f(index.pos[1].x, index.pos[1].y, index.pos[1].z);//그외

			glVertex3f(index.pos[2].x, index.pos[2].y, index.pos[2].z);//그외

		}
		glEnd();

		glBegin(GL_POLYGON); {//아래

			glVertex3f(index.pos[0].x, index.pos[0].y, index.pos[0].z);//중심

			glVertex3f(index.pos[2].x, index.pos[2].y, index.pos[2].z);//그외

			glVertex3f(index.pos[3].x, index.pos[3].y, index.pos[3].z);//그외
		}
		glEnd();

		glBegin(GL_POLYGON); {//아래

			glVertex3f(index.pos[0].x, index.pos[0].y, index.pos[0].z);//중심

			glVertex3f(index.pos[3].x, index.pos[3].y, index.pos[3].z);//그외

			glVertex3f(index.pos[4].x, index.pos[4].y, index.pos[4].z);//그외
		}
		glEnd();

		glBegin(GL_POLYGON); {//아래

			glVertex3f(index.pos[0].x, index.pos[0].y, index.pos[0].z);//중심

			glVertex3f(index.pos[4].x, index.pos[4].y, index.pos[4].z);//그외

			glVertex3f(index.pos[5].x, index.pos[5].y, index.pos[5].z);//그외
		}
		glEnd();

		for (int j = 0; j < 8; j++) {
			for (int i = 1; i < 4 + 1; i++) {

				glBegin(GL_POLYGON); {//아래

					glVertex3f(index.pos[(i + 1) + j * 5].x, index.pos[(i + 1) + j * 5].y, index.pos[(i + 1) + j * 5].z);//그외
					
					glVertex3f(index.pos[i + j * 5].x, index.pos[i + j * 5].y, index.pos[i + j * 5].z);//중심

					glVertex3f(index.pos[(i)+(j + 1) * 5].x, index.pos[(i)+(j + 1) * 5].y, index.pos[(i)+(j + 1) * 5].z);//그외

					glVertex3f(index.pos[(i + 1) + (j + 1) * 5].x, index.pos[(i + 1) + (j + 1) * 5].y, index.pos[(i + 1) + (j + 1) * 5].z);//그외



				}
				glEnd();
			}
		}
	}
	glPopMatrix();


}


void banana_draw(int pivot_x, int pivot_y, int pivot_z, int size) {

	
	banana_head(pivot_x, pivot_y, pivot_z, size);
}
