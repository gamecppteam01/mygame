#include "HitEffect.h"
#include"../Math/Easing.h"

//holdに行くまでの時間
static float toHoldTime = 0.07f;

HitEffect::HitEffect(float maxSize,int effectCount, float effectTime) :
	Effect(MODEL_ID::EFFECT_LIGHT_MODEL, 0.0f, 0.0f), effectCount_(effectCount), maxSize_(maxSize),timeCount_(0.0f), effectMaxTime_(effectTime){

}

void HitEffect::Update(float deltaTime)
{
	//死んでいたら更新を行わない
	if (isEnd_)return;


}

void HitEffect::Draw(const Vector3 & position) const
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	Effect::Draw(position);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
