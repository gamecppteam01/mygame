#include "Player.h"
#include"../../Graphic/Model.h"
#include"../../World/IWorld.h"
#include"../../Input/InputChecker.h"
#include"../../Define.h"
#include"../../Field/Field.h"
#include"../../Graphic/DebugDraw.h"
#include"../../Math/Collision/CollisionMesh.h"
#include"../../Math/Collision/Collision.h"
#include"../../Conv/DXConverter.h"
#include"../../Graphic/Anime.h"
#include"../../Graphic/Sprite.h"
#include"../Body/BoundingCapsule.h"
#include"../../Input/DualShock4Manager.h"
#include"PlayerBullet.h"
#include"../ActorGroup.h"
#include"../../Camera/OverLookingCamera.h"

//moveからidleに移行する際のinput確認数カウント
static int inputCheckCount = 4;
//男と女の距離
static Vector3 bulletDistance{ 8.0f,0.0f,0.0f };
//回転力の基本係数
static float defaultTurnPower = 1.0f;
//無視するコントローラの傾き範囲
static float ignoreSlope = 0.1f;


Player::Player(IWorld* world, const std::string& name, const Vector3& position) :
	Actor(world, name, position, std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f),
	Matrix::Identity, 20.0f, 3.0f)), upVelocity_(0.0f),velocity_(Vector3::Zero), gravity_(0.0f),animation_(),
	state_(Player_State::Idle), defaultPosition_(position), bullet_(std::make_shared<PlayerBullet>(world,position))
	, bulletVelocity_(Vector3::Zero), turnPower_(1.0f)
{
	world_->addActor(ActorGroup::PLAYER_BULLET, bullet_);

	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::PLAYER_MODEL));

	initialize();

	//各種更新関数を設定する
	playerUpdateFunc_[Player_State::Idle] = [this](float deltaTime) {idle_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Move] = [this](float deltaTime) {move_Update(deltaTime); };
	//playerUpdateFunc_[Player_State::Jump] = [this](float deltaTime) {jump_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Step] = [this](float deltaTime) {step_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Attack] = [this](float deltaTime) {attack_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Shoot] = [this](float deltaTime) {shoot_Update(deltaTime); };
	playerUpdateFunc_[Player_State::ShootEnd] = [this](float deltaTime) {shootend_Update(deltaTime); };
	playerUpdateFunc_[Player_State::KnockBack] = [this](float deltaTime) {knockback_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Down] = [this](float deltaTime) {down_Update(deltaTime); };

	//各種状態変更関数を設定する
	playerToNextModeFunc_[Player_State::Idle] = [this]() {to_IdleMode(); };
	playerToNextModeFunc_[Player_State::Move] = [this]() {to_MoveMode(); };
	//playerToNextModeFunc_[Player_State::Jump] = [this]() {to_JumpMode(); };
	playerToNextModeFunc_[Player_State::Step] = [this]() {to_StepMode(); };
	playerToNextModeFunc_[Player_State::Attack] = [this]() {to_AttackMode(); };
	playerToNextModeFunc_[Player_State::Shoot] = [this]() {to_ShootMode(); };
	playerToNextModeFunc_[Player_State::ShootEnd] = [this]() {to_ShootEndMode(); };
	playerToNextModeFunc_[Player_State::KnockBack] = [this]() {to_KnockBackMode(); };
	playerToNextModeFunc_[Player_State::Down] = [this]() {to_DownMode(); };
}

void Player::initialize()
{
	position_ = defaultPosition_;
	gravity_ = 0.0f;
	state_ = Player_State::Idle;
	modelHandle_ = MODEL_ID::PLAYER_MODEL;
	changeAnimation(Player_Animation::Idle);

	turnPower_ = 1.0f;
	bullet_->initialize();
	bulletPosition_ = bullet_->getPositionPtr();
}

void Player::onMessage(EventMessage message, void * param)
{
}

void Player::onUpdate(float deltaTime)
{
	playerUpdateFunc_[state_](deltaTime);
	animation_.Update(MathHelper::Sign(deltaTime));

	//今フレームの更新を適用
	position_ += velocity_;
	velocity_ -= velocity_*0.5f;
	correctPosition();

	//女を更新する
	if(isCanTracking())bulletUpdate(deltaTime);
}

void Player::onDraw() const
{
	animation_.Draw();
	//判定の中心に描画位置を合わせる
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	Model::GetInstance().Draw(modelHandle_, Matrix(rotation_).Translation(drawPosition));

	//body_->draw(position_);
}

void Player::onCollide(Actor & other)
{
	if (other.getName() == "PlayerBullet"&&state_== Player_State::Shoot) {
		change_State_and_Anim(Player_State::ShootEnd, Player_Animation::ShootEnd);
	}
}


void Player::gravityUpdate(float deltaTime)
{
	gravity_ -= 0.05f;

	Vector3 jumpVector = Vector3(0.0f, upVelocity_ + gravity_, 0.0f);
	velocity_ += jumpVector;

}


void Player::correctPosition()
{
	Vector3 result;
	if (field(result)) {
		position_ = result;
	}
	Vector3 start = position_ + body_->points(1);
	Vector3 end = start + Vector3::Down*(body_->radius() + 1.0f);
	if (world_->getField()->getMesh().collide_line(start, end)) {
		gravity_ = 0.0f;
	}

}

