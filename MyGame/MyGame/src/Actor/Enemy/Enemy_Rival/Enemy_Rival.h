#pragma once
#include "../BaseEnemy.h"
#include<queue>

class Enemy_Rival : public BaseEnemy {
private:
	enum class chooseAttackTargetMode {
		NotAttack,//�ʏ펞
		AttackMove,//�U���Ώۂɋ߂Â�
		Attack,//�U��
		Return,//���̈ʒu�ɖ߂�
		Step,//�X�e�b�v����
		StepMove//�X�e�b�v�ʒu�ɍs��
	};
public:
	//�R���X�g���N�^
	Enemy_Rival(IWorld* world, const std::string& name, const Vector3& position, int playerNumber, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));

private:
	// �`��
	virtual void onDraw() const override;

	//�X�e�b�v�ʒm���̏���
	virtual void JustStep()override;

	virtual void updateNormal(float deltaTime)override;
	virtual void updateTrack(float deltaTime)override;
	virtual void to_Normal()override;
	virtual void to_Track()override;
	virtual void to_Attack(BaseEnemy::Enemy_Animation anim)override;
	//����|�C���g�ꗗ�̂����ł��߂��_�����߂�
	int getNearestPoint(const Vector3 & position);

private:
	//Track����p�̃X�e�b�v�X�V
	void justStepTrack();
	//Track�̎����[�h�ւ̈ڍs
	void toNextStepTrackMode(chooseAttackTargetMode nextMode);

	//�U���Ώۂ����݂��Ă���ꍇ
	void chooseStepAttackTarget(const ActorPtr& player);
	//�v���C���[��1�ʂ�������
	void chooseStepAttackTopPlayer(const ActorPtr& player, const Vector3 basePos);
	bool chooseStepIsAttack();

	void setNextPosition();

	//�]�|�J�E���g�̃Z�b�g
	virtual void setCountDown();
private:
	//���̃|�C���g
	int nextPoint_{ 0 };

	//�_���ꏊ
	Vector3 targetPos_{ Vector3::Zero };
	//�U���Ώۂ��߂邩
	chooseAttackTargetMode chooseAttackTargetMode_{ chooseAttackTargetMode::NotAttack };
	//�U���Ώۂ̏����ʒu
	Vector3 attackTargetDefaultPos_{ Vector3::Zero };
	//�U�����̎��g�̏����ʒu
	Vector3 attackStartDefaultPos_{ Vector3::Zero };
	//�I��Q
	std::list<std::weak_ptr<Actor>> players_;
	//stepAnim�̃L�[�ԍ����X�g
	std::queue<int> stepQueue_;
	//�X�e�[�W����|�C���g�z��
	std::vector<Vector3> roundPoint_;

	MethodTimer defAnimSetTimer_;
};