#include "GameClearScene.h"
#include "../Graphic/Sprite.h"
#include "../ScoreManager/ScoreDisplay.h"
#include "../Input/InputChecker.h"
#include "../DataManager/DataManager.h"

GameClearScene::GameClearScene()
{
	next_ = SceneType::SCENE_TITLE;
}

GameClearScene::~GameClearScene()
{
}

void GameClearScene::start()

{
	world_.Initialize();
}

void GameClearScene::update(float deltaTime)
{
	world_.update(deltaTime);

	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::F)) {
		isEnd_ = true;
	}
}

void GameClearScene::draw() const
{
	world_.draw();

	Sprite::GetInstance().Draw(SPRITE_ID::RESULT, Vector2::Zero, 1.0f);
	int i = 0;
	//リストから値を取り出して順番に表示する
	ScoreDisplay(DataManager::GetInstance().getData());
}

void GameClearScene::end()
{
	world_.end();
}
