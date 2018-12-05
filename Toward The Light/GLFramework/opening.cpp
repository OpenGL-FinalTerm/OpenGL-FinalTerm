#include "opening.h"

float ending_camera_Eye(float start_x, float start_y, float start_z, float end_x, float end_y, float end_z, float t, float out_x, float out_y, float out_z) {

	out_x = (1 - t) * start_x + t * end_x;

	out_z = (1 - t) * start_z + t * end_z;

	out_y =
		((start_y * pow((1 - t), 3)) + //실린더 위치
		(3 * (130) * t * pow((1 - t), 2)) + //제어점 1
			(3 * (180) * pow(t, 2) * (1 - t)) + //제어점 2
			(end_y * pow(t, 3)) //도착지점
			);

	return out_x ,out_y, out_z;

}
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

void  ending_camera_At(float start_x, float start_y, float start_z, float end_x, float end_y, float end_z, float t, float* out_x, float* out_y, float* out_z) {
	*out_x = (1 - t) *  (start_x) + t * (end_x);
	*out_z = (1 - t) *  (start_z) + t * (end_z);
	*out_y = 10;

	//return out_x, out_y, out_z;

}