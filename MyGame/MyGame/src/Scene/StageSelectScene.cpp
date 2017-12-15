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
	sinCount_ = 0;
	t = 0.0f;
	Ypos = 0.0f;
}

void StageSelectScene::update(float deltaTime)
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::W) ||
		InputChecker::GetInstance().GetPovTriggerDownAngle() == 0) {
		cursor_ = (cursor_ - 1 + ButtonList.size()) % ButtonList.size();
		Ypos -= 150.0f;
		Sound::GetInstance().PlaySE(SE_ID::CURSOL_SE, 1, 1);
	}
	else if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::S) ||
		InputChecker::GetInstance().InputChecker::GetInstance().GetPovTriggerDownAngle() == 180){
		cursor_ = (cursor_ + 1) % ButtonList.size();
		Ypos += 150.0f;
		Sound::GetInstance().PlaySE(SE_ID::CURSOL_SE, 1, 1);
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
		//シーン遷移
		next_ = ButtonList[cursor_].first;
		Sound::GetInstance().PlaySE(SE_ID::SELECT_SE, 1, 1);
		DataManager::GetInstance().setStage(ButtonList[cursor_].second);//ステージ番号受け渡し
		isEnd_ = true;
	}
	//カーソルループ
	if (Ypos == 600.0f && InputChecker::GetInstance().InputChecker::GetInstance().GetPovTriggerDownAngle() == 180) Ypos = 0.0f;
	if (Ypos == -150.0f && InputChecker::GetInstance().InputChecker::GetInstance().GetPovTriggerDownAngle() == 0) Ypos = 450.0f;
	MathHelper::Clamp(Ypos, -150.0f, 600.0f);
	t = MathHelper::Sin(sinCount_);
	sinCount_ = (sinCount_ + 8) % 360;
}

void StageSelectScene::draw() const
{
	
	float cutSize = WINDOW_WIDTH / 6.0f;//ボタン軸のカット毎サイズ
	Sprite::GetInstance().Draw(SPRITE_ID::SELECT_BACK, Vector2::Zero);
	
	Vector2 basePos{ cutSize*4.0f,150.0f };//1番目の位置
	float padding = 150.0f;//要素ごとの隙間
	
	//カーソル
	Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::CURSOR) / 2;
	if (Ypos != 450)Sprite::GetInstance().Draw(SPRITE_ID::CURSOR, Vector2(basePos - (WINDOW_WIDTH / 2 * 0.5f)  + Vector2(0.0f, Ypos)) , origin, t, Vector2::One,true,true);
	Sprite::GetInstance().Draw(SPRITE_ID::CURSOR, Vector2(basePos - (WINDOW_WIDTH / 2 * -0.5f) + Vector2(0.0f, Ypos)), origin, t, Vector2::One,true,false);
	if(Ypos == 450)Sprite::GetInstance().Draw(SPRITE_ID::CURSOR, Vector2(basePos - (WINDOW_WIDTH / 2 - 440.0f) + Vector2(0.0f, Ypos)), origin, t, Vector2::One, true, true);
	//ステージ1～3
	origin = Sprite::GetInstance().GetSize(SPRITE_ID::STAGE1_TEXT_SPRITE) / 2;

	if (cursor_ != 0)SetDrawBright(100, 100, 100);
	Sprite::GetInstance().Draw(SPRITE_ID::STAGE1_TEXT_SPRITE, basePos, origin, 1.0f, Vector2::One*0.7f);
	SetDrawBright(255, 255, 255);
	origin = Sprite::GetInstance().GetSize(SPRITE_ID::STAGE2_TEXT_SPRITE) / 2;
	if (cursor_ != 1)SetDrawBright(100, 100, 100);
	Sprite::GetInstance().Draw(SPRITE_ID::STAGE2_TEXT_SPRITE, Vector2{ basePos.x,basePos.y+padding }, origin, 1.0f, Vector2::One*0.7f);
	SetDrawBright(255, 255, 255);
	origin = Sprite::GetInstance().GetSize(SPRITE_ID::STAGE3_TEXT_SPRITE) / 2;
	if (cursor_ != 2)SetDrawBright(100, 100, 100);
	Sprite::GetInstance().Draw(SPRITE_ID::STAGE3_TEXT_SPRITE, Vector2{ basePos.x,basePos.y + padding*2 }, origin, 1.0f, Vector2::One*0.7f);
	SetDrawBright(255, 255, 255);

	//タイトルへの遷移
	origin = Sprite::GetInstance().GetSize(SPRITE_ID::TOTITLE_SPRITE) / 2;
	if (cursor_ != 3)SetDrawBright(100, 100, 100);
	Sprite::GetInstance().Draw(SPRITE_ID::TOTITLE_SPRITE, Vector2{ basePos.x+60.0f,basePos.y + padding * 3 }, origin, 1.0f, Vector2::One*0.55f);
	SetDrawBright(255, 255, 255);

//	//タイトルへの遷移
//	origin = Sprite::GetInstance().GetSize(SPRITE_ID::TOTITLE_SPRITE) / 2;
//	if (cursor_ != 3)SetDrawBright(100, 100, 100);
//	Sprite::GetInstance().Draw(SPRITE_ID::TOTITLE_SPRITE, Vector2{ WINDOW_WIDTH*0.5f,600.0f }, origin, 1.0f, Vector2::One);
//	SetDrawBright(255, 255, 255);
}

void StageSelectScene::end()
{
}
