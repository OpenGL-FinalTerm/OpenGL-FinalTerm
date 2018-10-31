#include "stdafx.h"
#include "GLFramework.h"
#ifndef _SCENES_
#include "GLScenesInfo.h"
#endif

using namespace std;

GLFramework::GLFramework(std::string strWinTitle)
{
	m_WinTitle = strWinTitle;
}

GLFramework::~GLFramework()
{
}

void GLFramework::init(int argc, char * argv[], int WinWidth, int WinHeight, bool bFullScreen, int DisplayMode)
{
	m_Timer.reset();

	glutInit(&argc, argv);
	glutInitDisplayMode(DisplayMode);
	glutInitWindowSize(WinWidth, WinHeight);
	glutInitWindowPosition(
		(glutGet(GLUT_SCREEN_WIDTH) - WinWidth) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - WinHeight) / 2
	);
	glutCreateWindow(m_WinTitle.c_str());

	m_Framework = this;
	if(bFullScreen)
		glutFullScreen();

	glewInit();
	glEnable(GL_DEPTH_TEST);
	for (auto scene : SCENES)
		addScene(scene.name, scene.pScene, scene.bInitAtStart);
	toScene(STARTING_SCENE);
}

void GLFramework::run()
{
	glutMainLoop();
}

void GLFramework::draw()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	render();

	glutSwapBuffers();
}

void GLFramework::render()
{
	if (m_Scenes[m_CurrentScene])
		m_Scenes[m_CurrentScene]->render();
}

void GLFramework::reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int d = (w > h) ? w : h;
	glOrtho(0, w, h, 0, -1.f, 1.f);

	glMatrixMode(GL_MODELVIEW);
	if (m_Scenes[m_CurrentScene])
		m_Scenes[m_CurrentScene]->reshape(w, h);
	glutPostRedisplay();
}

void GLFramework::keyboardDown(unsigned char key, int x, int y)
{
	if (m_Scenes[m_CurrentScene])
		m_Scenes[m_CurrentScene]->keyboard(key, true, x, y, false);
}

void GLFramework::keyboardUp(unsigned char key, int x, int y)
{
	if (m_Scenes[m_CurrentScene])
		m_Scenes[m_CurrentScene]->keyboard(key, false, x, y, false);
}

void GLFramework::mouse(int button, int state, int x, int y)
{
	if (m_Scenes[m_CurrentScene])
		m_Scenes[m_CurrentScene]->mouse(button, state==GLUT_DOWN, x, y);
}

void GLFramework::motion(int x, int y)
{
	if (m_Scenes[m_CurrentScene])
		m_Scenes[m_CurrentScene]->motion(true, x, y);
}

void GLFramework::freeMotion(int x, int y)
{
	if (m_Scenes[m_CurrentScene])
		m_Scenes[m_CurrentScene]->motion(false, x, y);
}

void GLFramework::specialDown(int key, int x, int y)
{
	if (m_Scenes[m_CurrentScene])
		m_Scenes[m_CurrentScene]->keyboard(key, true, x, y, true);
}

void GLFramework::specialUp(int key, int x, int y)
{
	if (m_Scenes[m_CurrentScene])
		m_Scenes[m_CurrentScene]->keyboard(key, false, x, y, true);
}

void GLFramework::update(int value)
{
	m_Timer.tick();
	if (m_Scenes[m_CurrentScene])
		m_Scenes[m_CurrentScene]->update(m_Timer.getTimeElapsed());

	std::string fps_title = m_WinTitle + " - ( " + std::to_string(m_Timer.getFPS()) + " FPS )";
	glutSetWindowTitle(fps_title.c_str());
	glutPostRedisplay();
	glutTimerFunc(m_fps, fnTimer, 1);
}

void GLFramework::regDrawFunction(DrawFunc draw)
{
	fnDraw = draw;
}

void GLFramework::regReshapeFunction(ReshapeFunc reshape)
{
	fnReshape = reshape;
}

void GLFramework::regTimerFunction(TimerFunc timer)
{
	fnTimer = timer;
}

void GLFramework::regKeyboardFunction(KeyboardFunc keyboardDown, KeyboardFunc keyboardUp)
{
	fnKeyboardDown = keyboardDown;
	fnKeyboardUp = keyboardUp;
}

void GLFramework::regMouseFunction(MouseFunc mouse)
{
	fnMouse = mouse;
}

void GLFramework::regMotionFunction(MotionFunc motion, MotionFunc freeMotion)
{
	fnMotion = motion;
	fnFreeMotion = freeMotion;
}

void GLFramework::regSpecialFunction(SpecialFunc specialDown, SpecialFunc specialUp)
{
	fnSpecialDown = specialDown;
	fnSpecialUp = specialUp;
}

void GLFramework::bindFunctions()
{
	glutDisplayFunc(fnDraw);
	glutReshapeFunc(fnReshape);
	glutKeyboardFunc(fnKeyboardDown);
	glutKeyboardUpFunc(fnKeyboardUp);
	glutMouseFunc(fnMouse);
	glutMotionFunc(fnMotion);
	glutPassiveMotionFunc(fnFreeMotion);
	glutSpecialFunc(fnSpecialDown);
	glutSpecialUpFunc(fnSpecialUp);
	glutTimerFunc(m_fps, fnTimer, 1);
}

void GLFramework::addScene(std::string strSceneName, GLScene * pScene, bool bInitAtStart)
{
	if (!pScene) return;

	if (bInitAtStart)
	{
		pScene->drawLoadingScreen();
		pScene->init();
	}
		
	pScene->RTLoad = !bInitAtStart;
	m_Scenes.emplace(strSceneName, pScene);	
}

void GLFramework::deleteCurrentScene(std::string strNextScene)
{
	assert(m_Scenes.find(strNextScene) != m_Scenes.end());
	deleteScene(m_CurrentScene);
	m_CurrentScene = strNextScene;
}

void GLFramework::deleteScene(std::string strSceneName)
{
	assert(m_Scenes.find(strSceneName) != m_Scenes.end());
	if (m_Scenes[strSceneName])
		delete m_Scenes[strSceneName];
	m_Scenes.erase(strSceneName);
}

void GLFramework::deleteScenes()
{
	for (auto& pScene : m_Scenes)
		if (pScene.second)
		{
			delete pScene.second;
			pScene.second = nullptr;
		}
}

void GLFramework::toScene(std::string sceneName)
{
	assert(m_Scenes.find(sceneName) != m_Scenes.end());

	if (m_CurrentScene.size() > 0)
	{
		if (m_Scenes[m_CurrentScene]->RTLoad)
			m_Scenes[m_CurrentScene]->exit();
	}

	m_CurrentScene = sceneName;

	if (m_Scenes[m_CurrentScene]->RTLoad)
	{
		m_Scenes[m_CurrentScene]->drawLoadingScreen();
		m_Scenes[m_CurrentScene]->init();
	}
	m_Scenes[m_CurrentScene]->reset();
}
