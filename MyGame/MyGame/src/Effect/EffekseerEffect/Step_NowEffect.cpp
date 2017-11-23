#include "Step_NowEffect.h"
#include "../../Graphic/EffekseerManager.h"

Step_NowEffect::Step_NowEffect(IWorld * world)
{
}

void Step_NowEffect::Initialize()
{
	playerPos_ = Vector3::Zero;
}

void Step_NowEffect::Update(float deltaTime)
{
	player_ = std::static_pointer_cast<Player>(world_->findActor("Player"));
	player_->getState();
	playerPos_ = player_->position();
	if (player_->getState() == Player::Player_State::Step) {
		EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::CHARGE_EFFECT,playerPos_, Vector3::Zero, Vector3(10.0f, 10.0f, 10.0f));
	}
}

void Step_NowEffect::Draw() const
{
}

void Step_NowEffect::End()
{
}
