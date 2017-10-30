#pragma once
#include"Enemy.h"
#include"../Body/BoundingCapsule.h"

class EnemyBullet;

class BaseEnemy :public Enemy {
public:
	//�A�j���[�V�����̃L�[�ԍ�(�e�l�́A���ۂ�mv1�ɐݒ肳��Ă���A�j���[�V�����Ɗ֘A�t���鎖)
	enum class Enemy_Animation {
		Idle = 0,//�ҋ@��
		Move_Forward = 1,//�O�ړ���
		Step_Left = 2,//���X�e�b�v��
		Turn = 3,//��]��
		KnockBack = 4,//��e��
		Down = 5,//�_�E����
	};
	enum class Enemy_State {
		Normal,//�ʏ펞�X�V
		Step,//�X�e�b�v���J�n����
		Track,//�ǐՒ�
	};
public:
	//�J�v�Z������͗�A�L�����N�^�[�̑̌^�ɉ����Đݒ��ύX���鎖
	BaseEnemy(IWorld* world, const std::string& name, const Vector3& position,int playerNumber, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));
	void hitOther(const Vector3& velocity);

	//�I��ԍ����擾����
	int getPlayerNumber()const { return playerNumber_; }
private:
	// ���b�Z�[�W����
	virtual void onMessage(EventMessage message, void* param) override;
	// �X�V
	virtual void onUpdate(float deltaTime)override;
	// �`��
	virtual void onDraw() const override;
	// �Փ˂���
	virtual void onCollide(Actor& other) override;
	
	// �Փ˂�����
	virtual void onCollideResult() override;

	Vector3 mathBound(Actor& other);

	// �t�B�[���h�Ƃ̏Փ˔���(����Ɠ��������ꍇ��true��Ԃ�)
	virtual bool field(Vector3& result = Vector3()) override;

	//�t�B�[���h�Ƃ̓����蔻����s���A�ʒu��␳����
	void correctPosition();

private:
	//�X�e�b�v�ʒm���̏���
	virtual void JustStep()override;

	//���G
	void searchTarget(float deltaTime);
	//�p�[�g�i�[�̍X�V
	void bulletUpdate(float deltaTime);

	//�w��ʒu�ւ̈ړ�
	void addVelocity_NextPosition(float deltaTime);

	//�A�j���[�V�����̕ύX
	void changeAnimation(Enemy_Animation animID);
	//��Ԃ̍X�V
	bool change_State(Enemy_State state);
	//��ԕύX�ƃA�j���[�V�����ύX�𓯎��ɍs��
	bool change_State_and_Anim(Enemy_State state, Enemy_Animation animID);

	void to_Normal();
	void to_Step();
	void to_Track();

	void updateNormal(float deltaTime);
	void updateStep(float deltaTime);
	void updateTrack(float deltaTime);
private:
	float stepTime_{ 0.0f };
	Vector3 velocity_;
	//�͂����ꎞ�̃x�N�g��
	Vector3 bound_{ Vector3::Zero };
	//���Ɍ������Ώ�
	Vector3 nextPosition_;
	//�{��
	std::shared_ptr<EnemyBullet> bullet_;
	//���̈ʒu�A�j���Œ��ɏ���������
	Vector3* bulletPosition_{};
	//���̉�]�A�j���Œ��ɏ���������
	Matrix* bulletRotation_{};
	//���̈ړ��x�N�g��
	Vector3 bulletVelocity_;
	//��]��
	float turnPower_;

	ActorPtr target_;

	//�I��ԍ�
	int playerNumber_;

	Enemy_State state_{ Enemy_State::Normal };
};