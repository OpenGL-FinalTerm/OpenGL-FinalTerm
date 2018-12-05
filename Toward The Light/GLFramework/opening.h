#pragma once

#include "stdafx.h"
#include <math.h>

float ending_camera_Eye(float start_x, float start_y, float start_z, float end_x, float end_y, float end_z, float t, float out_x, float out_y, float out_z);

void ending_camera_At(float start_x, float start_y, float start_z, float end_x, float end_y, float end_z, float t, float* out_x, float* out_y, float* out_z);
