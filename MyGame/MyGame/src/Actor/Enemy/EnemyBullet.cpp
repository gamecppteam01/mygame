#include "EnemyBullet.h"
#include"../../Graphic/Model.h"
#include"../Player/Player.h"
#include"../Player/PlayerBullet.h"
#include"BaseEnemy.h"

//�e����΂���
static const float boundPower = 10.0f;

EnemyBullet::EnemyBullet(IWorld * world, const std::string & name, const Vector3 & position,BaseEnemy* enemy, MODEL_ID id, const IBodyPtr & body):
	Enemy(world, "EnemyBullet", position, body), enemy_(enemy)
{
		modelHandle_ = id;
		animation_.SetHandle(Model::GetInstance().GetHandle(id));

}

void EnemyBullet::hitOther(const Vector3 & bound)
{
	enemy_->hitOther(bound);
}

int EnemyBullet::getAttackPower() const
{
	return enemy_->getAttackPower();
}

void EnemyBullet::onMessage(EventMessage message, void * param)
{
}

void EnemyBullet::onUpdate(float deltaTime)
{
	//�A�j���[�V�������X�V
	animation_.Update(MathHelper::Sign(deltaTime));

}

void EnemyBullet::onDraw() const
{
	//����̒��S�ɕ`��ʒu�����킹��
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	animation_.Draw(Matrix(rotation_).Translation(drawPosition));
}

void EnemyBullet::onCollide(Actor & other)
{
	if (other.getName() == "Player") {
		Vector3 bound = mathBound(other);
		enemy_->setCountDown(static_cast<Player*>(&other)->getAttackPower());
		//����𒵂˕Ԃ�
		static_cast<Player*>(&other)->hitEnemy(name_, bound);
		//���g�����˕Ԃ�
		hitOther(-bound);
		//velocity_ = -bound;
		int keysub;
		if (enemy_->attackTarget_.expired())keysub = 2;
		else keysub = other.getCharacterNumber() == enemy_->attackTarget_.lock()->getCharacterNumber();
		if (enemy_->state_ == BaseEnemy::Enemy_State::Attack && (keysub == 0 || keysub == -1)) {
			enemy_->change_State_and_Anim(BaseEnemy::Enemy_State::Normal, BaseEnemy::Enemy_Animation::Move_Forward);
			return;
		}

	}
	if (other.getName() == "PlayerBullet") {
		Vector3 bound = mathBound(other);
		enemy_->setCountDown(static_cast<PlayerBullet*>(&other)->getAttackPower());
		//����𒵂˕Ԃ�
		static_cast<PlayerBullet*>(&other)->hitEnemy(name_, bound);
		//���g�����˕Ԃ�
		hitOther(-bound);
		//velocity_ = -bound;
		int keysub;
		if (enemy_->attackTarget_.expired())keysub = 2;
		else keysub = other.getCharacterNumber() == enemy_->attackTarget_.lock()->getCharacterNumber();
		if (enemy_->state_ == BaseEnemy::Enemy_State::Attack && (keysub == 0 || keysub == 1)) {
			enemy_->change_State_and_Anim(BaseEnemy::Enemy_State::Normal, BaseEnemy::Enemy_Animation::Move_Forward);
			return;
		}
	}
	else if (other.getName() == "ShootCenter") {
		Vector3 bound = mathBound(other);
		enemy_->setBoundPower(4);
		//���g�����˕Ԃ�
		hitOther(-bound);
		enemy_->setCountDown(20);
	}
	else if (other.getName() == "Enemy") {
		//�������g�Ȃ画�肵�Ȃ�
		if (static_cast<BaseEnemy*>(&other)->getPlayerNumber() == enemy_->playerNumber_) return;
		enemy_->setCountDown(static_cast<BaseEnemy*>(&other)->getAttackPower());

		Vector3 bound = mathBound(other);
		//����𒵂˕Ԃ�
		static_cast<BaseEnemy*>(&other)->hitOther(bound);
		//���g�����˕Ԃ�
		hitOther(-bound);
		int keysub;
		if (enemy_->attackTarget_.expired())keysub = 2;
		else keysub = other.getCharacterNumber() == enemy_->attackTarget_.lock()->getCharacterNumber();
		if (enemy_->state_ == BaseEnemy::Enemy_State::Attack && (keysub == 0 || keysub == -1)) {
			enemy_->change_State_and_Anim(BaseEnemy::Enemy_State::Normal, BaseEnemy::Enemy_Animation::Move_Forward);
			return;
		}
	}

	if (other.getName() == "EnemyBullet") {
		if (static_cast<EnemyBullet*>(&other)->enemy_->getPlayerNumber() == enemy_->getPlayerNumber())return;
		enemy_->setCountDown(static_cast<EnemyBullet*>(&other)->getAttackPower());

		Vector3 bound = mathBound(other);
		//����𒵂˕Ԃ�
		static_cast<EnemyBullet*>(&other)->hitOther(bound);
		//���g�����˕Ԃ�
		hitOther(-bound);

		//�U����Ԃ���Ȃ�������J�E���g��i�߂�
		int keysub;
		if (enemy_->attackTarget_.expired())keysub = 2;
		else keysub = other.getCharacterNumber() == enemy_->attackTarget_.lock()->getCharacterNumber();
		if (enemy_->state_ == BaseEnemy::Enemy_State::Attack && (keysub == 0 || keysub == 1)) {
			enemy_->change_State_and_Anim(BaseEnemy::Enemy_State::Normal, BaseEnemy::Enemy_Animation::Move_Forward);
			return;
		}

	}

}

Vector3 EnemyBullet::mathBound(Actor & other)
{
	Vector3 bound = other.position() - position_;
	bound = bound.Normalize();
	bound *= boundPower;
	bound.y = 0.0f;

	return bound;
}

void EnemyBullet::stepAnimUpdate(float deltaTime)
{
	animation_.Update(1.0f);
}

Vector3 * EnemyBullet::getPositionPtr()
{
	return &position_;
}

Matrix * EnemyBullet::getRotationPtr()
{
	return &rotation_;
}

void EnemyBullet::changeAnimation(EnemyBullet_Animation animID, float animFrame, float animSpeed, bool isLoop)
{
	animation_.ChangeAnim((int)animID, animFrame, animSpeed,isLoop);

}
