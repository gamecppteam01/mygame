#include "BaseEnemy.h"
#include"EnemyBullet.h"
#include"../ActorGroup.h"
#include"../../World/IWorld.h"
#include"../../Graphic/Model.h"
#include"../Player/Player.h"
#include"../Player/PlayerBullet.h"
#include"../../Graphic/DebugDraw.h"
#include"../../ScoreManager/ScoreManager.h"
#include"../../Math/Random.h"
#include"../../ScoreManager/ScoreMap.h"
#include"../../Field/Field.h"
#include"../../Input/InputChecker.h"

//男と女の距離
static const Vector3 bulletDistance{ 0.0f,0.0f,8.0f };
//弾き飛ばす力
static const float boundPower = 5.0f;
//視界角度
static const float viewAngle = 60.0f;
//動き出す視界角度
static const float moveAngle = 20.0f;
//基本的なダウン値
static const int defDownCount = 1;
//ダウンする時間
static const float downTime = 2.0f;

BaseEnemy::BaseEnemy(IWorld * world, const std::string & name, const Vector3 & position,int playerNumber, const IBodyPtr & body):
	Enemy(world,name,position,body),bullet_(std::make_shared<EnemyBullet>(world,name,position,this,body)), turnPower_(1.0f), playerNumber_(playerNumber), nextPosition_(position),
	downCount_(defDownCount)
{
	world_->addActor(ActorGroup::ENEMY_BULLET, bullet_);
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::ENEMY_MODEL));
	bullet_->changeAnimation(EnemyBullet::EnemyBullet_Animation::Move_Forward);
	modelHandle_ = MODEL_ID::ENEMY_MODEL;
	changeAnimation(Enemy_Animation::Move_Forward);

	bullet_->initialize();

	//女の移動と回転の操作権を得る
	bulletPosition_ = bullet_->getPositionPtr();
	bulletRotation_ = bullet_->getRotationPtr();

	target_ = world_->findActor("Player");
	
}

void BaseEnemy::hitOther(const Vector3 & velocity)
{
	bound_ += velocity;
	//bulletVelocity_ += velocity;
	//velocity_ += velocity;
}

void BaseEnemy::onMessage(EventMessage message, void * param)
{
}

void BaseEnemy::onUpdate(float deltaTime){
	
	switch (state_)
	{
	case BaseEnemy::Enemy_State::Normal: {
		updateNormal(deltaTime);
		break; 
	}
	case BaseEnemy::Enemy_State::Step: {
		updateStep(deltaTime);
		break;
	}
	case BaseEnemy::Enemy_State::Track: {
		updateTrack(deltaTime);
		break;
	}
	case BaseEnemy::Enemy_State::Attack: {
		updateAttack(deltaTime);
		break;
	}
	case BaseEnemy::Enemy_State::Down: {
		updateDown(deltaTime);
		break;
	}
	default:
		break;
	}	
	//アニメーションを更新
	animation_.Update(MathHelper::Sign(deltaTime));

	Vector2 result = InputChecker::GetInstance().Stick();

	velocity_+= Vector3(result.x,0.0f,result.y);

	position_ += velocity_;
	velocity_ *= 0.5f;

	correctPosition();

	bulletUpdate(deltaTime);


}

void BaseEnemy::onDraw() const
{
	//判定の中心に描画位置を合わせる
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	animation_.Draw(Matrix::CreateRotationY(180.0f)*Matrix(rotation_).Translation(drawPosition));
	
	//ターゲットが存在しなければ索敵無効
	if (target_ == nullptr)return;
	//ターゲットの位置を検索
	Vector3 targetPos = target_->position();
	//ターゲット方向のベクトル
	Vector3 toTarget = targetPos - position_;
	float forwardAngle = MathHelper::ACos(Vector3::Dot(rotation_.Forward().Normalize(), toTarget.Normalize()));

	DebugDraw::DebugDrawFormatString(50, 50, GetColor(255, 255, 255), "%f", forwardAngle);

	switch (state_)
	{
	case BaseEnemy::Enemy_State::Normal:
		DebugDraw::DebugDrawFormatString(100, 100, GetColor(255, 255, 255), "Normal");
		break;
	case BaseEnemy::Enemy_State::Step:
		DebugDraw::DebugDrawFormatString(100, 100, GetColor(255, 255, 255), "Step");
		break;
	case BaseEnemy::Enemy_State::Track:
		DebugDraw::DebugDrawFormatString(100, 100, GetColor(255, 255, 255), "Track");
		break;
	case BaseEnemy::Enemy_State::Attack:
		DebugDraw::DebugDrawFormatString(100, 100, GetColor(255, 255, 255), "Attack");
		break;
	case BaseEnemy::Enemy_State::Down:
		DebugDraw::DebugDrawFormatString(100, 100, GetColor(255, 255, 255), "Down");
		break;
	default:
		break;
	}
}

