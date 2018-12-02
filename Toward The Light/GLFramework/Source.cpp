#include "stdafx.h"
#include "GLFramework.h"
#include <windows.h>




using namespace std;

//........................이름 바꾸는 장소
GLFramework fw("Toward The Light");
// 여긴 찾기 힘들겟지
// 진짜 D-6인데... 심지어 마감일 일요일 11시 50분까지인데....
// 매일매일 고민...............
// 과연 통학과 기숙사와 다른점은 무엇인가.... (통학취침시간 == 기숙사취침시간)....
// 통학을 했으면 어떗으려나

int main(int argc, char* argv[])
{
	fw.init(argc, argv, DEF_WIN_WIDTH, DEF_WIN_HEIGHT); //초기화

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