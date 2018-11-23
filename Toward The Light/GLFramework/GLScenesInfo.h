#pragma once
#define _SCENES_
/*--------------------ADD SCENES HERE--------------------*/

/*~~~~~HEADER FILES~~~~*/
#include "Scene00_Main.h"
#include "Scene01.h"
#include "Scene02.h"
#include "Scene03.h"


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
};

/*~~~STARTING SCENE~~~*/
const std::string STARTING_SCENE { "Main" };

/*-------------------------------------------------------*/
