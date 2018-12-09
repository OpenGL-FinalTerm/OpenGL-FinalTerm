
#include "banana_draw.h"
QUAD index;

int array_count = 0;

void Swap(float a, float b) {
	float temp;
	temp = a;
	a = b;
	b = temp;
}
float banana_color_[7][3];


void banana_save_index() {
	//인덱스 버퍼 저장
	//바나나 헤드
	//머리 1

	// 번호 /  (몇 줄)행 / 라인 갯수

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

		Swap(index.pos[i].y, -index.pos[i].z);
	}

	// x z -y
	for (int i = 0; i <= (1 + 8 * 5 + 1); i++) {
		index.pos[i].x = index.pos[i].x;
		int tmp;
		tmp = index.pos[i].y;
		index.pos[i].y = index.pos[i].z;
		index.pos[i].z = -tmp;
	}
}

//사이즈를 한번만 키운다.
BOOL change = 0;
void banana_index_change(float size) {

	banana_save_index();
	//사이즈를 일괄 키워준다.
	for (int i = 0; i <= (1 + 8 * 5 + 1); i++) {
		index.pos[i].x *= size;
		index.pos[i].y *= size;
		index.pos[i].z *= size;
	}

}


float __tmp;
void banana_head(int pivot_x, int pivot_y, int pivot_z, float size, float degree, int state, float rotate) {
	QUAD temp;
	for (int i = 0; i <= (1 + 8 * 5 + 1); i++) {
		temp.pos[i].x = index.pos[i].x;
		temp.pos[i].y = index.pos[i].y;
		temp.pos[i].z = index.pos[i].z;

	}

	//초기값 닫기
	for (int i = 0; i <= 5; i++) {
		if (state == IDLE) {
			temp.pos[i].y = temp.pos[i].y + sin(degree / 5 * 3.14);
			temp.pos[i].z = temp.pos[i].z + cos(degree / 5 * 3.14);

		}
	}
	for (int i = 0; i < 2; i++) {
		if (i == 1) {

			for (int i = 0; i <= (1 + 8 * 5 + 1); i++) {
				temp.pos[i].x = -temp.pos[i].x;
			}
			glFrontFace(GL_CW);
		}
		else {
			glFrontFace(GL_CCW);
		}
		glPushMatrix(); {
			glTranslated(pivot_x, pivot_y, pivot_z);
			glRotatef(rotate, 0, 1, 0);
			glColor3f(1.0f, 1.0f, 1.0f);

			glBegin(GL_POLYGON); {//아래

				glVertex3f(temp.pos[0].x, temp.pos[0].y, temp.pos[0].z);//그외

				glVertex3f(temp.pos[1].x, temp.pos[1].y, temp.pos[1].z);//그외

				glVertex3f(temp.pos[2].x, temp.pos[2].y, temp.pos[2].z);//그외

			}
			glEnd();

			glBegin(GL_POLYGON); {//아래

				glVertex3f(temp.pos[0].x, temp.pos[0].y, temp.pos[0].z);//중심

				glVertex3f(temp.pos[2].x, temp.pos[2].y, temp.pos[2].z);//그외

				glVertex3f(temp.pos[3].x, temp.pos[3].y, temp.pos[3].z);//그외
			}
			glEnd();

			glBegin(GL_POLYGON); {//아래

				glVertex3f(temp.pos[0].x, temp.pos[0].y, temp.pos[0].z);//중심

				glVertex3f(temp.pos[3].x, temp.pos[3].y, temp.pos[3].z);//그외

				glVertex3f(temp.pos[4].x, temp.pos[4].y, temp.pos[4].z);//그외
			}
			glEnd();

			glBegin(GL_POLYGON); {//아래

				glVertex3f(temp.pos[0].x, temp.pos[0].y, temp.pos[0].z);//중심

				glVertex3f(temp.pos[4].x, temp.pos[4].y, temp.pos[4].z);//그외

				glVertex3f(temp.pos[5].x, temp.pos[5].y, temp.pos[5].z);//그외
			}
			glEnd();


			for (int j = 0; j < 1; j++) {

				glColor3f(j + 0.5 * 0.5, j * 0.2, 0);

				for (int i = 4; i > 0; i--) {


					glBegin(GL_POLYGON); {//아래

						glVertex3f(temp.pos[i + (j * 5)].x, temp.pos[i + (j * 5)].y, temp.pos[i + (j * 5)].z);//중심

						glVertex3f(temp.pos[(i + 1) + (j * 5)].x, temp.pos[(i + 1) + (j * 5)].y, temp.pos[(i + 1) + (j * 5)].z);//그외

						glVertex3f(temp.pos[(i + 1) + ((j + 1) * 5)].x, temp.pos[(i + 1) + ((j + 1) * 5)].y, temp.pos[(i + 1) + ((j + 1) * 5)].z);//그외

						glVertex3f(temp.pos[(i)+((j + 1) * 5)].x, temp.pos[(i)+((j + 1) * 5)].y, temp.pos[(i)+((j + 1) * 5)].z);//그외

					}
					glEnd();
				}
			}

		}
		glPopMatrix();

	}


}
int sign = 1;
float t = 0.f;

