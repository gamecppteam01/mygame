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
#include"../EffectActor/UniqueEffectActor/TrackingEffectActor.h"
#include"../../Effect/CircleEffect.h"
#include"../Dummy/BetweenPositionActor.h"
#include"../../Input/DualShock4Manager.h"
#include"../../Judge/JudgeDefine.h"
#include"../../ScoreManager/ScoreManager.h"
#include"../../Graphic/FontManager.h"


//moveからidleに移行する際のinput確認数カウント
static const int inputCheckCount = 4;
//男と女の距離
static const Vector3 bulletDistance{ 0.0f,0.0f,-8.0f };
//回転力の基本係数
static const float defaultTurnPower = 1.0f;
//無視するコントローラの傾き範囲
static const float ignoreSlope = 0.1f;
static const float boundPower = 5.0f;
static const float downTime = 2.0f;
//移動速度
static const float movePower = 0.5f;

Player::Player(IWorld* world, const std::string& name, const Vector3& position,int playerNumber) :
	Actor(world, name, position, std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f),
	Matrix::Identity, 20.0f, 3.0f)), upVelocity_(0.0f),velocity_(Vector3::Zero), gravity_(0.0f),animation_(),
	state_(Player_State::Idle), defaultPosition_(position), 
	bulletVelocity_(Vector3::Zero), turnPower_(1.0f), bound_(Vector3::Zero), playerNumber_(playerNumber),
	gyroCheck_()
{
	createBullet();
	world_->addActor(ActorGroup::PLAYER_BULLET, bullet_);

	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::PLAYER_MODEL));
	bullet_->changeAnimation(PlayerBullet::PlayerBullet_Animation::Move_Forward);
	initialize();

	//各種更新関数を設定する
	playerUpdateFunc_[Player_State::Idle] = [this](float deltaTime) {idle_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Move] = [this](float deltaTime) {move_Update(deltaTime); };
	//playerUpdateFunc_[Player_State::Jump] = [this](float deltaTime) {jump_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Step] = [this](float deltaTime) {step_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Step_Success] = [this](float deltaTime) {stepSuccess_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Attack] = [this](float deltaTime) {attack_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Shoot] = [this](float deltaTime) {shoot_Update(deltaTime); };
	playerUpdateFunc_[Player_State::ShootEnd] = [this](float deltaTime) {shootend_Update(deltaTime); };
	playerUpdateFunc_[Player_State::KnockBack] = [this](float deltaTime) {knockback_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Down] = [this](float deltaTime) {down_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Stumble] = [this](float deltaTime) {stumble_Update(deltaTime); };

	//各種状態変更関数を設定する
	playerToNextModeFunc_[Player_State::Idle] = [this]() {to_IdleMode(); };
	playerToNextModeFunc_[Player_State::Move] = [this]() {to_MoveMode(); };
	//playerToNextModeFunc_[Player_State::Jump] = [this]() {to_JumpMode(); };
	playerToNextModeFunc_[Player_State::Step] = [this]() {to_StepMode(); };
	playerToNextModeFunc_[Player_State::Step_Success] = [this]() {to_StepSuccessMode(); };
	playerToNextModeFunc_[Player_State::Attack] = [this]() {to_AttackMode(); };
	playerToNextModeFunc_[Player_State::Shoot] = [this]() {to_ShootMode(); };
	playerToNextModeFunc_[Player_State::ShootEnd] = [this]() {to_ShootEndMode(); };
	playerToNextModeFunc_[Player_State::KnockBack] = [this]() {to_KnockBackMode(); };
	playerToNextModeFunc_[Player_State::Down] = [this]() {to_DownMode(); };
	playerToNextModeFunc_[Player_State::Stumble] = [this]() {to_StumbleMode(); };

	playerEndModeFunc_[Player_State::Idle] = [this]() {		end_IdleMode(); };
	playerEndModeFunc_[Player_State::Move] = [this]() {		end_MoveMode(); };
	playerEndModeFunc_[Player_State::Step] = [this]() {		end_StepMode(); };
	playerEndModeFunc_[Player_State::Step_Success] = [this]() {		end_StepSuccessMode(); };
	playerEndModeFunc_[Player_State::Attack] = [this]() {	end_AttackMode(); };
	playerEndModeFunc_[Player_State::Shoot] = [this]() {	end_ShootMode(); };
	playerEndModeFunc_[Player_State::ShootEnd] = [this]() {	end_ShootEndMode(); };
	playerEndModeFunc_[Player_State::KnockBack] = [this]() {end_KnockBackMode(); };
	playerEndModeFunc_[Player_State::Down] = [this]() {		end_DownMode(); };
	playerEndModeFunc_[Player_State::Stumble] = [this]() {		end_StumbleMode(); };
	
}

