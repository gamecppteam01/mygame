#include"src\Game\MyGame.h"
#include"src\Define.h"
#pragma comment(linker,"/entry:mainCRTStartup")

int main() {
	MyGame(SCREEN_SIZE, WINDOW_RATE, WINDOW_MODE).run();
}