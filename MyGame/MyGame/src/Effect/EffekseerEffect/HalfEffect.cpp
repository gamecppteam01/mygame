#include "HalfEffect.h"
#include "../../Actor/Player/Player.h"

class Player;

HalfEffect::HalfEffect(IWorld * world) : world_(world)
{
}

void HalfEffect::start()
{
	auto target = std::static_pointer_cast<Player>(world_->findActor("Player"));
	effect_ = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::HALF_EFFECT);
	EffekseerManager::GetInstance().SetPositionTrackTarget(EFFECT_ID::HALF_EFFECT, effect_, &target->position());
	Sound::GetInstance().PlaySE(SE_ID::HALF_SE, 1, 1);
	Sound::GetInstance().PlaySE(SE_ID::CHEER_SE, 1, 1);
}

void HalfEffect::update(float deltaTime)
{
}

void HalfEffect::draw()
{
}

void HalfEffect::end()
{
	EffekseerManager::GetInstance().StopEffect3D(effect_);
	if (Sound::GetInstance().IsPlaySE(SE_ID::CHEER_SE) == true) Sound::GetInstance().StopSE(SE_ID::CHEER_SE);
}
