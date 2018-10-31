#pragma once
#include "Timer.h"

class GLScene;

class GLFramework
{
public:
	GLFramework(std::string strWinTitle = "Default Title");
	~GLFramework();

	void init(int argc, char* argv[], int WinWidth, int WinHeight, bool bFullScreen = false, int DisplayMode = GLUT_DOUBLE | GLUT_RGBA);

	void run();
	void draw();
	void render();
	void reshape(int w, int h);

	void keyboardDown(unsigned char key, int x, int y);
	void keyboardUp(unsigned char key, int x, int y);

	void mouse(int button, int state, int x, int y);
	void motion(int x, int y);
	void freeMotion(int x, int y);

	void specialDown(int key, int x, int y);
	void specialUp(int key, int x, int y);

	void update(int deltaTime);

	/*------------------------------------------------------- */

	using SceneMap = std::map<std::string, GLScene*>;

	using TimerFunc = void(*)(int);
	using DrawFunc = void(*)();
	using ReshapeFunc = void(*)(int, int);
	using KeyboardFunc = void(*)(unsigned char key, int x, int y);
	using MouseFunc = void(*)(int button, int state, int x, int y);
	using MotionFunc = void(*)(int x, int y);
	using SpecialFunc = void(*)(int key, int x, int y);

	void regDrawFunction(DrawFunc draw);
	void regReshapeFunction(ReshapeFunc reshape);
	void regTimerFunction(TimerFunc timer);
	void regKeyboardFunction(KeyboardFunc keyboardDown, KeyboardFunc keyboardUp);
	void regMouseFunction(MouseFunc mouse);
	void regMotionFunction(MotionFunc motion, MotionFunc freeMotion);
	void regSpecialFunction(SpecialFunc specialDown, SpecialFunc specialUp);
	void bindFunctions();

	void addScene(std::string strSceneName, GLScene * pScene, bool bInitAtStart=true);
	void deleteCurrentScene(std::string strNextScene);
	void deleteScene(std::string strSceneName);
	void deleteScenes();
	void toScene(std::string sceneName);

private:

	int				m_fps{ 10 };
	DrawFunc		fnDraw{ nullptr };
	ReshapeFunc		fnReshape{ nullptr };
	TimerFunc		fnTimer{ nullptr };
	KeyboardFunc	fnKeyboardDown{ nullptr };
	KeyboardFunc	fnKeyboardUp{ nullptr };
	MouseFunc		fnMouse{ nullptr };
	MotionFunc		fnMotion{ nullptr };
	MotionFunc		fnFreeMotion{ nullptr };
	SpecialFunc		fnSpecialUp{ nullptr };
	SpecialFunc		fnSpecialDown{ nullptr };

private:

	SceneMap			m_Scenes;
	std::string			m_CurrentScene;
	std::string			m_WinTitle;
	bool				m_FullScreen{ true };

	Timer				m_Timer;
};


