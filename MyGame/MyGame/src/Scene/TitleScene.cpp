#include "TitleScene.h"
#include "../Input/InputChecker.h"
#include "../Graphic/TextDraw.h"
#include "../Graphic/Sprite.h"
#include"../Camera/Camera.h"
#include"../Input/DualShock4Manager.h"
#include"../Graphic/Model.h"

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
}

void TitleScene::update(float deltaTime)
{

	if (Keyboard::GetInstance().KeyTriggerUp(KEYCODE::UP)) {
		_Counter += 1;
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

	/*prite::GetInstance().Draw(SPRITE_ID::TITLE_START, Vector2(150.0f, 100.0f));
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_END, Vector2(150.0f, 300.0f));
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_SELECT, Vector2(50.0f, 100.0f));*/
	
	Camera::GetInstance().Position.Set(Vector3(0, 0, 30));

	Camera::GetInstance().Target.Set(Vector3::Zero);
	Camera::GetInstance().SetRange(0.1f, 1000.0f);
	Camera::GetInstance().SetViewAngle(60.0f);
	Camera::GetInstance().Up.Set(Vector3::Up);

	Camera::GetInstance().Update();
	Vector3 seg = Vector3::Forward*20.0f;
	seg = seg*DualShock4Manager::GetInstance().gyroMat_;

	DrawLine3D(Vector3::Zero, seg, GetColor(255, 255, 255));
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, DualShock4Manager::GetInstance().gyroMat_);
	//DrawCapsule3D(-seg/2, seg/2,2, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);

}

void TitleScene::end()
{
	
}
