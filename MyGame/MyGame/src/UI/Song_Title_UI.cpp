#include "Song_Title_UI.h"
#include"../Graphic/FontManager.h"
#include"../Graphic/Sprite.h"
#include "../Sound/Sound.h"

//コンストラクタ
Song_Title_UI::Song_Title_UI(int soundhandle)
	:UI("Song_Title_UI", Vector2::Zero),soundhandle_(soundhandle){
	initialize();
}

//初期化
void Song_Title_UI::initialize()
{
	songMap_.clear();
	createSongList();
}

//更新
void Song_Title_UI::update(float deltaTime){
}

//描画
void Song_Title_UI::draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::NOTE, Vector2::Zero);
	FontManager::GetInstance().DrawTextApplyFont(32, 0,GetColor(255,0,255), FONT_ID::JAPANESE_FONT, songMap_.at(soundhandle_));
}

void Song_Title_UI::createSongList()
{
	songMap_[Sound::GetInstance().GetHandle(BGM_ID::STAGE1_BGM)] = "ハロウィンパレード";
	songMap_[Sound::GetInstance().GetHandle(BGM_ID::STAGE2_BGM)] = "曇空のワルツ";
	songMap_[Sound::GetInstance().GetHandle(BGM_ID::STAGE3_BGM)] = "フォークタンゴ";
}
