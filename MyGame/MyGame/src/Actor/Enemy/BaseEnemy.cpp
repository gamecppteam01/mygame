#include "BaseEnemy.h"
#include"EnemyBullet.h"
#include"../ActorGroup.h"
#include"../../World/IWorld.h"
#include"../../Graphic/Model.h"
#include"../Player/Player.h"

//�j�Ə��̋���
static Vector3 bulletDistance{ 0.0f,0.0f,-8.0f };

static float boundPower = 10.0f;

BaseEnemy::BaseEnemy(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr & body):
	Enemy(world,name,position,body),bullet_(std::make_shared<EnemyBullet>(world,name,position,body)), turnPower_(1.0f)
{
	world_->addActor(ActorGroup::ENEMY_BULLET, bullet_);
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::ENEMY_MODEL));

	modelHandle_ = MODEL_ID::ENEMY_MODEL;
	changeAnimation(Enemy_Animation::Idle);

	bullet_->initialize();

	//���̈ړ��Ɖ�]�̑��쌠�𓾂�
	bulletPosition_ = bullet_->getPositionPtr();
	bulletRotation_ = bullet_->getRotationPtr();

}

void BaseEnemy::onMessage(EventMessage message, void * param)
{
}

void BaseEnemy::onUpdate(float deltaTime)
{
	bulletUpdate(deltaTime);

	position_ += velocity_;
	velocity_ *= 0.5f;
}

void BaseEnemy::onDraw() const
{
	animation_.Draw();
	//����̒��S�ɕ`��ʒu�����킹��
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	Model::GetInstance().Draw(modelHandle_, Matrix(rotation_).Translation(drawPosition));
}

void BaseEnemy::onCollide(Actor & other)
{
	if (other.getName() == "Player") {
		Vector3 bound= other.position()-position_;
		bound = bound.Normalize();
		bound *= boundPower;
		bound.y = 0.0f;
		//����𒵂˕Ԃ�
		static_cast<Player*>(&other)->addVelocity(bound);
		
		//���g�����˕Ԃ�
		velocity_ = -bound;
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