void Player::addVelocity(const Vector3 & velocity)
{
	velocity_ += velocity;
}

void Player::hitEnemy(const std::string& hitName, const Vector3& velocity)
{
	bound_ += velocity;

	if (state_ == Player_State::Attack)return;

	stumbleDirection_= mathStumbleDirection(Vector2(-velocity.x, -velocity.z));

	//stumbleDirection_ = -velocity;
	change_State_and_Anim(Player_State::Stumble, Player_Animation::KnockBack);
}

void Player::createBullet()
{
	bullet_ = std::make_shared<PlayerBullet>(world_, position_, this);
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

	//女の移動と回転の操作権を得る
	bulletPosition_ = bullet_->getPositionPtr();
	bulletRotation_ = bullet_->getRotationPtr();

	gyroCheck_.initialize();
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
	//判定の中心に描画位置を合わせる
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	animation_.Draw(Matrix(rotation_).Translation(drawPosition));


	if (world_->getStepTimer().isJustTime()) {
		DebugDraw::DebugDrawFormatString(0, 0, GetColor(255, 255, 255), "akrmkermekr");
	}


	DrawFormatStringToHandle(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, GetColor(255, 255, 255), FontManager::GetInstance().GetFontHandle(FONT_ID::JAPANESE_FONT), std::to_string(nextStep_).c_str());
	
	if (state_ != Player_State::Step)return;

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
	if ((other.getName() == "Enemy" || other.getName() == "EnemyBullet") && isCanStamble()) {

	}

}
void Player::onCollideResult()
{
	bound_.y = 0.0f;
	Vector3 bound = bound_.Normalize()*boundPower;
	bound.y = 0.0f;
	bulletVelocity_ += bound;
	//シュート時でなければプレイヤー自身も発射する
	if (state_ != Player_State::Shoot)velocity_ += bound;

	bound_ = Vector3::Zero;
}

void Player::JustStep()
{
	
}

void Player::CreateJustEffect()
{
	createCircleEffect();
}

bool Player::field(Vector3 & result)
{
	if (!world_->getField()->isInField(position_)) {
		position_ = world_->getField()->CorrectPosition(position_);
	}
	Vector3 hit1;
	Vector3 hit2;
	if (world_->getField()->getMesh().collide_capsule(position_ + body_->points(0), position_ + body_->points(1), body_->radius(), *bulletPosition_ + body_->points(0), *bulletPosition_ + body_->points(1), bullet_->body_->radius(), (VECTOR*)&hit1, (VECTOR*)&hit2))
	{
		result = hit1 + ((body_->points(0)));

		return true;
	}
	return false;
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

	//状態の終了処理を行う
	playerEndModeFunc_[state_]();
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
	//Vector2 move = getSticktoMove();
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
	Vector2 move = DualShock4Manager::GetInstance().GetAngle();
	//Vector2 move = getSticktoMove();
	if (std::abs(move.x) < ignoreSlope && std::abs(move.y) < ignoreSlope) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle))playerUpdateFunc_[state_](deltaTime);
		return;
	}
	framevelocity.x += move.x*movePower;
	framevelocity.z += move.y*movePower;

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
	if (!isChangeStep()) {
		if (nextStep_ != 0) {
			//ダンスが成立してたら対応したアニメーションを再生(実行順序の関係でここではStateの変更のみ行い、内部で実行されるto_StepSuccessにてアニメーションを更新する)
			if (change_State(Player_State::Step_Success))playerUpdateFunc_[state_](deltaTime);
			return;
		}
		else {
			if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle))playerUpdateFunc_[state_](deltaTime);
			return;
		}
	}

	gyroCheck_.update();
	Vector2 rotate = gyroCheck_.getRotate();
	if (abs(rotate.y) >= 270.0f) {
		//1回転成立
		successStep_ = 3;
	}
	else if (rotate.y >= 160.0f)successStep_ = 2;
	else if (rotate.y >= 90.0f&&successStep_ != 2)successStep_ = 1;

	if (std::abs(gyroCheck_.getAngle()) >= 300.0f) {
		successStep_ = 4;
		nextStep_ = successStep_;
		gyroCheck_.initAngle();
	}
	OutputDebugString(std::to_string(DualShock4Manager::GetInstance().GetAngle3D().z).c_str());
	OutputDebugString("\n");
	if (DualShock4Manager::GetInstance().GetAngle3D().z > 45.0f&&DualShock4Manager::GetInstance().GetAngle3D().z <= 100.0f) {
		gyroCheck_.initRotate();
		nextStep_ = successStep_;
	}

}

