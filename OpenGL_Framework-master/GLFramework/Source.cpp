#include "stdafx.h"
#include "GLFramework.h"

constexpr auto DEF_WIN_WIDTH	{ 800 };
constexpr auto DEF_WIN_HEIGHT	{ 600 };

using namespace std;

GLFramework fw("OpenGL Framework Test");

int main(int argc, char* argv[])
{
	fw.init(argc, argv, DEF_WIN_WIDTH, DEF_WIN_HEIGHT);

	fw.regDrawFunction([]() { fw.draw(); });

	fw.regReshapeFunction([](int w, int h) { fw.reshape(w, h); });

	fw.regTimerFunction([](int value) { fw.update(value); });

	fw.regKeyboardFunction([](unsigned char key, int x, int y) { fw.keyboardDown(key, x, y); },
		[](unsigned char key, int x, int y) { fw.keyboardUp(key, x, y); });

	fw.regSpecialFunction([](int key, int x, int y) { fw.specialDown(key, x, y); },
		[](int key, int x, int y) { fw.specialUp(key, x, y); });

	fw.regMouseFunction([](int button, int state, int x, int y) { fw.mouse(button, state, x, y); });

	fw.regMotionFunction([](int x, int y) { fw.motion(x, y); },
		[](int x, int y) { fw.freeMotion(x, y); });

	fw.bindFunctions();

	fw.run();
}