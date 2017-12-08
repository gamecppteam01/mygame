#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	next_ = SceneType::SCENE_STAGESELECT;
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::start()
{
	isEnd_ = true;
}

void TutorialScene::update(float deltaTime)
{
}

void TutorialScene::draw() const
{
}

void TutorialScene::end()
{
}
