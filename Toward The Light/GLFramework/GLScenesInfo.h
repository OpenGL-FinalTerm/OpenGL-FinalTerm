#pragma once
#define _SCENES_
/*--------------------ADD SCENES HERE--------------------*/

/*~~~~~HEADER FILES~~~~*/
#include "Scene00_Main.h"
#include "Scene01.h"
#include "Scene02.h"
#include "Scene03.h"
#include "Scene04_Ending.h"
#include "Scene_Setting.h";
#include "Scene_Start.h"
#include "Scene05_clear.h"

struct GLSceneInfo
{
	std::string name;
	GLScene*	pScene;
	bool		bInitAtStart{ true };
};

/*~~~~~~~SCENES~~~~~~~*/
const GLSceneInfo SCENES[] =
{
	{"Main", new S00Logo, true},
	{"1", new S01Main, false},
	{"2", new S02Main, false},
	{"3", new S03Main, false},
	{"Ending", new S04End, false},
	{"Setting", new S05Setting, false},
	{"Start", new S06Start, false},
	{"Clear", new S05End, false}
};

/*~~~STARTING SCENE~~~*/
const std::string STARTING_SCENE { "Start" };

/*-------------------------------------------------------*/
