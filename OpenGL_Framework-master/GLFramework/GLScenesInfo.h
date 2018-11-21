#pragma once
#define _SCENES_
/*--------------------ADD SCENES HERE--------------------*/

/*~~~~~HEADER FILES~~~~*/
#include "Scene00_Logo.h"
#include "Scene01_Main.h"
#include "Scene01_Map1.h"
#include "Scene01_Map2.h"
#include "Scene01_Map3.h"

struct GLSceneInfo
{
	std::string name;
	GLScene*	pScene;
	bool		bInitAtStart{ true };
};

/*~~~~~~~SCENES~~~~~~~*/
const GLSceneInfo SCENES[] =
{
	{"Logo", new S00Logo, true},
	{"Main", new S01Main, false},
	{"Map1", new S01Map1, false},
	{"Map2", new S01Map2, false},
	{"Map3", new S01Map3, false}
};

/*~~~STARTING SCENE~~~*/
const std::string STARTING_SCENE { "Logo" };

/*-------------------------------------------------------*/
