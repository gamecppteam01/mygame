#include "Player.h"
#include"../../Graphic/Model.h"
#include"../../World/IWorld.h"
#include"../../Input/InputChecker.h"
#include"../../Define.h"
#include"../../Field/Field.h"
#include"../../Graphic/DebugDraw.h"
#include"../../Math/Collision/CollisionMesh.h"
#include"../../Math/Collision/Collision.h"
#include"../../Math/Collision/CollisionFunction.h"
#include"../../Conv/DXConverter.h"
#include"../../Graphic/Anime.h"
#include"../../Graphic/Sprite.h"

Player::Player(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body) :
	Actor(world, name, position, body), gravity_(0.0f),animation_(Model::GetInstance().GetHandle(MODEL_ID::PLAYER_MODEL))
{
	modelHandle_ = MODEL_ID::PLAYER_MODEL;

}

void Player::onMessage(EventMessage message, void * param)
{
}

void Player::onUpdate(float deltaTime)
{
	animation_.changeAnim(1,1.0f);
	animation_.update(deltaTime);

	Vector3 framevelocity{ 0.0f,0.0f,0.0f };
	if (InputChecker::GetInstance().StickStateDown(InputChecker::Input_Stick::Right)) {
		framevelocity.x += 0.5f;
	}
	if (InputChecker::GetInstance().StickStateDown(InputChecker::Input_Stick::Left)) {
		framevelocity.x -= 0.5f;
	}
	if (InputChecker::GetInstance().StickStateDown(InputChecker::Input_Stick::Up)) {
		framevelocity.z += 0.5f;
	}
	if (InputChecker::GetInstance().StickStateDown(InputChecker::Input_Stick::Down)) {
		framevelocity.z -= 0.5f;
	}
	if (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::R1)) {
		framevelocity.y -= 0.5f;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::Y)) {
		if(gravity_==0.0f)velocity_.y = 10.0f;
	}
	velocity_ -= velocity_*0.5f;
	framevelocity += velocity_;
	gravity_ -= 0.05f;
	framevelocity.y += gravity_;
	position_ += framevelocity;

	Vector3 result;
	if (field(result)) {
		gravity_ = 0.0f;
		position_ = result;
	}
}

void Player::onDraw() const
{
	//”»’è‚Ì’†S‚É•`‰æˆÊ’u‚ð‡‚í‚¹‚é
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	Model::GetInstance().Draw(modelHandle_, Matrix(rotation_*Matrix::CreateRotationY(180.0f)).Translation(drawPosition));

	body_->draw(position_);
}

void Player::onCollide(Actor & other)
{
}
/*
bool Player::field()
{
	Vector3 hitcenter;
	if (world_->getField()->getMesh().collide_capsule(position_ + body_->points(0), position_ + body_->points(1), body_->radius(), (VECTOR*)&hitcenter))
	{
		gravity_ = 0.0f;
		position_ = hitcenter;// +rotation_.Up()*body_->length()*0.5f;
		OutputDebugString("“–‚½‚Á‚½");
		OutputDebugString("\n");
	}
	else {
		OutputDebugString("“–‚½‚Á‚Ä‚È‚¢");
		OutputDebugString("\n");
	}
}
*/