bool Player::change_State_and_Anim(Player_State state, Player_Animation animID, float animSpeed)
{
	if (!change_State(state))return false;
	changeAnimation(animID, animSpeed);

	return true;
}

bool Player::change_State(Player_State state)
{
	//状態が変わらないなら失敗
	if (state_ == state)return false;
	//状態を更新
	state_ = state;
	//状態変更を行う
	playerToNextModeFunc_[state_]();
	//更新成功
	return true;
}

void Player::idle_Update(float deltaTime)
{
	Vector2 move = DualShock4Manager::GetInstance().GetAngle();
	if (std::abs(move.x) > ignoreSlope || std::abs(move.y) > ignoreSlope) {
		if (change_State_and_Anim(Player_State::Move, Player_Animation::Move_Forward))playerUpdateFunc_[state_](deltaTime);
		return;
	}
	if (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::R1)) {
		if (change_State_and_Anim(Player_State::Shoot, Player_Animation::Shoot))playerUpdateFunc_[state_](deltaTime);
		return;
		//rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), 5.0f);
	}
	if (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::L1)) {
		rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);
	}
	upVelocity_ -= upVelocity_*0.5f;

	gravityUpdate(deltaTime);

}

void Player::move_Update(float deltaTime)
{
	Vector3 framevelocity{ 0.0f,0.0f,0.0f };
	Vector2 move = DualShock4Manager::GetInstance().GetAngle();
	if (std::abs(move.x) < ignoreSlope && std::abs(move.y) < ignoreSlope) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle))playerUpdateFunc_[state_](deltaTime);
		return;
	}
	framevelocity.x += move.x;
	framevelocity.z += move.y;

	if (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::R1)) {
		if (change_State_and_Anim(Player_State::Shoot, Player_Animation::Shoot))playerUpdateFunc_[state_](deltaTime);
		return;
		//rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), 5.0f);
	}
	if (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::L1)) {
		rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);
	}

	upVelocity_ -= upVelocity_*0.5f;

	//framevelocity = framevelocity * rotation_;
	velocity_ += framevelocity;

	gravityUpdate(deltaTime);

}

/*
void Player::jump_Update(float deltaTime)
{
	Vector3 framevelocity{ 0.0f,0.0f,0.0f };
	if (InputChecker::GetInstance().StickStateDown(InputChecker::Input_Stick::Right)) {
		framevelocity.x += 1.0f;
	}
	if (InputChecker::GetInstance().StickStateDown(InputChecker::Input_Stick::Left)) {
		framevelocity.x -= 1.0f;
	}
	if (InputChecker::GetInstance().StickStateDown(InputChecker::Input_Stick::Up)) {
		framevelocity.z += 1.0f;
	}
	if (InputChecker::GetInstance().StickStateDown(InputChecker::Input_Stick::Down)) {
		framevelocity.z -= 1.0f;
	}


	upVelocity_ -= upVelocity_*0.5f;

	if (!InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::B)) {
		if (upVelocity_ < 5.0f&& gravity_ == 0.0f) {
			if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle)) {
				playerUpdateFunc_[state_](deltaTime);
			}
		}
	}
	gravityUpdate(deltaTime);

	velocity_ += framevelocity;
}
*/

void Player::step_Update(float deltaTime)
{
}

void Player::attack_Update(float deltaTime)
{
}

void Player::shoot_Update(float deltaTime)
{
	Vector3 framevelocity{ 0.0f,0.0f,0.0f };
	Vector2 move = DualShock4Manager::GetInstance().GetAngle();
	if (std::abs(move.x) < ignoreSlope && std::abs(move.y) < ignoreSlope) {
		//if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle))playerUpdateFunc_[state_](deltaTime);
		//return;
	}
	framevelocity.x += move.x;
	framevelocity.z += move.y;
	framevelocity += bulletVelocity_;
	bulletVelocity_ *= 0.98f;

	*bulletPosition_ += framevelocity;
}

void Player::shootend_Update(float deltaTime)
{
	if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle))playerUpdateFunc_[state_](deltaTime);
}

void Player::knockback_Update(float deltaTime)
{
}

void Player::down_Update(float deltaTime)
{
}

void Player::turn_Update(float deltaTime)
{
	if (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::R1)) {
		rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), 5.0f);
	}

}

void Player::to_IdleMode()
{

}

void Player::to_MoveMode()
{

}

/*
void Player::to_JumpMode()
{
	upVelocity_ = 20.0f;
}
*/

void Player::to_StepMode()
{

}

void Player::to_AttackMode()
{

}

void Player::to_ShootMode()
{
	world_->getCamera()->setTarget((ActorPtr)bullet_);
	Vector3 shootVector = *bulletPosition_ - position_;
	shootVector = shootVector.Normalize();
	bulletVelocity_ = shootVector*(turnPower_*defaultTurnPower);
}

void Player::to_ShootEndMode()
{
	world_->getCamera()->setTarget(shared_from_this());

}

void Player::to_KnockBackMode()
{

}

void Player::to_DownMode()
{

}

void Player::to_TurnMode()
{
}

void Player::changeAnimation(Player_Animation animID, float animSpeed) {
	animation_.ChangeAnim((int)animID);
}

bool Player::isCanTracking() const
{
	//発射時以外は追従する
	return state_!=Player_State::Shoot;
}

void Player::bulletUpdate(float deltaTime)
{
	*bulletPosition_ = position_ + (bulletDistance*rotation_);
}


