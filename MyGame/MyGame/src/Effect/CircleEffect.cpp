#include "CircleEffect.h"
#include"../Math/Easing.h"

CircleEffect::CircleEffect(float maxSize, float effectTime):
	Effect(MODEL_ID::EFFECT_CIRCLE_MODEL,0.0f,0.0f), maxSize_(maxSize), effectTime_(0.0f),effectMaxTime_(effectTime){

}

void CircleEffect::Update(float deltaTime)
{
	//Ž€‚ñ‚Å‚¢‚½‚çXV‚ðs‚í‚È‚¢
	if (isEnd_)return;

	effectTime_ += deltaTime;
	//size_ = max(effectTime_, 0.0f) - effectMaxTime_;
	//size_ = size_ / effectMaxTime_;
	//size_ *= maxSize_;
	size_ = Easing::EaseOutCubic(effectTime_, maxSize_, -maxSize_, effectMaxTime_);
	if (effectTime_ >= effectMaxTime_) {
		isEnd_ = true;
	}
}

void CircleEffect::Draw(const Vector3 & position) const
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	Effect::Draw(position);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
