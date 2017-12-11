#include "StageSelectScene.h"
#include"../Input/InputChecker.h"
#include"../Graphic/Sprite.h"
#include"../Define.h"
#include"../DataManager/DataManager.h"
#include "../Sound/Sound.h"

StageSelectScene::StageSelectScene()
{
	next_ = SceneType::SCENE_GAMEPLAY;

}

StageSelectScene::~StageSelectScene()
{
}

void StageSelectScene::start()
{
	cursor_ = 0;
	prevCursor_ = 0;
}

void StageSelectScene::update(float deltaTime)
{
	if (InputChecker::GetInstance().GetPovTriggerDownAngle() == 270) {
		cursor_ = (cursor_ - 1 + ButtonList.size()) % ButtonList.size();
		Sound::GetInstance().PlaySE(SE_ID::CURSOL_SE, 1, 1);
	}
	else if (InputChecker::GetInstance().GetPovTriggerDownAngle() == 90) {
		cursor_ = (cursor_ + 1) % ButtonList.size();
		Sound::GetInstance().PlaySE(SE_ID::CURSOL_SE, 1, 1);
	}
	else if (InputChecker::GetInstance().GetPovTriggerDownAngle() == 180) {
		if (cursor_ != 3) {
			prevCursor_ = cursor_;
			cursor_ = 3;
		}
		Sound::GetInstance().PlaySE(SE_ID::CURSOL_SE, 1, 1);
	}
	else if (InputChecker::GetInstance().GetPovTriggerDownAngle() == 0) {
		if (cursor_ == 3) {
			cursor_ = (prevCursor_ == 3) ? (cursor_ - 1 + ButtonList.size()) % ButtonList.size() : prevCursor_;
		}
		Sound::GetInstance().PlaySE(SE_ID::CURSOL_SE, 1, 1);
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
		//シーン遷移
		next_ = ButtonList[cursor_].first;
		Sound::GetInstance().PlaySE(SE_ID::SELECT_SE, 1, 1);
		DataManager::GetInstance().setStage(ButtonList[cursor_].second);//ステージ番号受け渡し
		isEnd_ = true;
	}
}

void StageSelectScene::draw() const
{

	float cutSize = WINDOW_WIDTH / 6.0f;//ボタン軸のカット毎サイズ
	Sprite::GetInstance().Draw(SPRITE_ID::SELECT_BACK, Vector2::Zero);

	//ステージ1～3
	Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::STAGE1_TEXT_SPRITE) / 2;

	float yPos = 400.0f;
	if (cursor_ != 0)SetDrawBright(100, 100, 100);
	Sprite::GetInstance().Draw(SPRITE_ID::STAGE1_TEXT_SPRITE, Vector2{ cutSize*1.0f,yPos }, origin, 1.0f, Vector2::One*0.5f);
	SetDrawBright(255, 255, 255);
	origin = Sprite::GetInstance().GetSize(SPRITE_ID::STAGE2_TEXT_SPRITE) / 2;
	if (cursor_ != 1)SetDrawBright(100, 100, 100);
	Sprite::GetInstance().Draw(SPRITE_ID::STAGE2_TEXT_SPRITE, Vector2{ cutSize*3.0f,yPos }, origin, 1.0f, Vector2::One*0.5f);
	SetDrawBright(255, 255, 255);
	origin = Sprite::GetInstance().GetSize(SPRITE_ID::STAGE3_TEXT_SPRITE) / 2;
	if (cursor_ != 2)SetDrawBright(100, 100, 100);
	Sprite::GetInstance().Draw(SPRITE_ID::STAGE3_TEXT_SPRITE, Vector2{ cutSize*5.0f,yPos }, origin, 1.0f, Vector2::One*0.5f);
	SetDrawBright(255, 255, 255);

	//タイトルへの遷移
	origin = Sprite::GetInstance().GetSize(SPRITE_ID::TOTITLE_SPRITE) / 2;
	if (cursor_ != 3)SetDrawBright(100, 100, 100);
	Sprite::GetInstance().Draw(SPRITE_ID::TOTITLE_SPRITE, Vector2{ WINDOW_WIDTH*0.5f,600.0f }, origin, 1.0f, Vector2::One);
	SetDrawBright(255, 255, 255);
}

void StageSelectScene::end()
{
}
