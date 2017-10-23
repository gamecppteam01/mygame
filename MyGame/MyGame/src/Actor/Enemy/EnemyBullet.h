#pragma once
#include"Enemy.h"
#include"../Body/BoundingCapsule.h"

class BaseEnemy;
class EnemyBullet :public Enemy {
	friend class BaseEnemy;
public:
	//�A�j���[�V�����̃L�[�ԍ�(�e�l�́A���ۂ�mv1�ɐݒ肳��Ă���A�j���[�V�����Ɗ֘A�t���鎖)
	enum class EnemyBullet_Animation {
		Idle = 0,//�ҋ@��
		Move_Forward = 2,//�O�ړ���
		Step_Left = 8,//���X�e�b�v��
		Turn = 11,//��]��
		KnockBack = 14,//��e��
		Down = 15,//�_�E����
	    //Jump = 17,//�W�����v��
	};
public:
	//�J�v�Z������͗�A�L�����N�^�[�̑̌^�ɉ����Đݒ��ύX���鎖
	EnemyBullet(IWorld* world, const std::string& name, const Vector3& position, BaseEnemy* enemy, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));
private:
	// ���b�Z�[�W����
	virtual void onMessage(EventMessage message, void* param) override;
	// �X�V
	virtual void onUpdate(float deltaTime)override;
	// �`��
	virtual void onDraw() const override;
	// �Փ˂���
	virtual void onCollide(Actor& other) override;

	//�x�[�X�p
private:
	Vector3* getPositionPtr();
	Matrix* getRotationPtr();
	//�A�j���[�V�����̕ύX
	void changeAnimation(EnemyBullet_Animation animID);

private:
	//�A�j���[�V����
	AnimationDx animation_;
	BaseEnemy* enemy_;
};