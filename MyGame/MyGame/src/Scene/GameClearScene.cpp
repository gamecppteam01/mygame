#include "GameClearScene.h"
#include "../Graphic/Sprite.h"
#include "../ScoreManager/ScoreDisplay.h"
#include "../Input/InputChecker.h"
#include "../DataManager/DataManager.h"
#include "../Sound/Sound.h"
#include"../Camera/Camera.h"
#include"../Graphic/Model.h"

GameClearScene::GameClearScene():sinCount_(0)
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

	score_.init();

	state_ = State::Start;
}

void GameClearScene::update(float deltaTime)
{
	score_.update(deltaTime);
	if (state_ == GameClearScene::Start) {
		Sound::GetInstance().StopBGM();
		Sound::GetInstance().PlayBGM(BGM_ID::CLEAR_BGM, DX_PLAYTYPE_LOOP);
		state_ = Normal;
		return;
	}
	if (score_.end()) {
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::W) ||
			InputChecker::GetInstance().GetPovTriggerDownAngle() == 0) {
			cursor_ = (cursor_ - 1 + cursorPoses.size()) % cursorPoses.size();
			Sound::GetInstance().PlaySE(SE_ID::CURSOL_SE, 1, 1);
		}
		else if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::S) ||
			InputChecker::GetInstance().InputChecker::GetInstance().GetPovTriggerDownAngle() == 180)
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
	Camera::GetInstance().Position.Set(Vector3(0.0f,50.0f,100.0f));

	Camera::GetInstance().Target.Set(Vector3::Zero);
	Camera::GetInstance().SetRotation(Vector3(0.0f, 0.0f, 0.0f));
	Camera::GetInstance().SetRange(0.1f, 1000.0f);
	Camera::GetInstance().SetViewAngle(60.0f);
	Camera::GetInstance().Up.Set(Vector3::Up);

	Camera::GetInstance().Update();

	Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::CLEAR_SPRITE) / 2;
	Sprite::GetInstance().Draw(SPRITE_ID::CLEAR_SPRITE, Vector2{ 250.0f,64.0f }, origin, 1.0f, Vector2::One*2.0f);

	if (score_.end()) {
		int col = 180;
		Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::CURSOR) / 2;
		Sprite::GetInstance().Draw(SPRITE_ID::CURSOR, Vector2{ WINDOW_WIDTH*0.5f - cursorPoses[cursor_].first.x,cursorPoses[cursor_].first.y }, origin, std::abs(MathHelper::Sin(sinCount_)), Vector2::One, true, true);
		Sprite::GetInstance().Draw(SPRITE_ID::CURSOR, Vector2{ WINDOW_WIDTH*0.5f + cursorPoses[cursor_].first.x,cursorPoses[cursor_].first.y }, origin, std::abs(MathHelper::Sin(sinCount_)), Vector2::One, true, false);
		
		origin = Sprite::GetInstance().GetSize(SPRITE_ID::NEXTSTAGE_SPRITE) / 2;
		if (cursor_ != 0)SetDrawBright(100, 100, 100);
		Sprite::GetInstance().Draw(SPRITE_ID::NEXTSTAGE_SPRITE, Vector2{ WINDOW_WIDTH*0.5f,cursorPoses[0].first.y }, origin, 1.0f, Vector2::One);
		SetDrawBright(255, 255, 255);
		
		origin = Sprite::GetInstance().GetSize(SPRITE_ID::TOTITLE_SPRITE) / 2;
		if (cursor_ != 1)SetDrawBright(100, 100, 100);
		Sprite::GetInstance().Draw(SPRITE_ID::TOTITLE_SPRITE, Vector2{ WINDOW_WIDTH*0.5f,cursorPoses[1].first.y }, origin, 1.0f, Vector2::One);
		SetDrawBright(255, 255, 255);
	}

	score_.draw();



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
}
