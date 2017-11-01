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
	//next_ = SceneType::SCENE_GAMEPLAY;
	next_ = SceneType::SCENE_CLEAR;

	titleState_ = TitleState::first;
	SinCount_ = 0;
	Counter_ = 0;
	Cursol_ = 0.0f;
}

TitleScene::~TitleScene()
{

}

void TitleScene::start()
{
	isEnd_ = false;
	
}


void TitleScene::update(float deltaTime)
{
	float t = 0.0f;
	
	//初期状態
	if (titleState_ == TitleState::first) {
		if (titleState_ == TitleState::first &&
			Keyboard::GetInstance().KeyStateDown(KEYCODE::F) ||
			InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::B)) {
			titleState_ = TitleState::second;
		}

		//単発のエフェクト
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::R)) {
			EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::SAMPLE_EFFECT, Vector3(1, 0, 0), Vector3::One, Vector3::One);
		}
		//連続のエフェクト
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::T)) {
			EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::EFFECT_TEST, Vector3(1, 0, 0), Vector3::Zero, Vector3::One);
		}
		//エフェクトテスト
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Y)) {
			//EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::RING_EFFECT, Vector3(0, 0, 0), Vector3(1, 0, 0), Vector3::One);
																				//Vector3(1, 0, 1), Vector3(1, 0, 0), Vector3::One
			//EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::HIT_EFFECT, Vector3::Zero, Vector3::Zero, Vector3::One);
			EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::ACTION_EFFECT, Vector3::Zero, Vector3::Zero, Vector3::One);
		}																		

	}
	//二段階目
	else if (titleState_ == TitleState::second)
	{
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::W) ||
			InputChecker::GetInstance().GetPovTriggerDownAngle() == 0) {
			Counter_ -= 1;
			Cursol_ -= 100.0f;
		}
		else if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::S) ||
			InputChecker::GetInstance().InputChecker::GetInstance().GetPovTriggerDownAngle() == 180)
		{
			Counter_ += 1;
			Cursol_ += 100.0f;
		}

		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::F) ||
			InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::B)) {
			//シーン遷移
			isEnd_ = true;
		}
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::F) ||
			InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::B)) {
			//ゲーム終了
		}
	}
	temp = MathHelper::Sin(SinCount_);
	//min(temp, 0.0f);
	SinCount_++;
}

void TitleScene::draw() const
{
	//タイトル
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_SCREEN, Vector2(0.0f, 0.0f), 1.0f);
	//はじめる
	if (titleState_ == TitleState::first) {
		Sprite::GetInstance().Draw(SPRITE_ID::START_SPRITE, Vector2(0.0f, 400.0f), temp * 1);

	}
	//ステージ選択か終了
	if (titleState_ == TitleState::second) {
		Sprite::GetInstance().Draw(SPRITE_ID::BUTTON_A, Vector2(0.0f, Cursol_ + 100.0f), 1.0f);
		if (Counter_ == 0) {
			Sprite::GetInstance().Draw(SPRITE_ID::START_SPRITE, Vector2(50.0f, 200.0f), temp * 1);
			Sprite::GetInstance().Draw(SPRITE_ID::START_SPRITE, Vector2(50.0f, 400.0f), 1.0f);
		}
		if (Counter_ == 1){
			Sprite::GetInstance().Draw(SPRITE_ID::START_SPRITE, Vector2(50.0f, 200.0f), 1.0f);
			Sprite::GetInstance().Draw(SPRITE_ID::START_SPRITE, Vector2(50.0f, 400.0f), temp * 1);
		}
	}
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
	DrawCapsule3D(-seg / 2, seg / 2, 2, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);

}

void TitleScene::end()
{

}

