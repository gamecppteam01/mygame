#include "PauseScreen.h"
#include"../../Input/InputChecker.h"
#include"../../Graphic/Sprite.h"
#include"../../Define.h"

PauseScreen::PauseScreen()
{

}

void PauseScreen::initialize()
{
	cursor_ = 0;
	sinCount_ = 0;
}

void PauseScreen::start()
{
	cursor_ = 0;
	sinCount_ = 0;
}

int PauseScreen::update(float deltaTime, SceneType & type, GamePlayState& state)
{
	//Sinカーブの進行
	sinCount_ = (sinCount_ + 5) % 360;

	//キー毎の遷移
	if (InputChecker::GetInstance().GetPovTriggerDownAngle() == 0) {
		cursor_ = (cursor_ - 1 + cursorPoses.size()) % cursorPoses.size();
	}
	else if (InputChecker::GetInstance().GetPovTriggerDownAngle() == 180) {
		cursor_ = (cursor_ + 1) % cursorPoses.size();
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
		//シーン遷移を行わないパターンの場合
		if (std::get<1>(cursorPoses[cursor_]) == SceneType::SCENE_EXIT) {
			state = std::get<2>(cursorPoses[cursor_]);
			return 2;
		}

		type = std::get<1>(cursorPoses[cursor_]);
		return 1;
	}
	return 0;
}

void PauseScreen::draw() const
{
	int col = 180;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(col, col, col), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::CURSOR) / 2;
	//Sprite::GetInstance().Draw(SPRITE_ID::CURSOR, cursorPoses[cursor_].first, origin, 1.0f, Vector2::One);
	Sprite::GetInstance().Draw(SPRITE_ID::CURSOR, Vector2{ WINDOW_WIDTH*0.5f - std::get<0>(cursorPoses[cursor_]).x,std::get<0>(cursorPoses[cursor_]).y }, origin, std::abs(MathHelper::Sin(sinCount_)), Vector2::One, true, true);
	Sprite::GetInstance().Draw(SPRITE_ID::CURSOR, Vector2{ WINDOW_WIDTH*0.5f + std::get<0>(cursorPoses[cursor_]).x,std::get<0>(cursorPoses[cursor_]).y }, origin, std::abs(MathHelper::Sin(sinCount_)), Vector2::One, true, false);

	origin = Sprite::GetInstance().GetSize(SPRITE_ID::PAUSE_SPRITE) / 2;
	Sprite::GetInstance().Draw(SPRITE_ID::PAUSE_SPRITE, Vector2{ WINDOW_WIDTH*0.5f,200.0f }, origin, 1.0f, Vector2::One);

	origin = Sprite::GetInstance().GetSize(SPRITE_ID::BACKGAME_SPRITE) / 2;
	Sprite::GetInstance().Draw(SPRITE_ID::BACKGAME_SPRITE, Vector2{ WINDOW_WIDTH*0.5f,std::get<0>(cursorPoses[0]).y }, origin, 1.0f, Vector2::One);
	origin = Sprite::GetInstance().GetSize(SPRITE_ID::RETRY_SPRITE) / 2;
	Sprite::GetInstance().Draw(SPRITE_ID::RETRY_SPRITE, Vector2{ WINDOW_WIDTH*0.5f,std::get<0>(cursorPoses[1]).y }, origin, 1.0f, Vector2::One);
	origin = Sprite::GetInstance().GetSize(SPRITE_ID::TOTITLE_SPRITE) / 2;
	Sprite::GetInstance().Draw(SPRITE_ID::TOTITLE_SPRITE, Vector2{ WINDOW_WIDTH*0.5f,std::get<0>(cursorPoses[2]).y }, origin, 1.0f, Vector2::One);

}