void Player::stepSuccess_Update(float deltaTime)
{
	stepTime_ -= deltaTime;
	//ステップが終了したら待機状態に戻る
	if (stepTime_ <= 0.0f) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle))playerUpdateFunc_[state_](deltaTime);
		return;
	}
}

void Player::attack_Update(float deltaTime)
{
	stepTime_ -= deltaTime;
	//ステップが終了したら待機状態に戻る
	if (stepTime_ <= 0.0f) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle))playerUpdateFunc_[state_](deltaTime);
		return;
	}
	stepAttack(deltaTime);
	

}

void Player::shoot_Update(float deltaTime)
{
	//回転を更新
	*bulletRotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -20.0f*turnPower_);

	Vector3 framevelocity{ 0.0f,0.0f,0.0f };
	Vector2 move = DualShock4Manager::GetInstance().GetAngle();
	//Vector2 move = getSticktoMove();
	//回転力を移動速度に追加
	move *= turnPower_;
	if (std::abs(move.x) < ignoreSlope && std::abs(move.y) < ignoreSlope) {
		//if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle))playerUpdateFunc_[state_](deltaTime);
		//return;
	}
	framevelocity.x += move.x*movePower;
	framevelocity.z += move.y*movePower;
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
	downTime_ += deltaTime;

	if (downTime_ >= downTime) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle))playerUpdateFunc_[state_](deltaTime);
	}
}

void Player::turn_Update(float deltaTime)
{
	if (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::R1)) {
		rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), 5.0f);
	}

}

void Player::stumble_Update(float deltaTime)
{
	stumbleTime_ += deltaTime;
	//よろけ時間がダウン時間に到達したら転倒
	if (stumbleTime_ >= fallTime) {
		//転倒処理を書く
		if (change_State_and_Anim(Player_State::Down, Player_Animation::Down))playerUpdateFunc_[state_](deltaTime);

	}

	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);

	Vector3 framevelocity{ 0.0f,0.0f,0.0f };
	Vector2 move = DualShock4Manager::GetInstance().GetAngle();
	//Vector2 move = getSticktoMove();
	//よろけ修正方向を向いたら
	if (Vector3::Angle(Vector3(stumbleDirection_.x,0.0f,stumbleDirection_.y),Vector3(move.x,0.0f,move.y))<=20.0f&&move.Length()>=0.3f) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle))playerUpdateFunc_[state_](deltaTime);
		return;
	}
	framevelocity.x += move.x*movePower;
	framevelocity.z += move.y*movePower;

	upVelocity_ -= upVelocity_*0.5f;

	velocity_ += framevelocity;

	gravityUpdate(deltaTime);

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
	//ジャスト判定タイミングならスコア加算フラグを有効にする
	isJustStep_ = world_->getStepTimer().isJustTime();

	gyroCheck_.initialize();
	successStep_ = 0;
	nextStep_ = 0;
}

