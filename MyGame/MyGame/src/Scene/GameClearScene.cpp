#include "GameClearScene.h"

GameClearScene::GameClearScene()
{
	next_ = SceneType::SCENE_CREDIT;
}

GameClearScene::~GameClearScene()
{
}

void GameClearScene::start()
{
	isEnd_ = true;
}

void GameClearScene::update(float deltaTime)
{
}

void GameClearScene::draw() const
{
}

void GameClearScene::end()
{
}