void BaseEnemy::onCollide(Actor & other)
{
	if (other.getName() == "Player") {
		Vector3 bound = mathBound(other);
		//相手を跳ね返す

		static_cast<Player*>(&other)->hitEnemy(name_,bound);
		//自身も跳ね返る
		hitOther(-bound);
		if (state_ == Enemy_State::Attack&&other.getCharacterNumber()==attackTarget_->getCharacterNumber())return;
		setCountDown();
	}
	else if (other.getName() == "PlayerBullet") {
		Vector3 bound = mathBound(other);
		//相手を跳ね返す
		static_cast<PlayerBullet*>(&other)->hitEnemy(name_, bound);
		//自身も跳ね返る
		hitOther(-bound);
		if (state_ == Enemy_State::Attack)return;
		setCountDown();
	}
	else if (other.getName() == "Enemy") {
		//自分自身なら判定しない
		if (static_cast<BaseEnemy*>(&other)->getPlayerNumber() == playerNumber_) return;

		Vector3 bound = mathBound(other);
		//相手を跳ね返す
		static_cast<BaseEnemy*>(&other)->hitOther(bound);
		//自身も跳ね返る
		hitOther(-bound);
		if (state_ == Enemy_State::Attack)return;
		setCountDown();
	}
	else if (other.getName() == "EnemyBullet") {
		if (static_cast<EnemyBullet*>(&other)->enemy_->playerNumber_ == playerNumber_)return;
		Vector3 bound = mathBound(other);
		//相手を跳ね返す
		static_cast<EnemyBullet*>(&other)->hitOther(bound);
		//自身も跳ね返る
		hitOther(-bound);
		if (state_ == Enemy_State::Attack)return;
		setCountDown();
	}

}

void BaseEnemy::onCollideResult()
{
	bound_.y = 0.0f;
	Vector3 bound = bound_.Normalize()*boundPower;
	bound.y = 0.0f;
	
	bulletVelocity_ += bound;
	velocity_ += bound;

	bound_ = Vector3::Zero;

	downTimer_.Action();
	//ダウン値が溜まったら
	if (downCount_ <= 0) {
		change_State_and_Anim(Enemy_State::Down, Enemy_Animation::Down);
	}
}

Vector3 BaseEnemy::mathBound(Actor & other)
{
	Vector3 bound = other.position() - position_;
	bound = bound.Normalize();
	bound *= boundPower;
	bound.y = 0.0f;

	return bound;
}
bool BaseEnemy::field(Vector3 & result)
{
	Vector3 hit1;
	Vector3 hit2;
	if (world_->getField()->getMesh().collide_capsule(position_ + body_->points(0), position_ + body_->points(1), body_->radius(), *bulletPosition_ + body_->points(0), *bulletPosition_ + body_->points(1), bullet_->body_->radius(), (VECTOR*)&hit1, (VECTOR*)&hit2))
	{
		result = hit1 + ((body_->points(0)));

		return true;
	}
	return false;
}

void BaseEnemy::JustStep()
{
	//if (Random::GetInstance().Range(1, 100) <= 50)return;


	//攻撃射程圏内なら
	if (Vector3::Distance(getNearestActor()->position(), position_)<= attackDistance) {
		change_State_and_Anim(Enemy_State::Attack, stepAnim[1].first);
		return;
	}
	int key = Random::GetInstance().Range(0, 1);
	if (key == 1)key++;

	change_State_and_Anim(Enemy_State::Step, stepAnim[key].first);
	world_->getCanChangedScoreManager().addScore(playerNumber_, stepAnim[key].second);
}

void BaseEnemy::searchTarget(float deltaTime)
{
	//ターゲットが存在しなければ索敵無効
	if (target_ == nullptr)return;
	//ターゲットの位置を検索
	Vector3 targetPos = target_->position();
	//ターゲット方向のベクトル
	Vector3 toTarget = targetPos - position_;
	//角度を求める
	float forwardAngle = MathHelper::ACos(Vector3::Dot(rotation_.Forward().Normalize(), toTarget.Normalize()));
	float leftAngle = MathHelper::ACos(Vector3::Dot(rotation_.Left().Normalize(), toTarget.Normalize()));

	//行動範囲内だったら
	if (forwardAngle < moveAngle) {
		float moveSpeed = 0.5f;
		//ターゲット方向に前進
		position_ += toTarget.Normalize()*moveSpeed;
	}
	//視界範囲内だったら
	if (forwardAngle < viewAngle) {
		//自身を回転させる
		float rotateAngle = 3.0f;
		//左なら右に
		if (leftAngle > 90.0f) rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -rotateAngle);
		//右なら左に
		else if(leftAngle < 90.0f) rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), rotateAngle);
		
	}
}

void BaseEnemy::bulletUpdate(float deltaTime)
{
	*bulletPosition_ = position_ + (bulletDistance*rotation_);

	*bulletRotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -20.0f*turnPower_);

}

