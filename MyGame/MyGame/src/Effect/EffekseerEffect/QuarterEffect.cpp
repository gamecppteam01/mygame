#include "QuarterEffect.h"
#include "../../Actor/Player/Player.h"
#include "../../Sound/Sound.h"

class Player;

QuarterEffect::QuarterEffect(IWorld * world) : world_(world)
{
}

void QuarterEffect::start()
{
	auto target = std::static_pointer_cast<Player>(world_->findActor("Player"));
	effect_ = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::QUARTER_EFFECT);
	EffekseerManager::GetInstance().SetPositionTrackTarget(EFFECT_ID::QUARTER_EFFECT, effect_, &target->position());
	Sound::GetInstance().PlaySE(SE_ID::CHEER_SE, 1, 1);
	Sound::GetInstance().PlaySE(SE_ID::QUATER_SE, 1, 1);
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
	if (Sound::GetInstance().IsPlaySE(SE_ID::CHEER_SE) == true) Sound::GetInstance().StopSE(SE_ID::CHEER_SE);
}
