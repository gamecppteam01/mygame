#include "EnemyBullet.h"
#include"../../Graphic/Model.h"

EnemyBullet::EnemyBullet(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr & body):
	Enemy(world, "EnemyBullet", position, body)
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
