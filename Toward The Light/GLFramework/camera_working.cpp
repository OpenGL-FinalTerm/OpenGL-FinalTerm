#include "camera_working.h"

void opening_camera_Eye(float* start_x, float* start_y, float* start_z, float* end_x, float* end_y, float* end_z, float* t, float contrl_pt, float* out_x, float* out_y, float* out_z) {

	*out_x = (1 - *t) * (*start_x + 1) + *t * *end_x;
	*out_z = (1 - *t) * (*start_z + 1) + *t * *end_z;

	//*out_y =
	//   ((*start_y * pow((1 - *t), 3)) + //실린더 위치
	//   (3 * ((contrl_pt + *start_y)/2 ) * *t * pow((1 - *t), 2)) + //제어점 1
	//      (3 * ((contrl_pt + *end_y) / 2) * pow(*t, 2) * (1 - *t)) + //제어점 2
	//      (*end_y * pow(*t, 3)) //도착지점
	//      );

	*out_y =
		((-pow(*t, 3) + 2 * pow(*t, 2) - *t)* *start_y +
		(3 * pow(*t, 3) - 5 * pow(*t, 2) + 2) * ((contrl_pt + *start_y) / 2) +
			(-3 * pow(*t, 3) + 4 * pow(*t, 2) + *t)* ((contrl_pt + *end_y) / 2) +
			(pow(*t, 3) - pow(*t, 2))* *end_y
			) / 2;
}
//스플라인
//직선 구하는 함수
   // pt = (1 - t ) * p0 + t * p1
//pt = ((pow((1 - t) .2) * p0) + (2 * t * (1 - t) * p1) + (pow(t, 2) * p2))
/*
pt =
((p0 * pow((1-t), 3))+
 (3 * p1 * t * pow((1-t), 2)) +
 (3 * p2 * pow(t, 2) * (1 - t)) +
 (p3 * pos(t, 3))
 )
*/
//카디널
/*
pt =(
((2 * pow(t, 2) - 3 * t + 1) * p0) +
((-4 * (pow(t,2) + 4 * t))*p1) +
((2 * (pow(t, 2)) - t ) * p2)
)
(2*pow(t, 2)-3*t+1)*p1[0]+(-4*pow(t, 2)+4*t)*p2[0]+(2*pow(t, 2)-t)*p3[0]
*/

void  opening_camera_At(float* start_x, float* start_y, float* start_z, float* end_x, float* end_y, float* end_z, float* t, float* out_x, float* out_y, float* out_z) {
	*out_x = (1 - *t) * (*start_x + 1) + *t * (*end_x);
	*out_z = (1 - *t) * (*start_z + 1) + *t * (*end_z);
	*out_y = 10;

	//return out_x, out_y, out_z;

}


void ending_camera_Eye(float* pos_x, float* pos_y, float* pos_z, float* degree, float* size_w, float* size_h, float* out_x, float* out_y, float* out_z) {
	//카메라 연산
	*degree += 0.1f;
	if (*size_w >= 100) {
		*size_w -= 0.1f;
	}
	else if (*size_w <= 100) {
		if (*size_w >= 50) {
			*size_w -= 1;
			*size_h += 1;
		}
	}

	*out_x = *pos_x + sin(*degree * 3.141592 / 180) * *size_w;
	*out_z = *pos_z + cos(*degree * 3.141592 / 180) * *size_w;
	*out_y = *size_h + *pos_y;
	//

}
void ending_camera_At(float* start_x, float* start_y, float* start_z, float* end_x, float* end_y, float* end_z, float* t, float* out_x, float* out_y, float* out_z) {

	if (*t <= 1) {
		*out_x = (1 - *t) *  (*start_x) + *t * (*end_x);
		*out_z = (1 - *t) *  (*start_z) + *t * (*end_z);
		*out_y = 0;

		*t += 0.01f;
	}
	//return out_x, out_y, out_z;
}

void camera_moving_Eye(float* pos_x, float* pos_y, float* pos_z, float* degree, int* size_w, int* size_y, float* out_x, float* out_y, float* out_z) {
	*out_x = -sin(*degree * 3.141592 / 180) * (*size_w + 0.1) + *pos_x;
	*out_y = *pos_y + *size_y;
	*out_z = -cos(*degree * 3.141592 / 180) * (*size_w + 0.1) + *pos_z;
}

void camera_moving_At(float* pos_x, float* pos_y, float* pos_z, float* degree, int* size_w, int* size_y, float* out_x, float* out_y, float* out_z) {
	*out_x = sin(*degree * 3.141592 / 180) * (*size_w) + *pos_x;
	*out_y = *size_y;
	*out_z = cos(*degree * 3.141592 / 180) * (*size_w) + *pos_z;
}

void camera_parabolic2(float* start_x, float* start_y, float* start_z, float* end_x, float* end_y, float* end_z, float* t, float contrl_pt, float* out_x, float* out_y, float* out_z) {

	if (*t <= 1.f) {
		*out_x = (1 - *t) * (*start_x + 1) + *t * *end_x;
		*out_z = (1 - *t) * (*start_z + 1) + *t * *end_z;

		*out_y = (2 * pow(*t, 2) - 3 * *t + 1)* *start_y + (-4 * pow(*t, 2) + 4 * *t)* contrl_pt + (2 * pow(*t, 2) - *t)* *end_y;

	}

	*t += 0.001f;

}