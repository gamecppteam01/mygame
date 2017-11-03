#include "SpinEffect.h"
#include "../Actor/Player/Player.h"
#include "../Graphic/EffekseerManager.h"


SpinEffect::SpinEffect(IWorld * world)
{
}

void SpinEffect::initialize()
{
}

void SpinEffect::update(float deltaTime)
{
	auto target = world->findActor("Player");
	position_ = target->position();
	position_ += Vector3::Up * 2;
}

void SpinEffect::draw() const
{
	EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::SPIN_EFFECT, position_);
}

void SpinEffect::end()
{
}