void BaseEnemy::addVelocity_NextPosition(float deltaTime)
{
	velocity_ += (nextPosition_ - position_).Normalize()*movePower;
}

void BaseEnemy::changeAnimation(Enemy_Animation animID)
{
	animation_.ChangeAnim((int)animID);
}

bool BaseEnemy::change_State(Enemy_State state,BaseEnemy::Enemy_Animation anim)
{
	//状態が変わらないなら失敗
	if (state_ == state)return false;

	//状態の終了処理を行う
	switch (state_)
	{
	case BaseEnemy::Enemy_State::Normal:
		break;
	case BaseEnemy::Enemy_State::Step:
		break;
	default:
		break;
	}
	//状態を更新
	state_ = state;

	//状態変更を行う
	switch (state_)
	{
	case BaseEnemy::Enemy_State::Normal:{
		to_Normal();
		break;
	}
	case BaseEnemy::Enemy_State::Step:{
		to_Step(anim);
		break;
	}
	case BaseEnemy::Enemy_State::Track:{
		to_Track();
		break;
	}
	case BaseEnemy::Enemy_State::Attack: {
		to_Attack(anim);
		break;
	}
	case BaseEnemy::Enemy_State::Down: {
		to_Down();
		break;
	}
	default:
		break;
	}
	//更新成功
	return true;
}

bool BaseEnemy::change_State_and_Anim(Enemy_State state, Enemy_Animation animID)
{
	if (!change_State(state,animID))return false;
	changeAnimation(animID);

	return true;
}

void BaseEnemy::to_Normal()
{
}

void BaseEnemy::to_Step(BaseEnemy::Enemy_Animation anim)
{
	world_->getScoreManager().addScore(playerNumber_, 100);

	//対応したアニメーションの終了時間を取得する
	stepTime_ = animation_.GetAnimMaxTime((int)anim);

}

void BaseEnemy::to_Track()
{
	nextPosition_ = world_->getCanChangedScoreMap().getNextPoint(position_)+Vector3(Random::GetInstance().Range(-20.0f,20.0f),0.0f, Random::GetInstance().Range(-20.0f, 20.0f));
}

void BaseEnemy::to_Attack(BaseEnemy::Enemy_Animation anim)
{
	attackTarget_ = getNearestActor();

	//stepTime_ = animation_.GetAnimMaxTime((int)anim);
	stepTime_ = 1.5f;
}

void BaseEnemy::to_Down()
{
	//ダウン値を元に戻して
	downCount_ = defDownCount;
	downTime_ = 0.0f;
}

void BaseEnemy::updateNormal(float deltaTime)
{
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);

	//searchTarget(deltaTime);
	gravity_ -= 0.05f;

	Vector3 jumpVector = Vector3(0.0f, gravity_, 0.0f);
	velocity_ += jumpVector;

}

void BaseEnemy::updateStep(float deltaTime)
{
	stepTime_ -= deltaTime;
	//ステップが終了したら待機状態に戻る
	if (stepTime_ <= 0.0f) {
		if (change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Move_Forward))updateNormal(deltaTime);
		return;
	}


}

void BaseEnemy::updateTrack(float deltaTime)
{
	if (Vector2::Distance(Vector2(position_.x, position_.z), Vector2(nextPosition_.x, nextPosition_.z)) <= 10.0f) {
		if (change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Move_Forward))updateNormal(deltaTime);
		return;
	}
	addVelocity_NextPosition(deltaTime);

}
void BaseEnemy::updateAttack(float deltaTime)
{
	stepTime_ -= deltaTime;
	//ステップが終了したら待機状態に戻る
	if (stepTime_ <= 0.0f) {
		if (change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Move_Forward))updateNormal(deltaTime);
		return;
	}

	position_ += (attackTarget_->position() - position_).Normalize() *movePower;

}
void BaseEnemy::updateDown(float deltaTime)
{
	downTime_ += deltaTime;

	if (downTime_ >= downTime) {
		if (change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Idle))updateDown(deltaTime);
	}

}
void BaseEnemy::correctPosition()
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

ActorPtr BaseEnemy::getNearestActor()
{
	ActorPtr attackTarget=nullptr;
	std::list<ActorPtr> others;
	world_->findActors("Enemy", others);

	others.remove_if([this] (const ActorPtr& ap){
		return std::static_pointer_cast<BaseEnemy>(ap)->getPlayerNumber() == getPlayerNumber();
	});
	
	auto player = world_->findActor("Player");
	others.push_back(player);

	attackTarget = others.front();
	for (auto& e : others) {
		if (Vector3::Distance(position_, attackTarget->position()) > Vector3::Distance(position_, e->position())) {
			attackTarget = e;
		}
	}
	return attackTarget;
}

void BaseEnemy::setCountDown()
{
	downTimer_.Initialize();
	downTimer_.Add([this] {downCount_--; });
}
