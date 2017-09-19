#include "TitleScene.h"
#include "../Input/Keyboard.h"
#include "../Graphic/TextDraw.h"

TitleScene::TitleScene()
{
	next_ = SceneType::SCENE_GAMEPLAY;
}

TitleScene::~TitleScene()
{
}

void TitleScene::start()
{
	isEnd_ = false;
	_counter = 0;
}

void TitleScene::update(float deltaTime)
{
	if (Keyboard::GetInstance().KeyTriggerUp(KEYCODE::UP)) {
		_counter += 1;
	}
	else if (Keyboard::GetInstance().KeyTriggerUp(KEYCODE::DOWN)) {
		_counter -= 1;
	}

	if (Keyboard::GetInstance().KeyTriggerUp(KEYCODE::A)) {
		isEnd_ = true;
	}

}

void TitleScene::draw() const
{
	TextDraw().Draw(100.0f, -100.0f, "counter" + _counter);
}

void TitleScene::end()
{
	
}
