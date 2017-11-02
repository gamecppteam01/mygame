#include "Enemy_Quick.h"
#include "../EnemyBullet.h"
#include "../../ActorGroup.h"
#include "../../../World/IWorld.h"
#include "../../../Graphic/Model.h"
#include "../../Player/Player.h"
#include "../../Player/PlayerBullet.h"
#include "../../../Graphic/DebugDraw.h"
#include "../../../ScoreManager/ScoreManager.h"
#include "../../../Math/Random.h"
#include "../../../ScoreManager/ScoreMap.h"



//����ɋC�Â��͈�
static const float noticeDistance = 30.0f;

//�R���X�g���N�^
Enemy_Quick::Enemy_Quick(IWorld * world, const std::string & name, const Vector3 & position, int playerNumber, const IBodyPtr & body)
:BaseEnemy(world,name,position,playerNumber,body){
	target_ = world_->findActor("Player");
	m_Timer = 5.0f;
}

//�X�e�b�v�ʒm���̏���
void Enemy_Quick::JustStep() {
	int rand = Random::GetInstance().Range(1, 10);
	if (rand <= 6) {
		//�^�[��
		world_->getCanChangedScoreManager().addScore(playerNumber_, 200);
		change_State_and_Anim(Enemy_State::Step, Enemy_Animation::Turn);
	}
	else {
		//�N�H�[�^�[
		world_->getCanChangedScoreManager().addScore(playerNumber_, 100);
		change_State_and_Anim(Enemy_State::Step, Enemy_Animation::KnockBack);
	}
}

void Enemy_Quick::updateNormal(float deltaTime){
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);

	searchTarget(deltaTime);
	gravity_ -= 0.05f;

	Vector3 jumpVector = Vector3(0.0f, gravity_, 0.0f);
	velocity_ += jumpVector;
	m_Timer--;
}

void Enemy_Quick::to_Normal(){

}

//���G
void Enemy_Quick::searchTarget(float deltaTime) {
	//�^�[�Q�b�g�����݂��Ȃ���΍��G����
	if (target_ == nullptr)return;
	//�^�[�Q�b�g�̈ʒu������
	Vector3 targetPos = target_->position();
	//�^�[�Q�b�g�����̃x�N�g��
	Vector3 toTarget = targetPos - position_;
	//�^�[�Q�b�g�Ƃ̋��������߂�
	float distance = Vector3::Distance(position_, targetPos);

	//�^�[�Q�b�g�Ƃ̋������͈͓���������
	if (distance < noticeDistance) {
		//�^�[�Q�b�g�̋t�����ɓ�����
		velocity_ = -toTarget.Normalize();
		m_Timer = 5.0f;
	}
	else if(distance > noticeDistance && m_Timer <= 0){
		velocity_ = Vector3::Zero;
	}
}