#include"src/Game/MyGame.h"
#include"src/Define.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	return MyGame(SCREEN_SIZE, WINDOW_RATE, WINDOW_MODE).run();
}