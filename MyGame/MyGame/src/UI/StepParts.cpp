#include "StepParts.h"
#include"../Graphic/Sprite.h"
#include"../Math/Easing.h"

StepParts::StepParts(DrawStepType type, const Vector2& position) :type_{ type }, position_{ position }, firstPos_{ position }, targetPos_{ position }
{
	switch (type)
	{
	case StepParts::DrawStepType::Quarter:
		id_ = SPRITE_ID::QUATER_SPRITE;
		break;
	case StepParts::DrawStepType::Half:
		id_ = SPRITE_ID::HALF_SPRITE;
		break;
	case StepParts::DrawStepType::Turn:
		id_ = SPRITE_ID::TURN_SPRITE;
		break;
	case StepParts::DrawStepType::Spin:
		id_ = SPRITE_ID::SPIN_SPRITE;
		break;
	default:
		break;
	}
}

void StepParts::update(float deltaTime)
{
	switch (state_)
	{
	case StepParts::State::Start:
		start(deltaTime);
		break;
	case StepParts::State::Normal:
		normal(deltaTime);
		break;
	case StepParts::State::Slide:
		slide(deltaTime);
		break;
	default:
		break;
	}
	if(startDead_)dead(deltaTime);

}

void StepParts::draw() const
{
	Sprite::GetInstance().Draw(id_, position_, alpha_);
}

void StepParts::dead()
{
	startDead_ = true;
}

bool StepParts::isDead() const
{
	return isDead_;
}

bool StepParts::isStartDead() const
{
	return startDead_;
}

void StepParts::start(float deltaTime)
{
	alpha_ += deltaTime*5.0f;
	if (alpha_ >= 1.0f)changeState(State::Normal);
}

void StepParts::normal(float deltaTime)
{
}

void StepParts::dead(float deltaTime)
{
	alpha_ -= deltaTime;
	if (alpha_ <= 0.0f)isDead_ = true;

}

void StepParts::slide(float deltaTime)
{
	countTimer_ += deltaTime;

	if (countTimer_ >= 1.0f) {
		countTimer_ = 1.0f;
		changeState(State::Normal);
	}

	position_.x = Easing::EaseOutQuart(countTimer_, firstPos_.x, targetPos_.x- firstPos_.x, 1.0f);
	position_.y = Easing::EaseOutQuart(countTimer_, firstPos_.y, targetPos_.y- firstPos_.y, 1.0f);
}

void StepParts::startSlide(const Vector2 & slidePos)
{
	firstPos_ = position_;
	targetPos_ = slidePos;
	changeState(State::Slide);
	countTimer_ = 0.0f;
}

void StepParts::setID(DrawStepType type)
{
	type_ = type;
	switch (type)
	{
	case StepParts::DrawStepType::Quarter:
		id_ = SPRITE_ID::QUATER_SPRITE;
		break;
	case StepParts::DrawStepType::Half:
		id_ = SPRITE_ID::HALF_SPRITE;
		break;
	case StepParts::DrawStepType::Turn:
		id_ = SPRITE_ID::TURN_SPRITE;
		break;
	case StepParts::DrawStepType::Spin:
		id_ = SPRITE_ID::SPIN_SPRITE;
		break;
	default:
		break;
	}

}

void StepParts::changeState(State state)
{
	switch (state_)
	{
	case StepParts::State::Start:
		alpha_ = 1.0f;
		break;
	case StepParts::State::Normal:
		break;
	case StepParts::State::Slide:
		break;
	default:
		break;
	}
	state_ = state;
	switch (state_)
	{
	case StepParts::State::Start:
		break;
	case StepParts::State::Normal:
		break;
	case StepParts::State::Slide:
		break;
	default:
		break;
	}
}

SPRITE_ID StepParts::getDrawType() const
{
	return id_;
}

Vector2 StepParts::getPos() const
{
	return position_;
}

float StepParts::getAlpha() const
{
	return alpha_;
}
