#pragma once
#include "stdafx.h"
#include <fstream>
#include <istream>
#include <iostream>
#include "BoxObject.h"
#include "Character.h"
#include "Light.h"
using namespace std;


int LoadMap(Box objectBox[], tmp &tmpRect, int stage);

void LoadLight(Light light[], int i);