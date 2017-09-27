#include "EffectActor.h"
#include"../../Effect/Effect.h"

EffectActor::EffectActor(IWorld * world, const std::string & name, const Vector3 & position, std::shared_ptr<Effect> effect) :
	Actor(world, name, position),effect_(effect)
{

}

void EffectActor::onUpdate(float deltaTime)
{
	effect_->Update(deltaTime);

	if (effect_->isEnd())dead_ = true;
}

void EffectActor::onDraw() const
{
	effect_->Draw(position_);
}
