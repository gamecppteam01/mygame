#include "StepStanbyEffect.h"
#include "../../Actor/Player/Player.h"

class Player;

StepStanbyEffect::StepStanbyEffect(IWorld * world)
	: world_(world)
{

}

void StepStanbyEffect::start()
{
	auto target = std::static_pointer_cast<Player>(world_->findActor("Player"));
	effect_ = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::STEP_STANDBY_INPUT2_EFFECT);
	EffekseerManager::GetInstance().SetPositionTrackTarget(EFFECT_ID::STEP_STANDBY_INPUT2_EFFECT, effect_, &target->position());
}

void StepStanbyEffect::update(float deltaTime)
{
	
}

void StepStanbyEffect::draw()
{
}

void StepStanbyEffect::end()
{
	EffekseerManager::GetInstance().StopEffect3D(effect_);
}
