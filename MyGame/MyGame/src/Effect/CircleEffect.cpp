#include "CircleEffect.h"
#include"../Math/Easing.h"

//holdに行くまでの時間
static float toHoldTime = 0.07f;

CircleEffect::CircleEffect(float maxSize, float effectTime):
	Effect(MODEL_ID::EFFECT_CIRCLE_MODEL,0.0f,0.0f), maxSize_(maxSize), effectTime_(0.0f),effectMaxTime_(effectTime), holdTime_(0.3f), effectMode_(0){

}

void CircleEffect::Update(float deltaTime)
{
	//死んでいたら更新を行わない
	if (isEnd_)return;

	switch (effectMode_)
	{
	case 0: {
		EffectUpdate(deltaTime);
		break;
	}
	case 1: {
		ToHoldUpdate(deltaTime);
		break;
	}
	case 2: {
		HoldUpdate(deltaTime);
		break;
	}
	default:
		break;
	}

}

void CircleEffect::Draw(const Vector3 & position) const
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	Effect::Draw(position);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void CircleEffect::EffectUpdate(float deltaTime)
{
	if (effectTime_ >= effectMaxTime_) {
		//時間が来たらToHoldModeに移行
		effectTime_ = 0.0f;
		effectMode_++;
		return;
	}

	effectTime_ += deltaTime;
	//size_ = max(effectTime_, 0.0f) - effectMaxTime_;
	//size_ = size_ / effectMaxTime_;
	//size_ *= maxSize_;
	size_ = Easing::EaseOutSine(effectTime_, maxSize_, -maxSize_, effectMaxTime_);

}

void CircleEffect::ToHoldUpdate(float deltaTime)
{
	effectTime_ += deltaTime;
	if (effectTime_ >= toHoldTime) {
		//時間が来たらHoldModeに移行
		effectMode_++;
		return;
	}

	size_ = Easing::Linear(effectTime_, 0.0f, maxSize_, toHoldTime);

}

void CircleEffect::HoldUpdate(float deltaTime)
{
	holdTime_ -= deltaTime;

	if (holdTime_ <= 0.0f) {
		//holdTimeが
		isEnd_ = true;
		return;
	}
	size_ = maxSize_;
}
