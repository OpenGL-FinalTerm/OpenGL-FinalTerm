#include "stdafx.h"
#include "Scene01_Main.h"
#include "GLFramework.h"

S01Main::S01Main()
{
}

S01Main::~S01Main()
{
}

void S01Main::init()
{
	m_SoundPlayer.init();
	m_SoundPlayer.selectFolder("Resources");

	m_Princess.load("Resources/model.obj", "Resources/texture.png"); 

	m_Camera.setDistance(3000.f);
	m_Camera.setPerspective(30.f, 0.125f, 7'000.f);
	m_Camera.setSensitivity(10.f);


	for (size_t i = 0; i < 10; ++i)
	{
		m_Object[i].setModel(&m_Princess);
		m_Object[i].setPosition(i*300.f - 1500.f, 0.f, 0.f);
	}
}

void S01Main::exit()
{
	m_Princess.kill();
	m_SoundPlayer.exit();
}

void S01Main::reset()
{
	m_SoundPlayer.play();
}

void S01Main::render()
{
	m_Camera.ready();
	print(m_SoundPlayer.getSoundFilename(), 0, 500, 200);
	for(size_t i = 0; i<10; ++i)
		m_Object[i].render();
}

void S01Main::reshape(int w, int h)
{

}

void S01Main::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if(pressed)
		switch (key)
		{
			case 'w': m_SoundPlayer.setLoop(true); break;
			case '2': m_SoundPlayer.setLoop(false); break;
			case 'e': m_SoundPlayer.unpause(); break;
			case 'q': m_SoundPlayer.pause(); break;
			case 'a': m_SoundPlayer.prev(); break;
			case 's': m_SoundPlayer.shuffle(); break;
			case 'x': m_SoundPlayer.unshuffle(); break;
			case 'd': m_SoundPlayer.next(); break;
			case ' ': m_Framework->toScene("Logo"); break;
		}
}

void S01Main::mouse(int button, bool pressed, int x, int y)
{
}

void S01Main::motion(bool pressed, int x, int y)
{
	m_Camera.rotate(x, y, pressed);
}

void S01Main::update(float fDeltaTime)
{
}