#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
	next_ = SceneType::SCENE_TITLE;
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::start()
{
	isEnd_ = true;
}

void GameOverScene::update(float detlaTime)
{
}

void GameOverScene::draw() const
{
}

void GameOverScene::end()
{
}
