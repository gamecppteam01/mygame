#include "WarningManager.h"
#include "../Input/Keyboard.h"
#include<memory>
#include "../Graphic/Sprite.h"
#include "../Actor/ActorGroup.h"
#include "../Math/Math.h"
#include"../Actor/Player/Player.h"
#include"../Define.h"

WarningManager::WarningManager(IWorld* world)
	:UI{ "warningmanager" , Vector2::Zero }, state_{ warningState::None }, world_(world)
{
	
}

void WarningManager::initialize()
{
	pos = Vector2::Zero;
	sincount = 0.0f;
	count = 0;

	//プレイヤーのポインタを取得
	player_= std::static_pointer_cast<Player>(world_->findActor("Player"));

	//画像の中心
	Vector2 origin = Vector2(100, 0)/*Sprite::GetInstance().GetSize(SPRITE_ID::WARNING) / 2*/;

	//上
	parameters_.emplace(std::piecewise_construct, std::forward_as_tuple(warningState::UP),
		std::forward_as_tuple(Vector2(WINDOW_WIDTH/2,0.0f), Vector2::One, 0.0f, origin));

	//下
	parameters_.emplace(std::piecewise_construct, std::forward_as_tuple(warningState::DOWN),
		std::forward_as_tuple(Vector2(WINDOW_WIDTH/2, WINDOW_HEIGHT), Vector2::One, 180.0f, origin));

	//左
	parameters_.emplace(std::piecewise_construct, std::forward_as_tuple(warningState::LEFT),
		std::forward_as_tuple(Vector2(0.0f, WINDOW_HEIGHT/2), Vector2::One, -90.0f, origin));

	//右
	parameters_.emplace(std::piecewise_construct, std::forward_as_tuple(warningState::RIGHT),
		std::forward_as_tuple(Vector2(WINDOW_WIDTH, WINDOW_HEIGHT/2), Vector2::One, 90.0f, origin));

	//空
	parameters_.emplace(std::piecewise_construct, std::forward_as_tuple(warningState::None),
		std::forward_as_tuple(Vector2::Zero, Vector2::Zero, 0.0f, origin));
	pause_ = false;

}

void WarningManager::pause(){
	pause_ = true;
}

void WarningManager::restart(){
	pause_ = false;
}

void WarningManager::update(float deltaTime)
{
	//危険値が最大20あり10以上で警告の色を変える

	//向きを決定
	Vector2 target = player_.lock()->getStumbleDirection();
	stateChange(target);
	if (!pause_ && warningCount() <= 9) {
		sincount += 8;
		sincount = std::fmodf(sincount, 360);
	}
	else if (!pause_ && warningCount() > 9) {
		sincount += 12;
		sincount = std::fmodf(sincount, 360);
	}
	switch (state_)
	{
	case warningState::UP:
		pos = Vector2::Lerp(Vector2(0, 0), Vector2(0, 50), std::abs(MathHelper::Sin(sincount)));
		break;
	case warningState::DOWN:
		pos = Vector2::Lerp(Vector2(0, 0), Vector2(0, -50), std::abs(MathHelper::Sin(sincount)));
		break;
	case warningState::RIGHT:
		pos = Vector2::Lerp(Vector2(0, 0), Vector2(-50, 0), std::abs(MathHelper::Sin(sincount)));
		break;
	case warningState::LEFT:
		pos = Vector2::Lerp(Vector2(0, 0), Vector2(50, 0), std::abs(MathHelper::Sin(sincount)));
		break;
	case warningState::None:
		break;
	}

	/*
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
	*/

	//時間経過かカウントが0で転倒
}

void WarningManager::draw() const
{
	if (player_.lock()->getState() != Player::Player_State::Stumble)return;

	WarningParamter wp = parameters_.at(state_);
	if (warningCount() <= 9) {
		Sprite::GetInstance().Draw(SPRITE_ID::WARNING, wp.warningPos_ + pos, wp.origin_, wp.scale_, wp.angle_);
	}
	else {
		Sprite::GetInstance().Draw(SPRITE_ID::WARNING2, wp.warningPos_ + pos, wp.origin_, wp.scale_, wp.angle_);
	}
}

float WarningManager::warningCount()const{
	if (player_.lock()->getState() == Player::Player_State::Stumble) {
		return player_.lock()->getTimer() / 7 * 20;
	}
	return 0;
}


void WarningManager::stateChange(const Vector3& v2)
{
	Vector3 V1 = Vector3(1.0f, 0.0f, 1.0f);
	Vector3 V2 = v2;
	V1 = V1.Normalize();
	V2 = V2.Normalize();

	Vector3 cross = Vector3::Cross(V1,V2);

	float result = Vector3::Dot(V1, V2);
	result = MathHelper::ACos(result);
	
	if (cross.y >= 0) {
		result = result * -1;
	}
	if (result >= 0 && result <= 90) {
		state_ = warningState::LEFT;
	}
	if (result >= 90 && result <= 180) {
		state_ = warningState::UP;
	}
	if (result <= 0 && result >= -90) {
		state_ = warningState::DOWN;
	}
	if (result <= -90 && result >= -180) {
		state_ = warningState::RIGHT;
	}
}

void WarningManager::stateChange(const Vector2 & v2)
{
	Vector2 result = Vector2::Zero;

	Vector2 base = Vector2::One;
	Vector2 target = v2;

	base = base.Normalize();
	target = target.Normalize();

	float cross = Vector2::Cross(base, target);
	float dot = Vector2::Dot(base, target);
	dot = MathHelper::ACos(dot);


	//右が+
	if (cross >= 0) {
		dot *= -1;
	}
	if (dot >= 0 && dot <= 90) {
		state_ = warningState::RIGHT;
	}
	if (dot >= 90 && dot <= 180) {
		state_ = warningState::DOWN;
	}
	if (dot <= 0 && dot >= -90) {
		state_ = warningState::UP;
	}
	if (dot <= -90 && dot >= -180) {
		state_ = warningState::LEFT;
	}

}

void WarningManager::stateChange(float angle)
{
	if (angle >= 0 && angle <= 90) {
		state_ = warningState::LEFT;
	}
	if (angle >= 90 && angle <= 180) {
		state_ = warningState::UP;
	}
	if (angle <= 0 && angle >= -90) {
		state_ = warningState::DOWN;
	}
	if (angle <= -90 && angle >= -180) {
		state_ = warningState::RIGHT;
	}

}
