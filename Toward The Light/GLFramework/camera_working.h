#pragma once

#include "stdafx.h"
#include <math.h>

//¿ÀÇÁ´×
void opening_camera_Eye(float* start_x, float* start_y, float* start_z, float* end_x, float* end_y, float* end_z, float* t, float* out_x, float* out_y, float* out_z);

void  opening_camera_At(float* start_x, float* start_y, float* start_z, float* end_x, float* end_y, float* end_z, float* t, float* out_x, float* out_y, float* out_z);

//¿£µù
void ending_camera_Eye(float* pos_x, float* pos_y, float* pos_z, float* degree, float* size_w, float* size_h, float* out_x, float* out_y, float* out_z);

void ending_camera_At(float* start_x, float* start_y, float* start_z, float* end_x, float* end_y, float* end_z, float* t, float* out_x, float* out_y, float* out_z);

