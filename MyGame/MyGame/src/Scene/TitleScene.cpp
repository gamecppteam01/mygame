#include "TitleScene.h"
#include "../Input/InputChecker.h"
#include "../Graphic/TextDraw.h"
#include "../Graphic/Sprite.h"
#include"../Camera/Camera.h"
#include"../Input/DualShock4Manager.h"
#include"../Graphic/Model.h"
#include"../Graphic/EffekseerManager.h"
#include "../Math/Easing.h"

TitleScene::TitleScene()
{
	next_ = SceneType::SCENE_GAMEPLAY;
	//next_ = SceneType::SCENE_CLEAR;

	titleState_ = TitleState::first;
	SinCount_ = 0;

}

TitleScene::~TitleScene()
{

}

void TitleScene::start()
{
	isEnd_ = false;
	titleState_ = TitleState::first;
	cursor_ = 0;
}


void TitleScene::update(float deltaTime)
{
	float t = 0.0f;
	
	//初期状態
	if (titleState_ == TitleState::first) {
		if (titleState_ == TitleState::first &&
			Keyboard::GetInstance().KeyTriggerDown(KEYCODE::F) ||
			InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
			titleState_ = TitleState::second;
			return;
		}
	}
	//二段階目
	else if (titleState_ == TitleState::second)
	{
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::W) ||
			InputChecker::GetInstance().GetPovTriggerDownAngle() == 0) {
			cursor_=(cursor_-1+ cursorPoses.size())% cursorPoses.size();
		}
		else if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::S) ||
			InputChecker::GetInstance().InputChecker::GetInstance().GetPovTriggerDownAngle() == 180)
		{
			cursor_=(cursor_+1)%cursorPoses.size();
		}

		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::F) ||
			InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
			//シーン遷移
			isEnd_ = true;
			auto next = cursorPoses[cursor_].second;
			if (next == SceneType::SCENE_EXIT)exit(0);
			else next_ = next;
		}
	}
	temp = MathHelper::Sin(SinCount_);
	//min(temp, 0.0f);
	SinCount_+=3;
}

void TitleScene::draw() const
{
	//タイトル
	Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::TITLE_SCREEN)/2;
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_SCREEN, Vector2(WINDOW_WIDTH/2,WINDOW_HEIGHT/2), origin, 1.0f,Vector2::One*1.3f);
	//はじめる
	if (titleState_ == TitleState::first) {
		origin = Sprite::GetInstance().GetSize(SPRITE_ID::START_SPRITE) / 2;
		Sprite::GetInstance().Draw(SPRITE_ID::START_SPRITE, Vector2(WINDOW_WIDTH/2, 600.0f),origin, std::abs(temp),Vector2::One);
	}
	//ステージ選択か終了
	if (titleState_ == TitleState::second) {
		origin = Sprite::GetInstance().GetSize(SPRITE_ID::BUTTON_A) / 2;
		Sprite::GetInstance().Draw(SPRITE_ID::BUTTON_A, cursorPoses[cursor_].first, origin, 1.0f,Vector2::One);
	
		origin = Sprite::GetInstance().GetSize(SPRITE_ID::START_SPRITE) / 2;
		Sprite::GetInstance().Draw(SPRITE_ID::START_SPRITE, Vector2(WINDOW_WIDTH/2,cursorPoses[0].first.y),origin, cursor_==0 ? std::abs(temp):1.0f,Vector2::One);
		origin = Sprite::GetInstance().GetSize(SPRITE_ID::END_SPRITE) / 2;
		Sprite::GetInstance().Draw(SPRITE_ID::END_SPRITE, Vector2(WINDOW_WIDTH / 2, cursorPoses[1].first.y),origin, cursor_ == 1 ? std::abs(temp) : 1.0f,Vector2::One);
	}
	Camera::GetInstance().Position.Set(Vector3(0, 10, 300));

	Camera::GetInstance().Target.Set(Vector3::Zero);
	Camera::GetInstance().SetRange(0.1f, 1000.0f);
	Camera::GetInstance().SetViewAngle(60.0f);
	Camera::GetInstance().Up.Set(Vector3::Up);
	
	Camera::GetInstance().Update();

}

void TitleScene::end()
{

}

