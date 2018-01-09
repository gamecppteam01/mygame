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
}

void SpecifiedDraw::update(float deltaTime)
{
	if (IsStart_ == true) {
		alpha_ -= 0.1f;
		if(alpha_ <= 0.0f){
			IsDead_ = true;
		}

		
	}
}

void SpecifiedDraw::draw() const
{
	Sprite::GetInstance().Draw(id_, position_ ,alpha_);
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

