#pragma once
#include "Sound.h"

class FolderReader;

class SoundPlayer
{

public:

	SoundPlayer();
	~SoundPlayer();

	void init();
	void exit();
	void selectFolder(std::string strFolderPath, bool isMusic = true);

	/* PLAYER CONTROLS ----------- */
	void play();
	void unpause(); 
	void pause();
	void stop();
	bool next();
	bool prev();
	void setLoop(bool bLoopState);
	void shuffle();
	void unshuffle();
	/* --------------------------- */

	bool playing();

	std::string getSoundFilename() const;
	std::string getSoundFilename(size_t index) const;
	size_t getSoundCount() const;

private:
	Sound							m_SoundManager;
	std::unique_ptr<FolderReader>	m_SoundFolder;
	std::vector<size_t>				m_SoundPlayOrder;
	std::vector<std::string>		m_SoundFilenames;
	size_t							m_CurrentSoundIdx;
	bool							m_bMusic;
	bool							m_bLoop;
	bool							m_bPaused;
};
