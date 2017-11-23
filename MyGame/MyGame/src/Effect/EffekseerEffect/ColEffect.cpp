#include "ColEffect.h"

ColEffect::ColEffect(IWorld * world)
{

}

void ColEffect::Initialize()
{
	playerPos_ = Vector3::Zero;
}

void ColEffect::Update(float deltaTime)
{
	auto target_ = std::static_pointer_cast<Player>(world_->findActor("Player"));
	target_->getState();
	playerPos_ = target_->position();
	if (target_->getState() == Player::Player_State::KnockBack) {
		EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::COL_EFFECT, playerPos_, Vector3::Zero, Vector3(1.0f, 1.0f, 1.0f));
	}
}

void ColEffect::Draw() const
{
}

void ColEffect::End()
{
}
