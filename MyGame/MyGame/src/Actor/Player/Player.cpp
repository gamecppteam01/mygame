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
#include"PlayerBullet.h"
#include"../ActorGroup.h"
#include"../../Camera/OverLookingCamera.h"
#include"../EffectActor/EffectActor.h"
#include"../../Effect/CircleEffect.h"

//moveからidleに移行する際のinput確認数カウント
static int inputCheckCount = 4;
//男と女の距離
static Vector3 bulletDistance{ 0.0f,0.0f,-8.0f };
//回転力の基本係数
static float defaultTurnPower = 1.0f;
//無視するコントローラの傾き範囲
static float ignoreSlope = 0.1f;
//ジャスト判定の時間
static float justTime = 0.5f;
//ジャストエフェクトの生成時間
static float justEffectStartTime = 0.5f;

Player::Player(IWorld* world, const std::string& name, const Vector3& position) :
	Actor(world, name, position, std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f),
	Matrix::Identity, 20.0f, 3.0f)), upVelocity_(0.0f),velocity_(Vector3::Zero), gravity_(0.0f),animation_(),
	state_(Player_State::Idle), defaultPosition_(position), bullet_(std::make_shared<PlayerBullet>(world,position))
	, bulletVelocity_(Vector3::Zero), turnPower_(1.0f), justTimer_(0.0f), stepMaxTime_(0.0f)
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

	justTimer_ = 0.0f;
	turnPower_ = 1.0f;
	bullet_->initialize();

	//女の移動と回転の操作権を得る
	bulletPosition_ = bullet_->getPositionPtr();
	bulletRotation_ = bullet_->getRotationPtr();

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

	if (justTimer_ >= -justTime&&justTimer_<=0.0f) {
		DebugDraw::DebugDrawFormatString(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, GetColor(255, 255, 255), "ジャスト!");
	}
	if (state_ != Player_State::Step)return;

	int drawPos = 0;
	for (auto i:stepCombo_)
	{
		drawPos += 30;
		switch (i)
		{
		case Player::Step_Type::Chasse:
			DebugDraw::DebugDrawFormatString(200,drawPos,GetColor(255,255,255),"シャッセ");
			break;
		case Player::Step_Type::Turn:
			DebugDraw::DebugDrawFormatString(200, drawPos, GetColor(255, 255, 255), "ターン");
			break;
		case Player::Step_Type::Whisk:
			DebugDraw::DebugDrawFormatString(200, drawPos, GetColor(255, 255, 255), "ホイスク");
			break;
		case Player::Step_Type::SplitCubanBreak:
			DebugDraw::DebugDrawFormatString(200, drawPos, GetColor(255, 255, 255), "スプリットキューバンブレイク");
			break;
		case Player::Step_Type::Empty:
			DebugDraw::DebugDrawFormatString(200, drawPos, GetColor(255, 255, 255), "空");
			break;
		case Player::Step_Type::Dance_Count:
			break;
		default:
			break;
		}
	}
	//float ringSize = stepMaxTime_ - max(justTimer_,0.0f);
	//ringSize = ringSize / stepMaxTime_;
	//Model::GetInstance().Draw2D(MODEL_ID::EFFECT_CIRCLE_MODEL, position_, 0, ringSize*64.0f);
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
	//Vector2 move = DualShock4Manager::GetInstance().GetAngle();
	Vector2 move = getSticktoMove();
	if (std::abs(move.x) > ignoreSlope || std::abs(move.y) > ignoreSlope) {
		if (change_State_and_Anim(Player_State::Move, Player_Animation::Move_Forward))playerUpdateFunc_[state_](deltaTime);
		return;
	}
	if (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::R1)) {
		if (change_State_and_Anim(Player_State::Shoot, Player_Animation::Shoot))playerUpdateFunc_[state_](deltaTime);
		return;
		//rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), 5.0f);
	}
	//if (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::L1)) {
	//	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);
	//}
	if (isChangeStep()) {
		if (change_State_and_Anim(Player_State::Step, Player_Animation::Step_Left))playerUpdateFunc_[state_](deltaTime);
		return;
	}
	upVelocity_ -= upVelocity_*0.5f;

	gravityUpdate(deltaTime);

}

