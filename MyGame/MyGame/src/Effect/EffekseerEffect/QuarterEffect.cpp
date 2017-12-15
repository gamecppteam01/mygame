#include "QuarterEffect.h"
#include "../../Actor/Player/Player.h"

class Player;

QuarterEffect::QuarterEffect(IWorld * world) : world_(world)
{
}

void QuarterEffect::start()
{
	auto target = std::static_pointer_cast<Player>(world_->findActor("Player"));
	effect_ = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::QUARTER_EFFECT);
	EffekseerManager::GetInstance().SetPositionTrackTarget(EFFECT_ID::QUARTER_EFFECT, effect_, &target->position());
}

void QuarterEffect::update(float deltaTime)
{
}

void QuarterEffect::draw()
{
}

void QuarterEffect::end()
{
	EffekseerManager::GetInstance().StopEffect3D(effect_);
}