void Player::to_StepSuccessMode()
{
	//スコア加算を呼び出す(ステップ開始時点でジャスト判定に合っていなかったら加算されない)
	if (isJustStep_) {
		world_->getCanChangedScoreManager().addScore(playerNumber_, stepAnimScoreList_.at(nextStep_).second);
	}

	changeAnimation(stepAnimScoreList_.at(nextStep_).first);

	//対応したアニメーションの終了時間を取得する
	stepTime_ = animation_.GetAnimMaxTime((int)stepAnimScoreList_.at(nextStep_).first);

	if (nextStep_ == 2) {
		change_State_and_Anim(Player_State::Attack, stepAnimScoreList_.at(nextStep_).first);
		return;
	}


	if (world_->getStepTimer().isJustTime()) {

	}
}

void Player::to_AttackMode()
{
	changeAnimation(stepAnimScoreList_.at(nextStep_).first);

	//対応したアニメーションの終了時間を取得する
	stepTime_ = animation_.GetAnimMaxTime((int)stepAnimScoreList_.at(nextStep_).first);

	std::list<ActorPtr> enemys;
	world_->findActors("Enemy", enemys);

	attackTarget_ = enemys.front();
	for (auto& e : enemys) {
		if (Vector3::Distance(position_, attackTarget_->position()) > Vector3::Distance(position_, e->position())) {
			attackTarget_ = e;
		}
	}

}

void Player::to_ShootMode()
{
	std::shared_ptr<BetweenPositionActor> point= std::make_shared<BetweenPositionActor>();
	point->addTarget(shared_from_this());
	point->addTarget(bullet_);
	world_->addActor(ActorGroup::DUMMYACTOR, point);
	world_->getCamera()->setTarget((ActorPtr)point);
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

void Player::to_StumbleMode()
{
	stumbleTime_ = 0.0f;
}

void Player::end_IdleMode()
{
}

void Player::end_MoveMode()
{
}

void Player::end_StepMode()
{
}

void Player::end_StepSuccessMode()
{
}

void Player::end_AttackMode()
{
}

void Player::end_ShootMode()
{
	ActorPtr cameraPoint = world_->findActor("Point");
	if(cameraPoint!=nullptr)cameraPoint->dead();
}

void Player::end_ShootEndMode()
{
}

void Player::end_KnockBackMode()
{
}

void Player::end_DownMode()
{
}

void Player::end_TurnMode()
{
}

void Player::end_StumbleMode()
{
}

void Player::stepAttack(float deltaTime)
{
	position_ += (attackTarget_->position() - position_).Normalize() *2.f;
}

void Player::changeAnimation(Player_Animation animID, float animSpeed) {
	animation_.ChangeAnim((int)animID);
}

bool Player::isChangeStep() const
{
	return  {
		(
		InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::A) ||
		InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::B) ||
		InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::X) ||
		InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::Y)
		)
		&&
		InputChecker::GetInstance().GetPovAngle() != -1
	};
}
bool Player::isCanStamble() const
{
	if (state_ == Player_State::Idle || state_ == Player_State::Move || state_ == Player_State::Step)return true;
	if (state_ == Player_State::Step_Success && (nextStep_ != 2 && nextStep_ != 4))return true;
	return false;
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

void Player::createCircleEffect()
{
	std::shared_ptr<CircleEffect> circleEffect = std::make_shared<CircleEffect>(40.0f, justEffectStartTime);
	world_->addActor(ActorGroup::EFFECT, std::make_shared<TrackingEffectActor>(world_,"CircleEffect",position_, circleEffect,shared_from_this()));
}

Vector2 Player::getSticktoMove()
{
	Vector2 result = InputChecker::GetInstance().Stick();
	result.y = -result.y;
	return result;

}

Vector2 Player::mathStumbleDirection(const Vector2 & stumbleDirection)
{
	
	Vector2 result = Vector2::Zero;

	Vector2 base = Vector2::One;
	Vector2 target = stumbleDirection;

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
		result = Vector2::Left;
	}
	if (dot >= 90 && dot <= 180) {
		result = Vector2::Up;
	}
	if (dot <= 0 && dot >= -90) {
		result = Vector2::Down;
	}
	if (dot <= -90 && dot >= -180) {
		result = Vector2::Right;
	}
	return result;
}
