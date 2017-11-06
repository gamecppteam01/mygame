#include "GameClearScene.h"
#include "../Graphic/Sprite.h"
#include "../ScoreManager/ScoreDisplay.h"
#include "../Input/InputChecker.h"
#include "../DataManager/DataManager.h"

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
}

void GameClearScene::update(float deltaTime)
{
	world_.update(deltaTime);

	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
		isEnd_ = true;
	}
	sinCount_ = (sinCount_ + 3) % 360;
}

void GameClearScene::draw() const
{
	world_.draw();

	Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::RESULT) / 2;
	Sprite::GetInstance().Draw(SPRITE_ID::RESULT, Vector2(WINDOW_WIDTH/2,200.f),origin, 1.0f,Vector2::One);
	int i = 0;
	//リストから値を取り出して順番に表示する
	ScoreDisplay::Score(DataManager::GetInstance().getData(),Vector2(WINDOW_WIDTH/2-150,WINDOW_HEIGHT/2-100));

	origin = Sprite::GetInstance().GetSize(SPRITE_ID::TOTITLE_SPRITE) / 2;
	Sprite::GetInstance().Draw(SPRITE_ID::TOTITLE_SPRITE, Vector2(WINDOW_WIDTH / 2, 600.0f), origin, std::abs(MathHelper::Sin((float)sinCount_)), Vector2::One);

}

void GameClearScene::end()
{
	world_.end();
}
