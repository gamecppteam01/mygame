#pragma once
#include"Enemy.h"
#include"../Body/BoundingCapsule.h"

class EnemyBullet;

class BaseEnemy :public Enemy {
public:
	//�A�j���[�V�����̃L�[�ԍ�(�e�l�́A���ۂ�mv1�ɐݒ肳��Ă���A�j���[�V�����Ɗ֘A�t���鎖)
	enum class Enemy_Animation {
		Idle = 0,//�ҋ@��
		Move_Forward = 2,//�O�ړ���
		Step_Left = 8,//���X�e�b�v��
		Attack = 11,//�U����
		KnockBack = 14,//��e��
		Down = 15,//�_�E����
	  Turn = 11,//��]��
	};

public:
	//�J�v�Z������͗�A�L�����N�^�[�̑̌^�ɉ����Đݒ��ύX���鎖
	BaseEnemy(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));
private:
	// ���b�Z�[�W����
	virtual void onMessage(EventMessage message, void* param) override;
	// �X�V
	virtual void onUpdate(float deltaTime)override;
	// �`��
	virtual void onDraw() const override;
	// �Փ˂���
	virtual void onCollide(Actor& other) override;

private:
	//���G
	void searchTarget(float deltaTime);
	//�p�[�g�i�[�̍X�V
	void bulletUpdate(float deltaTime);

	//�A�j���[�V�����̕ύX
	void changeAnimation(Enemy_Animation animID);

private:
	Vector3 velocity_;
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
};