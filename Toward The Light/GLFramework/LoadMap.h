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

int LoadLight(Light mapLight[], int i);