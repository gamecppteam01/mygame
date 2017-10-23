#include "EnemyBullet.h"
#include"../../Graphic/Model.h"
#include"../Player/Player.h"
#include"../Player/PlayerBullet.h"
#include"BaseEnemy.h"

//弾き飛ばす力
static const float boundPower = 10.0f;

EnemyBullet::EnemyBullet(IWorld * world, const std::string & name, const Vector3 & position,BaseEnemy* enemy, const IBodyPtr & body):
	Enemy(world, "EnemyBullet", position, body), enemy_(enemy)
{
		modelHandle_ = MODEL_ID::ENEMY_MODEL;
		animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::ENEMY_MODEL));

}

void EnemyBullet::onMessage(EventMessage message, void * param)
{
}

void EnemyBullet::onUpdate(float deltaTime)
{
	//アニメーションを更新
	animation_.Update(MathHelper::Sign(deltaTime));

}

void EnemyBullet::onDraw() const
{
	//判定の中心に描画位置を合わせる
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	animation_.Draw(Matrix(rotation_).Translation(drawPosition));
}

void EnemyBullet::onCollide(Actor & other)
{
	if (other.getName() == "Player") {
		Vector3 bound = other.position() - position_;
		bound = bound.Normalize();
		bound *= boundPower;
		bound.y = 0.0f;
		//相手を跳ね返す
		static_cast<Player*>(&other)->addVelocity(bound);

		//自身も跳ね返る
		enemy_->hitPlayer(-bound);
		//velocity_ = -bound;
	}
	if (other.getName() == "PlayerBullet") {
		Vector3 bound = other.position() - position_;
		bound = bound.Normalize();
		bound *= boundPower;
		bound.y = 0.0f;
		//相手を跳ね返す
		static_cast<PlayerBullet*>(&other)->hitEnemy(name_, bound);

		//自身も跳ね返る
		enemy_->hitPlayer(-bound);
		//velocity_ = -bound;

	}

}

Vector3 * EnemyBullet::getPositionPtr()
{
	return &position_;
}

Matrix * EnemyBullet::getRotationPtr()
{
	return &rotation_;
}

void EnemyBullet::changeAnimation(EnemyBullet_Animation animID)
{
	animation_.ChangeAnim((int)animID);

}
