#include"src/Game/MyGame.h"
#include"src/Define.h"
#include"src/Conv/ByteConverter.h"

#pragma comment(linker,"/entry:mainCRTStartup")

int main() {
	//std::string name{ "‚ " };
	//int f = name.front();
	//int b = name.back();
	//auto nm=ByteConverter::String_to_Int(name);
	//auto tx = ByteConverter::Int_to_String(nm);
	//OutputDebugString(name.c_str());
	//name.back() -= 1;
	//OutputDebugString(name.c_str());
	//name.back() += 1;
	//name.back() += 1;
	//OutputDebugString(name.c_str());


	return MyGame(SCREEN_SIZE, WINDOW_RATE, WINDOW_MODE).run();
}