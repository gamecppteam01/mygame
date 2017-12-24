#include "SpinEffect.h"
#include "../../Actor/Player/Player.h"
#include "../../Graphic/EffekseerManager.h"
#include"../../Sound/Sound.h"

class Player;

SpinEffect::SpinEffect(IWorld * world) : world_(world)
{
}

void SpinEffect::start()
{
	auto target = std::static_pointer_cast<Player>(world_->findActor("Player"));
	effect_ = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::SPIN_EFFECT);
	EffekseerManager::GetInstance().SetPositionTrackTarget(EFFECT_ID::SPIN_EFFECT, effect_, &target->position());
	Sound::GetInstance().PlaySE(SE_ID::SPIN_SE, 1, 1);
	Sound::GetInstance().PlaySE(SE_ID::CHEER_SE, 1, 1);
	Sound::GetInstance().SetSEVolume(SE_ID::CHEER_SE, 0.5);
}

void SpinEffect::update(float deltaTime)
{
	
}

void SpinEffect::draw() const
{
	
}

void SpinEffect::end()
{
	EffekseerManager::GetInstance().StopEffect3D(effect_);
	if (Sound::GetInstance().IsPlaySE(SE_ID::CHEER_SE) == true) Sound::GetInstance().StopSE(SE_ID::CHEER_SE);
}
