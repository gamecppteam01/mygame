#include "WarningManager.h"
#include "../Input/Keyboard.h"
#include<memory>
#include "../Graphic/Sprite.h"
#include "../Actor/ActorGroup.h"
#include "../Math/Math.h"
#include"../Actor/Player/Player.h"

WarningManager::WarningManager(IWorld* world)
	:UI{ "warningmanager" , position_ }, state_{ warningState::None }, world_(world)
{
	
}

void WarningManager::initialize()
{
	//プレイヤーのポインタを取得
	player_= std::static_pointer_cast<Player>(world_->findActor("Player"));

	//画像の中心
	Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::WARNING) / 2;

	//上
	parameters_.emplace(std::piecewise_construct, std::forward_as_tuple(warningState::UP),
		std::forward_as_tuple(Vector2::Zero, Vector2::One, 0.0f, origin));

	//下
	parameters_.emplace(std::piecewise_construct, std::forward_as_tuple(warningState::DOWN),
		std::forward_as_tuple(Vector2(1280.0f, 720.0f), Vector2::One, 180.0f, origin));

	//左
	parameters_.emplace(std::piecewise_construct, std::forward_as_tuple(warningState::LEFT),
		std::forward_as_tuple(Vector2(1280.0f, 0.0f), Vector2::One, 90.0f, origin));

	//右
	parameters_.emplace(std::piecewise_construct, std::forward_as_tuple(warningState::RIGHT),
		std::forward_as_tuple(Vector2(0.0f, 720.0f), Vector2::One, -90.0f, origin));

	//空
	parameters_.emplace(std::piecewise_construct, std::forward_as_tuple(warningState::None),
		std::forward_as_tuple(Vector2::Zero, Vector2::Zero, 0.0f, origin));

}

void WarningManager::update(float deltaTime)
{
	//上
	if(Keyboard::GetInstance().KeyStateDown(KEYCODE::G)) {
		Vector3 a = Vector3(0, 0, 1);
		stateChange(a);
	}
	//下
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::H)) {
		Vector3 a = Vector3(1, 0, 0);
		stateChange(a);
	}
	//左
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::J)) {
		Vector3 a = Vector3(0, 0, -1);
		stateChange(a);
	}
	//右
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::K)) {
		Vector3 a = Vector3(-1, 0, 0);
		stateChange(a);
	}

	//時間経過かカウントが0で転倒
}

void WarningManager::draw() const
{
	if (player_.lock()->getState() != Player::Player_State::Stumble)return;

	WarningParamter wp = parameters_.at(state_);
	Sprite::GetInstance().Draw(SPRITE_ID::WARNING, wp.warningPos_, wp.origin_, wp.scale_, wp.angle_);
}


void WarningManager::stateChange(const Vector3& v2)
{
	Vector3 V1 = Vector3(1.0f, 0.0f, 1.0f);
	Vector3 V2 = v2;
	V1.Normalize();
	V2.Normalize();

	Vector3 cross = Vector3::Cross(V1,V2);

	float result = Vector3::Dot(V1, V2);
	result = MathHelper::ACos(result);
	

	if (cross.y >= 0) {
		result = result * -1;
	}
	if (result >= 0 && result <= 90) {
		state_ = warningState::UP;
	}
	if (result >= 90 && result <= 180) {
		state_ = warningState::LEFT;
	}
	if (result <= 0 && result >= -90) {
		state_ = warningState::DOWN;
	}
	if (result <= -90 && result >= -180) {
		state_ = warningState::RIGHT;
	}
}
