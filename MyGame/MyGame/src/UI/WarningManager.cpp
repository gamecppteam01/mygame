#include "WarningManager.h"
#include "../Input/Keyboard.h"
#include<memory>
#include "../Graphic/Sprite.h"
#include "../Actor/ActorGroup.h"
#include "../Math/Math.h"

WarningManager::WarningManager()
	:UI{ "warningmanager" , position_ }, state_{ warningState::None }
{
	
}

void WarningManager::initialize()
{
	warningCount_ = 3;
	warningTime_ = 0.0f;

	//��
	WarningParamter param;
	param.angle_ = 0.0f;
	param.warningPos_ = Vector2::Zero;
	param.origin_ = Vector2::Zero;
	param.scale_ = Vector2(1.0f, 1.0f);
	parameters_[warningState::UP] = param;

	//��
	param.angle_ = 180.0f;
	param.warningPos_ = Vector2(1280.0f, 720.0f);
	param.origin_ = Vector2::Zero;
	param.scale_ = Vector2(1.0f, 1.0f);
	parameters_[warningState::DOWN] = param;

	//��
	param.angle_ = 90.0f;
	param.warningPos_ = Vector2(1280.0f, 0.0f);
	param.origin_ = Vector2::Zero;
	param.scale_ = Vector2(1.0f, 1.0f);
	parameters_[warningState::LEFT] = param;

	//�E
	param.angle_ = -90.0f;
	param.warningPos_ = Vector2(2.0f,720.0f);
	param.origin_ = Vector2::Zero;
	param.scale_ = Vector2(1.0f, 1.0f);
	parameters_[warningState::RIGHT] = param;

	//��
	param.angle_ = 0.0f;
	param.origin_ = Vector2::Zero;
	param.scale_ = Vector2::Zero;
	param.warningPos_ = Vector2::Zero;
	parameters_[warningState::None] = param;
}

void WarningManager::update(float deltaTime)
{
	//��
	if(Keyboard::GetInstance().KeyStateDown(KEYCODE::G)) {
		Vector3 a = Vector3(0, 0, 1);
		stateChange(a);
	}
	//��
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::H)) {
		Vector3 a = Vector3(1, 0, 0);
		stateChange(a);
	}
	//��
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::J)) {
		Vector3 a = Vector3(0, 0, -1);
		stateChange(a);
	}
	//�E
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::K)) {
		Vector3 a = Vector3(-1, 0, 0);
		stateChange(a);
	}

	//���Ԍo�߂��J�E���g��0�œ]�|
}

void WarningManager::draw() const
{
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
