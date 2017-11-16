#include "ColEffect.h"

ColEffect::ColEffect(IWorld * world)
{

}

void ColEffect::Initialize()
{
	
}

void ColEffect::Update(float deltaTime)
{
	auto target_ = std::static_pointer_cast<Player>(world_->findActor("Player"));
	target_->getState();
	if (target_->getState() == Player::Player_State::KnockBack) {
		EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::COL_EFFECT, Vector3::Zero, Vector3::Zero, Vector3(10.0f, 10.0f, 10.0f));
	}
}

void ColEffect::Draw() const
{
}

void ColEffect::End()
{
}
