#include "StepComboUI.h"

StepComboUI::StepComboUI(const SPRITE_ID& id, const Vector2& position)
	: UI{ "StepComboUI",position_ }, id_(id), position_(position)
{
	initialize();
}

void StepComboUI::initialize()
{
	alpha_ = 1.0f;
	timer_ = 0.0f;

}

void StepComboUI::update(float deltaTime)
{

	
}

void StepComboUI::draw() const
{
	Sprite::GetInstance().Draw(id_, position_ , alpha_);
}

bool StepComboUI::IsCount()
{
	return true;
}

void StepComboUI::alpha(const float & alpha)
{
	alpha_ = alpha;
}

void StepComboUI::position(const Vector2 & pos)
{
	position_ = pos;
}

SPRITE_ID StepComboUI::GetId() const
{
	return SPRITE_ID(id_);
}
