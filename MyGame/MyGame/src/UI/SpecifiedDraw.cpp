#include "SpecifiedDraw.h"

SpecifiedDraw::SpecifiedDraw(const SPRITE_ID & id, const Vector2 & position)
	:UI{ "SpecifiedDraw", position_ }, id_(id), position_(position)
{
	initialize();
}

void SpecifiedDraw::initialize()
{
	timer_ = 0.0f;
	alpha_ = 1.0f;
	pos = 0.0f;
}

void SpecifiedDraw::update(float deltaTime)
{
	if (IsStart_ == true) {
		alpha_ -= 0.1f;
		position_ += Vector2(0.0f, pos);
		if(alpha_ <= 0.0f){
			IsDead_ = true;
//			position_ += Vector2(140.0f, 0.0f);
		}

		pos = MathHelper::Lerp(0.0f, 100.0f, timer_);

		if (timer_ <= 1.0f) {
			timer_ += 0.2f;
		}
		
	}
}

void SpecifiedDraw::draw() const
{
	Sprite::GetInstance().Draw(id_, position_, alpha_);
}

void SpecifiedDraw::IsStart()
{
	IsStart_ = true;
}

SPRITE_ID SpecifiedDraw::getid() const
{
	return SPRITE_ID(id_);
}

bool SpecifiedDraw::getIsDead() const
{
	return IsDead_;
}

bool SpecifiedDraw::getIsStart() const
{
	return IsStart_;
}

void SpecifiedDraw::addPosition(const Vector2 & pos)
{
	position_ += pos;
}
