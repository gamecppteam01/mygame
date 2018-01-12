#include "TitleScene.h"
#include "../Input/InputChecker.h"
#include "../Graphic/TextDraw.h"
#include "../Graphic/Sprite.h"
#include"../Camera/Camera.h"
#include"../Input/DualShock4Manager.h"
#include"../Graphic/Model.h"
#include "../Math/Easing.h"
#include "../Sound/Sound.h"
#include "../DataManager/DataManager.h"

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
	Sound::GetInstance().StopBGM();
	isEnd_ = false;
	titleState_ = TitleState::first;
	logoPos_ = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 10);
	cursor_ = 0;
	timer_ = 0;
	alpha_ = 0.0f;
	brightCount_ = 0;
	SinCount_ = 0;
	Sound::GetInstance().PlayBGM(BGM_ID::TITLE_BGM, DX_PLAYTYPE_LOOP);
}


void TitleScene::update(float deltaTime)
{
	float t = 0.0f;

	switch (titleState_)
	{
	case TitleState::first:
		firstUpdate();
		break;
	case TitleState::second:
		secondUpdate(deltaTime);
		break;
	case TitleState::third:
		thirdUpdate(deltaTime);
		break;
	}
	
	temp = MathHelper::Sin(SinCount_);
	//min(temp, 0.0f);
	SinCount_ = (SinCount_ + 8) % 360;
	brightCount_ = (brightCount_ + 2) % 360;
}

void TitleScene::draw() const
{
	//タイトル
	Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::TITLE_SCREEN)/2;
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_SCREEN, Vector2(WINDOW_WIDTH/2,WINDOW_HEIGHT/2), origin, 1.0f,Vector2::One*1.3f);
	//タイトルロゴ
	origin = Sprite::GetInstance().GetSize(SPRITE_ID::TITLE_LOGO)/2;
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_LOGO,logoPos_, origin, 1.0f, Vector2::One);

	switch (titleState_)
	{
	case TitleState::first:
		firstDraw();
		break;
	case TitleState::second:
		secondDraw();
		break;
	case TitleState::third:
		thirdDraw();
		break;
	}

	Camera::GetInstance().Position.Set(Vector3(0, 10, 300));

	Camera::GetInstance().Target.Set(Vector3::Zero);
	Camera::GetInstance().SetRange(0.1f, 1000.0f);
	Camera::GetInstance().SetViewAngle(60.0f);
	Camera::GetInstance().Up.Set(Vector3::Up);
	
	Camera::GetInstance().Update();

}

void TitleScene::end(){
}

void TitleScene::firstUpdate(){
	if (is_Triger_Chack()) {
		Sound::GetInstance().PlaySE(SE_ID::SELECT_SE, 1, 1);
		titleState_ = TitleState::second;
	}
}

void TitleScene::secondUpdate(float deltaTime){
	float t = timer_ / maxTimer;
	logoPos_ = Vector2::Lerp(logoPos_, logoPos2_, t);
	alpha_ = MathHelper::Lerp(0.0f, 1.0f, t);
	timer_ = min(timer_ + deltaTime, maxTimer);

	if (DataManager::GetInstance().getIsTutorial() == true /* && timer_ >= maxTimer*/) {
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::W) || InputChecker::GetInstance().GetPovTriggerDownAngle() == 0) {
			cursor_ = (cursor_ - 1 + cursorPoses2.size()) % cursorPoses2.size();
			Sound::GetInstance().PlaySE(SE_ID::CURSOL_SE, 1, 1);
		}
		else if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::S) || InputChecker::GetInstance().InputChecker::GetInstance().GetPovTriggerDownAngle() == 180) {
			cursor_ = (cursor_ + 1) % cursorPoses2.size();
			Sound::GetInstance().PlaySE(SE_ID::CURSOL_SE, 1, 1);
		}

		if (is_Triger_Chack()) {
			if (cursorPoses2[cursor_].second == true) {
				//シーン遷移
				isEnd_ = true;
				auto next = SceneType::SCENE_TUTORIAL;
				Sound::GetInstance().PlaySE(SE_ID::SELECT_SE, 1, 1);
				if (next == SceneType::SCENE_EXIT)exit(0);
				else next_ = next;
			}
			else {
				titleState_ = TitleState::third;
				Sound::GetInstance().PlaySE(SE_ID::SELECT_SE, 1, 1);
			}
			DataManager::GetInstance().setIsTutorial(false);
		}
	}
	else {
		titleState_ = TitleState::third;
		alpha_ = 0.0f;
		timer_ = 0.0f;
		cursor_ = 1;
	}

}

void TitleScene::thirdUpdate(float deltaTime){
	float t = timer_ / (maxTimer*0.5f) ;
	if (DataManager::GetInstance().getIsTutorial() == false) {
		logoPos_ = Vector2::Lerp(logoPos_, logoPos2_, t);
	}
	alpha_ = MathHelper::Lerp(0.0f, 1.0f, t);
	timer_ = min(timer_ + deltaTime, maxTimer);

	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::W) || InputChecker::GetInstance().GetPovTriggerDownAngle() == 0) {
		cursor_ = (cursor_ - 1 + cursorPoses.size()) % cursorPoses.size();
		Sound::GetInstance().PlaySE(SE_ID::CURSOL_SE, 1, 1);
	}
	else if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::S) || InputChecker::GetInstance().InputChecker::GetInstance().GetPovTriggerDownAngle() == 180)	{
		cursor_ = (cursor_ + 1) % cursorPoses.size();
		Sound::GetInstance().PlaySE(SE_ID::CURSOL_SE, 1, 1);
	}

	if (is_Triger_Chack()) {
		//シーン遷移
		isEnd_ = true;
		auto next = cursorPoses[cursor_].second;
		Sound::GetInstance().PlaySE(SE_ID::SELECT_SE, 1, 1);
		if (next == SceneType::SCENE_EXIT)exit(0);
		else next_ = next;
	}
}

