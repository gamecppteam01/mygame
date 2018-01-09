#include "SpecifiedDraw.h"

SpecifiedDraw::SpecifiedDraw(const SPRITE_ID & id, const Vector2 & position)
	:UI{ "SpecifiedDraw", position_ }, id_(id), position_(position)
{
}

void SpecifiedDraw::initialize()
{
	
}

void SpecifiedDraw::update(float deltaTime)
{
}

void SpecifiedDraw::draw() const
{
	Sprite::GetInstance().Draw(id_, position_);
}
