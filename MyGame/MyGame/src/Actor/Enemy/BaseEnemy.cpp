#include "BaseEnemy.h"
#include"EnemyBullet.h"
#include"../ActorGroup.h"
#include"../../World/IWorld.h"
#include"../../Graphic/Model.h"
#include"../Player/Player.h"
#include"../Player/PlayerBullet.h"
#include"../../Graphic/DebugDraw.h"
#include"../../ScoreManager/ScoreBase.h"
#include"../../Math/Random.h"

//男と女の距離
static const Vector3 bulletDistance{ 0.0f,0.0f,8.0f };
//弾き飛ばす力
static const float boundPower = 10.0f;
//視界角度
static const float viewAngle = 60.0f;
//動き出す視界角度
static const float moveAngle = 20.0f;

BaseEnemy::BaseEnemy(IWorld * world, const std::string & name, const Vector3 & position,int playerNumber, const IBodyPtr & body):
	Enemy(world,name,position,body),bullet_(std::make_shared<EnemyBullet>(world,name,position,this,body)), turnPower_(1.0f), playerNumber_(playerNumber)
{
	world_->addActor(ActorGroup::ENEMY_BULLET, bullet_);
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::ENEMY_MODEL));

	modelHandle_ = MODEL_ID::ENEMY_MODEL;
	changeAnimation(Enemy_Animation::Idle);

	bullet_->initialize();

	//女の移動と回転の操作権を得る
	bulletPosition_ = bullet_->getPositionPtr();
	bulletRotation_ = bullet_->getRotationPtr();

	target_ = world_->findActor("Player");
}

void BaseEnemy::hitPlayer(const Vector3 & velocity)
{
	bulletVelocity_ += velocity;
	velocity_ += velocity;
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
	default:
		break;
	}	
	//アニメーションを更新
	animation_.Update(MathHelper::Sign(deltaTime));

	bulletUpdate(deltaTime);

	position_ += velocity_;
	velocity_ *= 0.5f;
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
}

void BaseEnemy::onCollide(Actor & other)
{
	if (other.getName() == "Player") {
		Vector3 bound= other.position()-position_;
		bound = bound.Normalize();
		bound *= boundPower;
		bound.y = 0.0f;
		//相手を跳ね返す
		static_cast<Player*>(&other)->addVelocity(bound);
		
		//自身も跳ね返る
		velocity_ = -bound;
	}
	if (other.getName() == "PlayerBullet") {
		Vector3 bound = other.position() - position_;
		bound = bound.Normalize();
		bound *= boundPower;
		bound.y = 0.0f;
		//相手を跳ね返す
		static_cast<PlayerBullet*>(&other)->hitEnemy(name_,bound);

		//自身も跳ね返る
		velocity_ = -bound;

	}
}

void BaseEnemy::JustStep()
{
	std::vector<int> stepAnim{
		(int)Enemy_Animation::KnockBack,
		(int)Enemy_Animation::Move_Forward,
		(int)Enemy_Animation::Step_Left,
		(int)Enemy_Animation::Turn
	};

	change_State_and_Anim(Enemy_State::Step, (Enemy_Animation)Random::GetInstance().Randomize(stepAnim));
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

void BaseEnemy::changeAnimation(Enemy_Animation animID)
{
	animation_.ChangeAnim((int)animID);
}

bool BaseEnemy::change_State(Enemy_State state)
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
	case BaseEnemy::Enemy_State::Normal:
		break;
	case BaseEnemy::Enemy_State::Step:
		to_Step();
		break;
	default:
		break;
	}
	//更新成功
	return true;
}

bool BaseEnemy::change_State_and_Anim(Enemy_State state, Enemy_Animation animID)
{
	if (!change_State(state))return false;
	changeAnimation(animID);

	return true;
}

void BaseEnemy::to_Step()
{
	world_->getScoreBase().AddScore(playerNumber_, 100);

	//対応したアニメーションの終了時間を取得する
	stepTime_ = animation_.GetAnimMaxTime();

}

void BaseEnemy::updateNormal(float deltaTime)
{
	searchTarget(deltaTime);

}

void BaseEnemy::updateStep(float deltaTime)
{
	stepTime_ -= deltaTime;
	//ステップが終了したら待機状態に戻る
	if (stepTime_ <= 0.0f) {
		if (change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Idle))updateNormal(deltaTime);
		return;
	}


}
