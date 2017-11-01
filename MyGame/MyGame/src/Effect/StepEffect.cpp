#include "StepEffect.h"
#include "../Graphic/EffekseerManager.h"
#include "../Input/InputChecker.h"
#include "../Actor/Player/Player.h"

void StepEffect::Initialize()
{

}

void StepEffect::Update(float deltaTime)
{
	player_ = std::static_pointer_cast<Player>(world_->findActor("Player"));
	player_->getState();
	if (player_->getState() == Player::Player_State::Step) {
		EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::ACTION_EFFECT, Vector3::Zero, Vector3::Zero, Vector3::One);
	}
}

void StepEffect::Draw() const
{
}

void StepEffect::End()
{
}

