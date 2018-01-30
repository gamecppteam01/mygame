#include "StepComboUI.h"

StepComboUI::StepComboUI(const SPRITE_ID& id, const Vector2& position)
	: UI{ "StepComboUI",position_ }, id_(id)
{
	initialize();
}

void StepComboUI::initialize()
{
	alpha_ = 0.0f;
	timer_ = 0.0f;
	pos = 0.0f;
}

void StepComboUI::update(float deltaTime)
{
	//èoÇƒÇ≠ÇÈÇ∆Ç´
	if (IsStart_ == true) {
		alpha_ += 0.3f;
		position_ += Vector2(0.0f, pos);
		
		pos = MathHelper::Lerp(0.0f, -100.0f, timer_);
		pos = MathHelper::Clamp(pos, 0.0f, -100.0f);

		if (timer_ <= 60.0f) {
			timer_ += deltaTime;
		}
		else{
			IsStart_ = false;
		}

	}
	//è¡Ç¶ÇÈÇ∆Ç´
	if (IsEnd_ == true) {
		alpha_ -= 0.3f;
		position_ += Vector2(0.0f, pos);

		pos = MathHelper::Lerp(0.0f, 100.0f, timer_);
		pos = MathHelper::Clamp(pos, 0.0f, 100.0f);

		if(timer_ <= 1.0f){
			timer_ += 0.01f;
		}
		else{
			IsEnd_ = false;
		}
	}
	
	
}

void StepComboUI::draw() const
{
	Sprite::GetInstance().Draw(id_, position_ , alpha_);
}

void StepComboUI::IsStart()
{
	IsStart_ = true;
}

void StepComboUI::IsEnd()
{
	IsEnd_ = true;
}

bool StepComboUI::getIsDead() const
{
	return IsDead_;
}

bool StepComboUI::getIsStart() const
{
	return IsStart_;
}

SPRITE_ID StepComboUI::GetId() const
{
	return SPRITE_ID(id_);
}

int StepComboUI::getPos() {
	return pos;
}