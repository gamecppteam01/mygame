#include "NamingScene.h"
#include"../Graphic/Sprite.h"
#include"../Math/Vector2.h"
#include"../UI/CutInText.h"
#include"../Input/InputChecker.h"

NamingScene::NamingScene()
{
}

void NamingScene::start()
{
	next_ = SceneType::SCENE_STAGESELECT;
}

void NamingScene::update(float deltaTime)
{
	if (key_.isEnd()) {
		if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
			isEnd_ = true;
			next_ = SceneType::SCENE_STAGESELECT;
		}
		if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::B)) {
			key_.stateReset();
		}

		return;
	}


	key_.update(deltaTime);
}

void NamingScene::draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::SELECT_BACK, Vector2::Zero);

	key_.draw(Vector2{ 500.0f,300.0f });

	CutInText::DrawMin(Vector2{ 100.0f,50.0f });

	FontManager::GetInstance().DrawTextApplyFont(100.0f, 50.0f, GetColor(255, 255, 255), FONT_ID::BIG_FONT, key_.getNameStr());
}

void NamingScene::end()
{
}
