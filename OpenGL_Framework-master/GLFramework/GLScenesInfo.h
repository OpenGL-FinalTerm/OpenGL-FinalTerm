#pragma once
#define _SCENES_
/*--------------------ADD SCENES HERE--------------------*/

/*~~~~~HEADER FILES~~~~*/
#include "Scene00_Logo.h"
#include "Scene01_Main.h"

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
	{"Main", new S01Main, false}
};

/*~~~STARTING SCENE~~~*/
const std::string STARTING_SCENE { "Logo" };

/*-------------------------------------------------------*/