void Player::move_Update(float deltaTime)
{
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);

	Vector3 framevelocity{ 0.0f,0.0f,0.0f };
	//Vector2 move = DualShock4Manager::GetInstance().GetAngle();
	Vector2 move = getSticktoMove();
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

	if (isChangeStep()) {
		if (change_State_and_Anim(Player_State::Step, Player_Animation::Step_Left))playerUpdateFunc_[state_](deltaTime);
		return;
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
	justTimer_ -= deltaTime;
	if (justTimer_ < -justTime) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle))playerUpdateFunc_[state_](deltaTime);
	}
	//エフェクト生成時間が来たらエフェクト生成関数を呼び出す
	if (justTimer_ <= justEffectStartTime) {
		effectCreator_.Action();
	}
	//タイマーが終わってなかったら更新しない
	if (justTimer_ > 0.0f)return;
	int count = 0;
	//空のコンボを検索する
	for (auto& i : stepCombo_) {
		if (i == Step_Type::Empty) {
			break;
		}
		count++;
	}
	//コンボが全て成立していたら元に戻る
	if (count == stepCombo_.size()) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle))playerUpdateFunc_[state_](deltaTime);
		return;
	}
	
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
		addStep(count, 2.0f, (Step_Type)InputChecker::Input_Key::A);
		//justTimer_ = 2.0f;
		//stepMaxTime_ = justTimer_;
		//
		//stepCombo_.at(count) = (Step_Type)InputChecker::Input_Key::A;
	}
	else if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::B)) {
		addStep(count, 1.0f, (Step_Type)InputChecker::Input_Key::B);
		
		//justTimer_ = 1.0f;
		//stepMaxTime_ = justTimer_;
		//
		//stepCombo_.at(count) = (Step_Type)InputChecker::Input_Key::B;
	}
	else if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::X)) {
		addStep(count, 3.0f, (Step_Type)InputChecker::Input_Key::X);
		
		//justTimer_ = 3.0f;
		//stepMaxTime_ = justTimer_;
		//
		//stepCombo_.at(count) = (Step_Type)InputChecker::Input_Key::X;
	}
	else if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::Y)) {
		addStep(count, 2.0f, (Step_Type)InputChecker::Input_Key::Y);
		
		//justTimer_ = 2.0f;
		//stepMaxTime_ = justTimer_;
		//
		//stepCombo_.at(count) = (Step_Type)InputChecker::Input_Key::Y;
	}
}

void Player::attack_Update(float deltaTime)
{
}

void Player::shoot_Update(float deltaTime)
{
	//回転を更新
	*bulletRotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -20.0f*turnPower_);

	Vector3 framevelocity{ 0.0f,0.0f,0.0f };
	//Vector2 move = DualShock4Manager::GetInstance().GetAngle();
	Vector2 move = getSticktoMove();
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
	//コンボをリセットする
	for (auto& sc : stepCombo_) {
		sc = Step_Type::Empty;
	}
	justTimer_ = 0.0f;
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

bool Player::isChangeStep() const
{
	return  InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)||
			InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::B)||
			InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::X)||
			InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::Y);
}

bool Player::isCanTracking() const
{
	//発射時以外は追従する
	return state_!=Player_State::Shoot;
}

void Player::bulletUpdate(float deltaTime)
{
	*bulletPosition_ = position_ + (bulletDistance*rotation_);
	
	*bulletRotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -20.0f*turnPower_);

}

void Player::addStep(int stepCount,float stepTime, Step_Type type)
{
	justTimer_ = stepTime;
	stepMaxTime_ = justTimer_;

	stepCombo_.at(stepCount) = type;

	effectCreator_.Add([this] {createCircleEffect(); });
}

void Player::createCircleEffect()
{
	std::shared_ptr<CircleEffect> circleEffect = std::make_shared<CircleEffect>(40.0f, justEffectStartTime);
	world_->addActor(ActorGroup::EFFECT, std::make_shared<EffectActor>(world_,"CircleEffect",position_, circleEffect));
}

Vector2 Player::getSticktoMove()
{
	Vector2 result = InputChecker::GetInstance().Stick();
	result.y = -result.y;
	return result;

}


