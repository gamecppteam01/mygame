#include "TurnEffect.h"
#include "../../Actor/Player/Player.h"

class Player;

TurnEffect::TurnEffect(IWorld * world)
	:world_(world)
{
	
}

void TurnEffect::start()
{
	auto target = std::static_pointer_cast<Player>(world_->findActor("Player"));
	effect_ = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::TURN_EFFECT);
	EffekseerManager::GetInstance().SetPositionTrackTarget(EFFECT_ID::TURN_EFFECT, effect_, &target->position());
}

void TurnEffect::update(float deltaTime)
{
}

void TurnEffect::draw()
{
}

void TurnEffect::end()
{
	EffekseerManager::GetInstance().StopEffect3D(effect_);
}
