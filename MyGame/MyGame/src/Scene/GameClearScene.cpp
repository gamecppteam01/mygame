#include "GameClearScene.h"
#include "../Graphic/Sprite.h"
#include "../ScoreManager/ScoreDisplay.h"
#include "../Input/InputChecker.h"
#include "../DataManager/DataManager.h"

static const float moveTimer_ = 30.0f;

GameClearScene::GameClearScene():sinCount_(0)
{
	next_ = SceneType::SCENE_TITLE;
}

GameClearScene::~GameClearScene()
{
}

void GameClearScene::start()

{
	world_.Initialize();
	sinCount_ = 0;
	timer_ = 0.0f;
}

void GameClearScene::update(float deltaTime)
{
	world_.update(deltaTime);

	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)||
		Keyboard::GetInstance().KeyStateDown(KEYCODE::F)) {
		isEnd_ = true;
	}
	
	timer_ -= deltaTime;
	sinCount_ = (sinCount_ + 3) % 360;
}

void GameClearScene::draw() const
{
	world_.draw();
	//                                 開始位置　移動量　時間 Vector2(-10.0f, WINDOW_HEIGHT / 2 - 500.0f)
	Vector2 scorePos_ = scorePos_.Lerp(Vector2(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 100),Vector2(WINDOW_WIDTH/ 2 - 150,0.0f), timer_ / 60);
	Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::RESULT) / 2;
	Sprite::GetInstance().Draw(SPRITE_ID::RESULT, Vector2(WINDOW_WIDTH/2,200.f),origin, 1.0f,Vector2::One);

	//リストから値を取り出して順番に表示する
	ScoreDisplay::Score(DataManager::GetInstance().getData(), scorePos_, 5);

	origin = Sprite::GetInstance().GetSize(SPRITE_ID::TOTITLE_SPRITE) / 2;
	Sprite::GetInstance().Draw(SPRITE_ID::TOTITLE_SPRITE, Vector2(WINDOW_WIDTH / 2, 600.0f), origin, std::abs(MathHelper::Sin((float)sinCount_)), Vector2::One);

}

void GameClearScene::end()
{
	world_.end();
}
