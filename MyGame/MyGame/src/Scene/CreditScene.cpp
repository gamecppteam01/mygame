#include "CreditScene.h"

CreditScene::CreditScene()
{
	next_ = SceneType::SCENE_TITLE;
}

CreditScene::~CreditScene()
{
}

void CreditScene::start()
{
	isEnd_ = true;
}

void CreditScene::update(float deltaTime)
{
}

void CreditScene::draw() const
{
}

void CreditScene::end()
{
}
