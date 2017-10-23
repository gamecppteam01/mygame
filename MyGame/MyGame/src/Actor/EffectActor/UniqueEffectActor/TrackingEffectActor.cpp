#include "TrackingEffectActor.h"

TrackingEffectActor::TrackingEffectActor(IWorld * world, const std::string & name, const Vector3 & position, std::shared_ptr<Effect> effect, const ActorPtr& target):
	EffectActor(world,name,position,effect),target_(target)
{
	Tracking();
}

void TrackingEffectActor::onUpdate(float deltaTime)
{
	EffectActor::onUpdate(deltaTime);
	Tracking();
}

void TrackingEffectActor::Tracking()
{
	//position_ = target_->position();
	position_.x = target_->position().x;
	position_.z = target_->position().z;
}
