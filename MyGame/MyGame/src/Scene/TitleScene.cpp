#include "TitleScene.h"
#include "../Input/InputChecker.h"
#include "../Graphic/TextDraw.h"
#include "../Graphic/Sprite.h"

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
	_Counter = 0;
	_CursolPos = Vector2(0.0f,0.0f);
}

void TitleScene::update(float deltaTime)
{

	if (Keyboard::GetInstance().KeyTriggerUp(KEYCODE::UP)) {
		_Counter += 1;
		_CursolPos
	}
	else if (Keyboard::GetInstance().KeyTriggerUp(KEYCODE::DOWN)) {
		_Counter -= 1;
	}
	if (Keyboard::GetInstance().KeyTriggerUp(KEYCODE::A) && _Counter == 0) {
		isEnd_ = true;
	}
}

void TitleScene::draw() const
{
	//UIclassÇçÏê¨Ç∑ÇÈÇ©UpdateÇ≈à⁄ìÆÇ≥ÇπÇÈ
	//TextDraw().Draw(100.0f, -100.0f, "counter" + _counter);
	if (_Counter == 0) {
		Sprite::GetInstance().Draw(SPRITE_ID::TITLE_START,  Vector2(150.0f,100.0f));
		Sprite::GetInstance().Draw(SPRITE_ID::TITLE_END,    Vector2(150.0f, 300.0f));
		Sprite::GetInstance().Draw(SPRITE_ID::TITLE_SELECT, Vector2(50.0f, 100.0f));
	}
	else if (_Counter == 1) {
		Sprite::GetInstance().Draw(SPRITE_ID::TITLE_START,  Vector2(150.0f, 100.0f));
		Sprite::GetInstance().Draw(SPRITE_ID::TITLE_END,    Vector2(150.0f, 300.0f));
		Sprite::GetInstance().Draw(SPRITE_ID::TITLE_SELECT, Vector2(50.0f, 300.0f));
	}

	S/*prite::GetInstance().Draw(SPRITE_ID::TITLE_START, Vector2(150.0f, 100.0f));
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_END, Vector2(150.0f, 300.0f));
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_SELECT, Vector2(50.0f, 100.0f));*/

}

void TitleScene::end()
{
	
}
