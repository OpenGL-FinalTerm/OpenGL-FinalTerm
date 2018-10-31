#pragma once

class GLFramework;

/* GLOBAL VARIABLES */
extern GLFramework*	 m_Framework;
/* ---------------- */

class GLScene
{
public:
	GLScene() {}
	virtual ~GLScene() {}
	virtual void init() {}
	virtual void exit() {}
	virtual void reset() {}
	virtual void render() {}
	virtual void reshape(int w, int h) {}
	virtual void keyboard(int key, bool pressed, int x, int y, bool special) {}
	virtual void mouse(int button, bool pressed, int x, int y) {}
	virtual void motion(bool pressed, int x, int y) {}
	virtual void update(float fDeltaTime) {}

	void drawLoadingScreen();

	virtual void loading(); // Testing. Very basic Loading Screen. It's virtual so each Scene may have a Different Loading Screen if desired.

	void print(std::string str, float x, float y, float z) const; // for debugging purposes only

public:
	bool RTLoad		{ false };	// if to load when program starting or while in Runtime
};