void banana_body(int pivot_x, int pivot_y, int pivot_z, float size, float rot_degree, int state, float rotate, float R, float G, float B) {

	QUAD temp;
	for (int i = 0; i <= (1 + 8 * 5 + 1); i++) {
		temp.pos[i].x = index.pos[i].x;
		temp.pos[i].y = index.pos[i].y;
		temp.pos[i].z = index.pos[i].z;

		temp.cl[i].R = index.cl[i].R;
		temp.cl[i].G = index.cl[i].G;
		temp.cl[i].B = index.cl[i].B;

	}
	int mult_default = 1;
	//초기값 닫기

	if (state == IDLE) {

		for (int i = 20; i <= 41 - 4 * 3; i++) {

			if ((i % 5 == 1) || (i % 5 == 2)) {
				temp.pos[i].y = (temp.pos[i].y + (rot_degree / 10));
				temp.pos[i].z = (temp.pos[i].z + (rot_degree / 10));
			}
		}

	}

	for (int i = 0; i < 2; i++) {
		float t__t;
		if (i == 1) {

			for (int i = 0; i <= (1 + 8 * 5 + 1); i++) {
				temp.pos[i].x = -temp.pos[i].x;
			}
			glFrontFace(GL_CW);
			mult_default = -1;
		}
		else {
			glFrontFace(GL_CCW);
			mult_default = 1;
		}


		glPushMatrix(); {

			glTranslated(pivot_x, pivot_y, pivot_z);
			glRotatef(rotate, 0, 1, 0);
			//glRotated(rot_degree, 1, 0, 0);
			for (int j = 1; j < 7; j++) {
				//glColor3f((float)(230 - j * 50) / 255, (float)(230 - j * 20) / 255, (float)(230 - j * 50) / 255);
				//banana_color_
				glColor3f((float)(255 - j * R) / 255, (float)(230 - j * G) / 255, (float)(30 - j * B) / 255);
				for (int i = 4; i > 0; i--) {
				
					glBegin(GL_POLYGON); {//아래

						glVertex3f(temp.pos[i + (j * 5)].x, temp.pos[i + (j * 5)].y, temp.pos[i + (j * 5)].z);//중심
						 
						glVertex3f(temp.pos[(i + 1) + (j * 5)].x, temp.pos[(i + 1) + (j * 5)].y, temp.pos[(i + 1) + (j * 5)].z);//그외

						glVertex3f(temp.pos[(i + 1) + ((j + 1) * 5)].x, temp.pos[(i + 1) + ((j + 1) * 5)].y, temp.pos[(i + 1) + ((j + 1) * 5)].z);//그외

						glVertex3f(temp.pos[(i)+((j + 1) * 5)].x, temp.pos[(i)+((j + 1) * 5)].y, temp.pos[(i)+((j + 1) * 5)].z);//그외

					}
					glEnd();
				}
			}
			glColor3f(0.5f, 0.1f, 0.1f);

			glBegin(GL_POLYGON); {//아래

				glVertex3f(temp.pos[36 + 0].x, temp.pos[36 + 0].y, temp.pos[36 + 0].z);//중심

				glVertex3f(temp.pos[36 + 1].x, temp.pos[36 + 1].y, temp.pos[36 + 1].z);//중심

				glVertex3f(temp.pos[36 + 5].x, temp.pos[36 + 5].y, temp.pos[36 + 5].z);//중심

			}
			glEnd();
			glColor3f(0.5f, 0.1f, 0.1f);

			glBegin(GL_POLYGON); {//아래

				glVertex3f(temp.pos[36 + 1].x, temp.pos[36 + 1].y, temp.pos[36 + 1].z);//중심

				glVertex3f(temp.pos[36 + 2].x, temp.pos[36 + 2].y, temp.pos[36 + 2].z);//중심

				glVertex3f(temp.pos[36 + 5].x, temp.pos[36 + 5].y, temp.pos[36 + 5].z);//중심

			}
			glEnd();
			glColor3f(0.5f, 0.1f, 0.1f);

			glBegin(GL_POLYGON); {//아래

				glVertex3f(temp.pos[36 + 2].x, temp.pos[36 + 2].y, temp.pos[36 + 2].z);//중심

				glVertex3f(temp.pos[36 + 3].x, temp.pos[36 + 3].y, temp.pos[36 + 3].z);//중심

				glVertex3f(temp.pos[36 + 5].x, temp.pos[36 + 5].y, temp.pos[36 + 5].z);//중심

			}
			glEnd();
			glColor3f(0.5f, 0.1f, 0.1f);

			glBegin(GL_POLYGON); {//아래

				glVertex3f(temp.pos[36 + 3].x, temp.pos[36 + 3].y, temp.pos[36 + 3].z);//중심

				glVertex3f(temp.pos[36 + 4].x, temp.pos[36 + 4].y, temp.pos[36 + 4].z);//중심

				glVertex3f(temp.pos[36 + 5].x, temp.pos[36 + 5].y, temp.pos[36 + 5].z);//중심

			}
			glEnd();

			glColor3f(1.f, 1.f, 1.f);
			//팔
			glPushMatrix();
			{
				GLfloat limb_up[4] = { 0 };
				GLfloat limb_mid[4] = { 0 };
				GLfloat limb_down[4] = { 0 };

				limb_up[0] = temp.pos[3 + 3 * 5].x;
				limb_up[1] = temp.pos[3 + 3 * 5].y;
				limb_up[2] = temp.pos[3 + 3 * 5].z;

				limb_down[1] = temp.pos[3 + 5 * 5].y;
				limb_down[2] = temp.pos[3 + 5 * 5].z;
				if (i == 0) {
					limb_down[0] = temp.pos[3 + 5 * 5].x - (size * 5);

				}
				else {
					limb_down[0] = temp.pos[3 + 5 * 5].x + (size * 5);

				}

				if (state == IDLE) {
					limb_down[1] += size * 2 * sin(rot_degree / 4 * 3.141592 * 1) * mult_default;
					limb_down[2] += size * 2 * cos(rot_degree / 4 * 3.141592 * 1) * mult_default;

				}
				//중간 관절 보간
				for (int i = 0; i < 3; i++) {
					limb_mid[i] = (limb_up[i] + limb_down[i]) / 2;
				}
				limb_mid[2] -= (size * 5);
				//그리기 부분
				glLineWidth((size * 2));

				glBegin(GL_LINES);
				{
					glVertex3f(limb_up[0], limb_up[1], limb_up[2]);//상단
					glVertex3f(limb_mid[0], limb_mid[1], limb_mid[2]);//중심
				}
				glEnd();


				glBegin(GL_LINES);
				{
					glVertex3f(limb_mid[0], limb_mid[1], limb_mid[2]);//중심
					glVertex3f(limb_down[0], limb_down[1], limb_down[2]);//말단
				}
				glEnd();
				//핸드
				glTranslatef(limb_down[0], limb_down[1], limb_down[2]);
				glutSolidSphere(size * 3, 10, 10);
			}
			glPopMatrix();

			//다리
			glPushMatrix();
			{
				GLfloat leg_up[4] = { 0 };
				GLfloat leg_mid[4] = { 0 };
				GLfloat leg_down[4] = { 0 };

				leg_up[0] = temp.pos[4 + 5 * 5].x;
				leg_up[1] = temp.pos[4 + 5 * 5].y;
				leg_up[2] = temp.pos[4 + 5 * 5].z;
				
				if (state == IDLE) {
					leg_down[0] = temp.pos[4 + 5 * 5].x;
					leg_down[1] = temp.pos[4 + 5 * 5].y - (size * 10);
					leg_down[2] = temp.pos[4 + 5 * 5].z;
				}
				else if (state == RUN) {
					leg_down[0] = temp.pos[4 + 5 * 5].x;
					leg_down[1] = temp.pos[4 + 5 * 5].y - (size * 10);
					leg_down[2] = temp.pos[4 + 5 * 5].z + rot_degree / 2 * mult_default;
				}

				for (int i = 0; i < 3; i++) {
					leg_mid[i] = (leg_up[i] + leg_down[i]) / 2;
				}
				leg_mid[1] -= (size * 5);

				glLineWidth((size * 2));

				//그리기 부분
				glBegin(GL_LINES);
				{
					glVertex3f(leg_up[0], leg_up[1], leg_up[2]);//상단
					glVertex3f(leg_mid[0], leg_mid[1], leg_mid[2]);//중심
				}
				glEnd();

				glBegin(GL_LINES);
				{
					glVertex3f(leg_mid[0], leg_mid[1], leg_mid[2]);//중심
					glVertex3f(leg_down[0], leg_down[1], leg_down[2]);//말단
				}
				glEnd();
				//핸드
				glTranslatef(leg_down[0], leg_down[1], leg_down[2]);
				glutSolidSphere(size * 3, 10, 10);
			}
			glPopMatrix();

			//표정
			glPushMatrix();
			{
				glColor3f(0, 0, 0);
				glTranslatef((temp.pos[2 + 3 * 5].x + temp.pos[1 + 3 * 5].x) / 2, (temp.pos[2 + 3 * 5].y + temp.pos[1 + 3 * 5].y) / 2, (temp.pos[2 + 3 * 5].z + temp.pos[1 + 3 * 5].z) / 2);
				glRotated(-(temp.pos[2 + 2 * 5].y - temp.pos[1 + 3 * 5].y)*size, 1, 0, 0);
				glTranslatef(0, -size, 0);
				glScalef(0.5, 1.5 *(rot_degree / 2), 0.5);
				if (size > 1) {
					glutSolidCube(size * 1);
				}
				else {
					glutSolidCube(size * 1.5);
				}
			}
			glPopMatrix();

		}
		glPopMatrix();

	}

}
void banana_set_cl(float* R, float* G, float* B)
{
	
	for (int j = 1; j < 7; j++) {
		;
	}
}


void banana_draw(int pivot_x, int pivot_y, int pivot_z, float size, int state, float sub_degree, float rotate, float R, float G,float B) {
	if (state == IDLE) {

		banana_index_change(size);
		banana_head(pivot_x, pivot_y, pivot_z, size, sub_degree / 2, IDLE, rotate);//머리
		banana_body(pivot_x, pivot_y, pivot_z, size, sub_degree * 2, IDLE, rotate  , R, G, B);//몸
	}
}
//오늘은 glPush Pop 짝을 못맞추는 오류를 냈다.
// 바나나가 먹고싶다. 델몬트로