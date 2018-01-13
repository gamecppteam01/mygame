#include "GameClearScene.h"
#include "../Graphic/Sprite.h"
#include "../ScoreManager/ScoreDisplay.h"
#include "../Input/InputChecker.h"
#include "../DataManager/DataManager.h"
#include "../Sound/Sound.h"
#include"../Camera/Camera.h"
#include"../Graphic/Model.h"


GameClearScene::GameClearScene():sinCount_(0), field_()
{
	next_ = SceneType::SCENE_TITLE;
}

GameClearScene::~GameClearScene()
{
}

void GameClearScene::start()
{
	sinCount_ = 0;
	cursor_ = 0;
	rrMgr_ =ResultRankManager();
	rrMgr_.init();
	score_.init();

	state_ = State::Start;
}

void GameClearScene::update(float deltaTime)
{
	field_.update(deltaTime);
	rrMgr_.update(deltaTime);
	score_.update(deltaTime);
	if (state_ == GameClearScene::Start) {
		Sound::GetInstance().StopBGM();
		Sound::GetInstance().PlayBGM(BGM_ID::CLEAR_BGM, DX_PLAYTYPE_LOOP);
		state_ = Normal;
		return;
	}
	if (rrMgr_.isEnd()) {
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::A) ||
			InputChecker::GetInstance().GetPovTriggerDownAngle() == 90) {
			cursor_ = (cursor_ - 1 + cursorPoses.size()) % cursorPoses.size();
			Sound::GetInstance().PlaySE(SE_ID::CURSOL_SE, 1, 1);
		}
		else if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::D) ||
			InputChecker::GetInstance().InputChecker::GetInstance().GetPovTriggerDownAngle() == 270)
		{
			cursor_ = (cursor_ + 1) % cursorPoses.size();
			Sound::GetInstance().PlaySE(SE_ID::CURSOL_SE, 1, 1);
		}

		if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
			isEnd_ = true;
			int next = DataManager::GetInstance().getStage() + 1;
			if (next > 3)next = 1;
			DataManager::GetInstance().setStage(next);
			Sound::GetInstance().PlaySE(SE_ID::SELECT_SE, 1, 1);
			next_ = cursorPoses[cursor_].second;
		}
	}
	sinCount_ = (sinCount_ + 3) % 360;
}

void GameClearScene::draw() const
{

	field_.draw();

	rrMgr_.draw();
	
	Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::CLEAR_SPRITE) / 2;
	Sprite::GetInstance().Draw(SPRITE_ID::CLEAR_SPRITE, Vector2{ 150.0f,64.0f }, origin, 1.0f, Vector2::One*0.5f);

	if (rrMgr_.isEnd()) {
		int col = 180;
		Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::CURSOR) / 2;

		float scl = 0.5f;
		Vector2 borigin = Sprite::GetInstance().GetSize(SPRITE_ID::NEXTSTAGE_SPRITE) / 2;
		Sprite::GetInstance().Draw(SPRITE_ID::CURSOR, Vector2{ cursorPoses[cursor_].first.x- borigin.x*scl,cursorPoses[cursor_].first.y }, origin, std::abs(MathHelper::Sin(sinCount_)), Vector2::One, true, true);
		Sprite::GetInstance().Draw(SPRITE_ID::CURSOR, Vector2{ cursorPoses[cursor_].first.x+ borigin.x*scl,cursorPoses[cursor_].first.y }, origin, std::abs(MathHelper::Sin(sinCount_)), Vector2::One, true, false);
		
		if (cursor_ != 0)SetDrawBright(100, 100, 100);
		Sprite::GetInstance().Draw(SPRITE_ID::NEXTSTAGE_SPRITE, Vector2{ cursorPoses[0].first.x,cursorPoses[0].first.y }, borigin, 1.0f, Vector2::One*scl);
		SetDrawBright(255, 255, 255);
		
		borigin = Sprite::GetInstance().GetSize(SPRITE_ID::TOTITLE_SPRITE) / 2;
		if (cursor_ != 1)SetDrawBright(100, 100, 100);
		Sprite::GetInstance().Draw(SPRITE_ID::TOTITLE_SPRITE, Vector2{ cursorPoses[1].first.x,cursorPoses[1].first.y }, borigin, 1.0f, Vector2::One*scl);
		SetDrawBright(255, 255, 255);
	}

	//score_.draw();



	//Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::RESULT) / 2;
	//Sprite::GetInstance().Draw(SPRITE_ID::RESULT, Vector2(WINDOW_WIDTH/2,200.f),origin, 1.0f,Vector2::One);
	//int i = 0;
	//リストから値を取り出して順番に表示する
	//ScoreDisplay::Score(DataManager::GetInstance().getData(),Vector2(WINDOW_WIDTH/2-150,WINDOW_HEIGHT/2-120),5);

	//origin = Sprite::GetInstance().GetSize(SPRITE_ID::TOTITLE_SPRITE) / 2;
	//Sprite::GetInstance().Draw(SPRITE_ID::TOTITLE_SPRITE, Vector2(WINDOW_WIDTH / 2, 600.0f), origin, std::abs(MathHelper::Sin((float)sinCount_)), Vector2::One);

}

void GameClearScene::end()
{
	rrMgr_.end();
}