void TitleScene::firstDraw() const{
	Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::START_SPRITE) / 2;

	int bright = (int)(std::abs(MathHelper::Sin(brightCount_))*155.f) + 100;
	SetDrawBright(bright, bright, bright);
	Sprite::GetInstance().Draw(SPRITE_ID::START_SPRITE, Vector2(WINDOW_WIDTH / 2, 600.0f), origin, /*std::abs(MathHelper::Sin(SinCount_*0.5f))*/1.0f, Vector2::One);
	SetDrawBright(255, 255, 255);
}

void TitleScene::secondDraw() const{
	//if (timer_ <= maxTimer-0.1f) return;
	if (DataManager::GetInstance().getIsTutorial() == true && timer_ >= maxTimer * 0.5f) {
		Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::CURSOR) / 2;
		Sprite::GetInstance().Draw(SPRITE_ID::CURSOR, Vector2{ WINDOW_WIDTH*0.5f - cursorPoses2[cursor_].first.x*0.7f,cursorPoses2[cursor_].first.y }, origin, std::abs(temp), Vector2::One, true, true);
		Sprite::GetInstance().Draw(SPRITE_ID::CURSOR, Vector2{ WINDOW_WIDTH*0.5f + cursorPoses2[cursor_].first.x*0.7f,cursorPoses2[cursor_].first.y }, origin, std::abs(temp), Vector2::One, true, false);
		origin = Sprite::GetInstance().GetSize(SPRITE_ID::TUTORIAL_SPRITE) / 2;
		//チュートリアルをしますか？
		origin = Sprite::GetInstance().GetSize(SPRITE_ID::TUTORIAL_TEXT) / 2;
		Sprite::GetInstance().Draw(SPRITE_ID::TUTORIAL_TEXT, Vector2(WINDOW_WIDTH / 2, 400.0f), origin, alpha_, Vector2::One);
		SetDrawBright(255, 255, 255);
		//YES
		origin = Sprite::GetInstance().GetSize(SPRITE_ID::YES_TEXT) / 2;
		if (cursor_ != 0)SetDrawBright(100, 100, 100);
		Sprite::GetInstance().Draw(SPRITE_ID::YES_TEXT, Vector2(WINDOW_WIDTH / 2, cursorPoses2[0].first.y), origin, alpha_, Vector2::One);
		SetDrawBright(255, 255, 255);
		//NO
		origin = Sprite::GetInstance().GetSize(SPRITE_ID::NO_TEXT) / 2;
		if (cursor_ != 1)SetDrawBright(100, 100, 100);
		Sprite::GetInstance().Draw(SPRITE_ID::NO_TEXT, Vector2(WINDOW_WIDTH / 2, cursorPoses2[1].first.y), origin, alpha_, Vector2::One);
		SetDrawBright(255, 255, 255);
	}
}

void TitleScene::thirdDraw() const{
	Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::CURSOR) / 2;
	Sprite::GetInstance().Draw(SPRITE_ID::CURSOR, Vector2{ WINDOW_WIDTH*0.5f - cursorPoses[cursor_].first.x,cursorPoses[cursor_].first.y }, origin, std::abs(temp), Vector2::One, true, true);
	Sprite::GetInstance().Draw(SPRITE_ID::CURSOR, Vector2{ WINDOW_WIDTH*0.5f + cursorPoses[cursor_].first.x,cursorPoses[cursor_].first.y }, origin, std::abs(temp), Vector2::One, true, false);
	origin = Sprite::GetInstance().GetSize(SPRITE_ID::TUTORIAL_SPRITE) / 2;
	if (cursor_ != 0)SetDrawBright(100, 100, 100);
	Sprite::GetInstance().Draw(SPRITE_ID::TUTORIAL_SPRITE, Vector2(WINDOW_WIDTH / 2, cursorPoses[0].first.y), origin, alpha_, Vector2::One);
	SetDrawBright(255, 255, 255);
	origin = Sprite::GetInstance().GetSize(SPRITE_ID::START_SPRITE) / 2;
	if (cursor_ != 1)SetDrawBright(100, 100, 100);
	Sprite::GetInstance().Draw(SPRITE_ID::STAGESELECT_SPRITE, Vector2(WINDOW_WIDTH / 2, cursorPoses[1].first.y), origin, alpha_, Vector2::One);
	SetDrawBright(255, 255, 255);
	origin = Sprite::GetInstance().GetSize(SPRITE_ID::END_SPRITE) / 2;
	if (cursor_ != 2)SetDrawBright(100, 100, 100);
	Sprite::GetInstance().Draw(SPRITE_ID::END_SPRITE, Vector2(WINDOW_WIDTH / 2, cursorPoses[2].first.y), origin, alpha_, Vector2::One);
	SetDrawBright(255, 255, 255);
}

bool TitleScene::is_Triger_Chack(){
	return Keyboard::GetInstance().KeyTriggerDown(KEYCODE::F) || InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A);
}

