#include "EnemyBullet.h"
#include"../../Graphic/Model.h"
#include"../Player/Player.h"
#include"../Player/PlayerBullet.h"
#include"BaseEnemy.h"

//’e‚«”ò‚Î‚·—Í
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
}

void EnemyBullet::onDraw() const
{
	animation_.Draw();
	//”»’è‚Ì’†S‚É•`‰æˆÊ’u‚ð‡‚í‚¹‚é
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	Model::GetInstance().Draw(modelHandle_, Matrix(rotation_).Translation(drawPosition));
}

void EnemyBullet::onCollide(Actor & other)
{
	if (other.getName() == "Player") {
		Vector3 bound = other.position() - position_;
		bound = bound.Normalize();
		bound *= boundPower;
		bound.y = 0.0f;
		//‘ŠŽè‚ð’µ‚Ë•Ô‚·
		static_cast<Player*>(&other)->addVelocity(bound);

		//Ž©g‚à’µ‚Ë•Ô‚é
		enemy_->hitPlayer(-bound);
		//velocity_ = -bound;
	}
	if (other.getName() == "PlayerBullet") {
		Vector3 bound = other.position() - position_;
		bound = bound.Normalize();
		bound *= boundPower;
		bound.y = 0.0f;
		//‘ŠŽè‚ð’µ‚Ë•Ô‚·
		static_cast<PlayerBullet*>(&other)->hitEnemy(name_, bound);

		//Ž©g‚à’µ‚Ë•Ô‚é
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
