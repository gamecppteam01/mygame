#pragma once
#include "../BaseEnemy.h"
#include "../../../ScoreManager/ScoreManager.h"
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

	enum class LightState {
		Extinction,
		CenterLighting,
		SpotLighting,
	};
	enum class RivalState {
		AttackMode,
		MoveMode,
		StepMode,
	};
public:
	Enemy_Rival();
	//�R���X�g���N�^
	Enemy_Rival(IWorld* world, const std::string& name, const Vector3& position, int playerNumber, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));

	virtual std::shared_ptr<BaseEnemy> Create(IWorld* world, const Vector3& position, int playerNumber)override;

private:
	virtual void JustStep() override{}
	//������
	void initialize();
	virtual void onMessage(EventMessage message, void * param) override;
	// �`��
	virtual void onDraw() const override;

	virtual void onShadowDraw() const override;

	virtual void updateNormal(float deltaTime)override;
	virtual void to_Normal()override;
	virtual void to_Step(Enemy_Animation anim) override;
	virtual void to_Attack(Enemy_Animation anim) override;

	//virtual void spin(float deltaTime)override;

	//����|�C���g�ꗗ�̂����ł��߂��_�����߂�
	int getNearestPoint(const Vector3 & position);
	void setNearestPoint();

private:

	void setNextPosition();

	void ExtinctionUpdate(float deltaTime);
	void CenterLightingUpdate(float deltaTime);
	void SpotLighting(float deltaTime);

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
	//�X�R�A�}�l�[�W���[
	ScoreManager* scoreManager_;
	//���C�g���W
	Vector3 lightPosition_;
	//�X�^�[�g���W
	Vector3 startPos_;

	//�O�̍U���^�C�v
	AttackType prevAttackType_;
	MethodTimer defAnimSetTimer_;
	//�y�A��
	int count_{ 0 };
	//�ړ���~�J�E���g
	int moveCount_{ 0 };
	//�X�e�b�v�J�E���g
	int stepCount_{ 0 };
	//�ړ��^�C�}�[
	float moveTimer_{ 0.0f };
	//��~�^�C�}�[
	float stopTimer_{ 0.0f };
	//���C�g�̏��
	LightState lightState_{ LightState::Extinction };
	//���
	RivalState rivalState_{ RivalState::AttackMode };
	//�O�̏��
	RivalState prevRivalState_;

	std::map<LightState, std::function<void(float deltaTime)>> m_LightStateUpdateFunc;

};