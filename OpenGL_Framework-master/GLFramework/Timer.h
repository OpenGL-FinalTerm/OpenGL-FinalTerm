#pragma once

class Timer {

	typedef std::chrono::high_resolution_clock	Time;
	typedef std::chrono::duration<float>		fsec;

public:
	Timer(bool run = false);
	~Timer();

	void reset();
	void tick();
	int	 getFPS() const;
	float getTimeElapsed() const;

private:
	Time::time_point	m_tpCurrent;
	Time::time_point	m_tpPrevious;
	fsec				m_fsFPSTimeElapsed;
	fsec				m_fsTimeElapsed;
	int					m_nCurrentFPS;
	int					m_nFrames;
};