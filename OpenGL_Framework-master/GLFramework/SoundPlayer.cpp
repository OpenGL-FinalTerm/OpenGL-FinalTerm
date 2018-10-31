#include "stdafx.h"
#include "SoundPlayer.h"
#include "FolderReader.h"
#include <random>

void SoundPlayer::play()
{
	if (m_CurrentSoundIdx >= m_SoundFilenames.size())
		return;
	m_SoundManager.play(m_SoundPlayOrder[m_CurrentSoundIdx], m_bMusic);
}

void SoundPlayer::unpause()
{
	m_SoundManager.unpause();
}

void SoundPlayer::pause()
{
	m_SoundManager.pause();
}

void SoundPlayer::stop()
{
	m_SoundManager.stop(false);
}

bool SoundPlayer::next()
{
	if (m_CurrentSoundIdx >= m_SoundFilenames.size())
		return false;

	if (m_CurrentSoundIdx == m_SoundFilenames.size() - 1)
	{
		if (m_bLoop)
			m_CurrentSoundIdx = -1;
		else
			return false;
	}
	++m_CurrentSoundIdx;
	m_SoundManager.stop(false);
	m_SoundManager.play(m_SoundPlayOrder[m_CurrentSoundIdx], m_bMusic);
	return true;
}

bool SoundPlayer::prev()
{	
	if (m_CurrentSoundIdx >= m_SoundFilenames.size())
		return false;

	if (m_CurrentSoundIdx == 0)
	{
		if (m_bLoop) 
			m_CurrentSoundIdx = m_SoundFilenames.size();
		else
			return false;
	}
	--m_CurrentSoundIdx;
	m_SoundManager.stop(false);
	m_SoundManager.play(m_SoundPlayOrder[m_CurrentSoundIdx], m_bMusic);
	return true;
}

void SoundPlayer::setLoop(bool bLoopState)
{
	m_bLoop = bLoopState;
}

void SoundPlayer::shuffle()
{
	if (m_CurrentSoundIdx >= m_SoundFilenames.size())
		return;

	std::random_device rd;
	std::default_random_engine dre(rd());
	size_t szCurrentSound = m_SoundPlayOrder[m_CurrentSoundIdx];
	std::shuffle(m_SoundPlayOrder.begin(), m_SoundPlayOrder.end(), dre);
	ptrdiff_t pos = std::distance(m_SoundPlayOrder.begin(), std::find(m_SoundPlayOrder.begin(), m_SoundPlayOrder.end(), szCurrentSound));
	szCurrentSound = static_cast<size_t>(pos);
	
	size_t temp = m_SoundPlayOrder[0];
	m_SoundPlayOrder[0] = m_SoundPlayOrder[szCurrentSound];
	m_SoundPlayOrder[szCurrentSound] = temp;
	m_CurrentSoundIdx = 0;
	
}

void SoundPlayer::unshuffle()
{
	std::sort(m_SoundPlayOrder.begin(), m_SoundPlayOrder.end());
}

bool SoundPlayer::playing()
{
	return m_SoundManager.playing();
}

std::string SoundPlayer::getSoundFilename() const
{
	if (m_CurrentSoundIdx >= m_SoundFilenames.size())
		return std::string();

	return getSoundFilename(m_SoundPlayOrder[m_CurrentSoundIdx]);
}

std::string SoundPlayer::getSoundFilename(size_t index) const
{
	if(index >= m_SoundFilenames.size())
		return std::string();
	return m_SoundFilenames.at(index);
}

size_t SoundPlayer::getSoundCount() const
{
	return m_SoundFilenames.size();
}

SoundPlayer::SoundPlayer()
{
}

SoundPlayer::~SoundPlayer()
{
}

void SoundPlayer::selectFolder(std::string strFolderPath, bool isMusic)
{
	m_SoundFilenames.clear();
	m_SoundFilenames = m_SoundFolder->readFolder(strFolderPath, "mp3");
	size_t idx = 0;
	m_bMusic = isMusic;

	for (auto strSoundFilename : m_SoundFilenames)
	{
		std::string strFullSoundFilepath;
		strFullSoundFilepath = strFolderPath + "/" + strSoundFilename;
		m_SoundManager.addSound(strFullSoundFilepath.c_str(), m_bMusic);
		m_SoundPlayOrder.push_back(idx);
		++idx;
	}
}

void SoundPlayer::init()
{
	m_CurrentSoundIdx = 0;
	m_bLoop = false;
	m_bPaused = false;
	m_bMusic = false;
	m_SoundManager.init();
}

void SoundPlayer::exit()
{
	m_SoundManager.exit();
	m_SoundPlayOrder.clear();
	m_SoundFilenames.clear();	
}

