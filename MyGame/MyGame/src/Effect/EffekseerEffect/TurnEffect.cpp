#include "TurnEffect.h"
#include "../../Actor/Player/Player.h"
#include "../../Sound/Sound.h"

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
	Sound::GetInstance().PlaySE(SE_ID::TURN_SE, 1, 1);
	Sound::GetInstance().PlaySE(SE_ID::CHEER_SE, 1, 1);
	Sound::GetInstance().SetSEVolume(SE_ID::CHEER_SE, 0.5);
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
	if (Sound::GetInstance().IsPlaySE(SE_ID::CHEER_SE) == true) Sound::GetInstance().StopSE(SE_ID::CHEER_SE);
}
