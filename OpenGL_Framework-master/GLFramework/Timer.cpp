#include "stdafx.h"
#include "Timer.h"

Timer::Timer(bool run)
{
	m_nFrames = 0;
	if (run) reset();
}

Timer::~Timer()
{
}

void Timer::reset()
{
	m_nFrames = 0;
	m_tpPrevious = Time::now();
	m_fsFPSTimeElapsed = fsec::zero();
	m_fsTimeElapsed = fsec::zero();
}

void Timer::tick()
{
	m_tpCurrent = Time::now();

	m_nFrames++;

	m_fsFPSTimeElapsed += (m_tpCurrent - m_tpPrevious);
	m_fsTimeElapsed = (m_tpCurrent - m_tpPrevious);
	m_tpPrevious = m_tpCurrent;
	if (m_fsFPSTimeElapsed.count() >= 1.f)
	{
		m_fsFPSTimeElapsed = fsec::zero();
		m_nCurrentFPS = m_nFrames;
		m_nFrames = 0;
	}
}

int Timer::getFPS() const
{
	return m_nCurrentFPS;
}

float Timer::getTimeElapsed() const
{
	return m_fsTimeElapsed.count();
}


