#include "stdafx.h"
#include "Sound.h"

/* SOUND */

Sound::Sound()
{
	init();
}

Sound::~Sound()
{
	exit();
}

int Sound::addSound(LPCSTR path, bool isBGM)
{
	FMOD_RESULT res;
	m_Sounds.emplace_back(nullptr);
	++m_SoundsIdx;

	if (isBGM)
		res = m_SoundSystem->createStream(path, FMOD_DEFAULT | FMOD_2D, nullptr, &m_Sounds[m_SoundsIdx]);
	else
		res = m_SoundSystem->createSound(path, FMOD_DEFAULT, nullptr, &m_Sounds[m_SoundsIdx]);

	if (res == FMOD_OK) return m_SoundsIdx;
	else return -1;
}

void Sound::init()
{
	FMOD::System_Create(&m_SoundSystem);
	m_SoundSystem->init(FMOD_MAX_CHANNEL_WIDTH,
		FMOD_INIT_NORMAL, nullptr);
	for (auto& p : m_Sounds)
		p = nullptr;
}

void Sound::exit()
{
	stop(true);
	for (auto& p : m_Sounds) {
		if (p) p->release();
		p = nullptr;
	}
	m_SoundSystem->close();
	m_SoundSystem->release();
	m_Sounds.clear();
	m_SoundsIdx = -1;
}

void Sound::stop(bool master_stop)
{
	if (!m_SoundChannel) return;
	bool nowPlaying;
	m_SoundChannel->isPlaying(&nowPlaying);
	if (nowPlaying)
		m_SoundChannel->stop();
	if (!master_stop) return;

	FMOD::ChannelGroup* cg_master{ nullptr };
	m_SoundSystem->getMasterChannelGroup(&cg_master);
	cg_master->stop();
}

void Sound::play(size_t idx, bool isMusic)
{
	if (idx < 0 && idx >= m_Sounds.size()) return;
	if (isMusic)
		m_SoundSystem->playSound(m_Sounds[idx], nullptr, false, &m_SoundChannel);
	else
		m_SoundSystem->playSound(m_Sounds[idx], nullptr, false, nullptr);
	m_isPaused = false;
}

void Sound::pause()
{
	if (!m_SoundChannel) return;
	m_SoundChannel->setPaused(true);
	m_isPaused = true;
}

void Sound::unpause()
{
	if (!m_SoundChannel) return;
	m_SoundChannel->setPaused(false);
	m_isPaused = false;
}

void Sound::fadeOut(int samples)
{
	if (!m_SoundChannel) return;
	m_SoundChannel->getDSPClock(NULL, &m_ParentClock);
	m_SoundChannel->addFadePoint(m_ParentClock, 1);
	m_SoundChannel->addFadePoint(m_ParentClock + samples, 0);
	m_SoundChannel->setDelay(0, m_ParentClock + samples, true);
}

bool Sound::playing() const
{
	if (!m_SoundChannel) return false;
	bool bPlaying;
	m_SoundChannel->isPlaying(&bPlaying);
	return bPlaying && !m_isPaused;
}