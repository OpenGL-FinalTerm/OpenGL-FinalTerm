#include "stdafx.h"
#include "Scene02.h"
#include "GLFramework.h"

S02Main::S02Main()
{
}


S02Main::~S02Main()
{
}

void S02Main::init()
{
	m_SoundPlayer.init();
	m_SoundPlayer.selectFolder("Resources\\BGM");
}

void S02Main::exit()
{
	m_SoundPlayer.exit();
}

void S02Main::reset()
{
	m_SoundPlayer.play();
}

void S02Main::render()
{
	m_Camera.ready();
}

void S02Main::reshape(int w, int h)
{

}

void S02Main::keyboard(int key, bool pressed, int x, int y, bool special)
{
}

void S02Main::mouse(int button, bool pressed, int x, int y)
{
}

void S02Main::motion(bool pressed, int x, int y)
{
}

void S02Main::update(float fDeltaTime)
{
}