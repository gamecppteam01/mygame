#pragma once
#include"Enemy.h"
#include"../Body/BoundingCapsule.h"

class BaseEnemy;
class EnemyBullet :public Enemy {
	friend class BaseEnemy;
public:
	//�A�j���[�V�����̃L�[�ԍ�(�e�l�́A���ۂ�mv1�ɐݒ肳��Ă���A�j���[�V�����Ɗ֘A�t���鎖)
	enum class EnemyBullet_Animation {
		Move_Forward = 0,//�O�ړ���
		Idle = 0,//�ҋ@��
		Spin = 1,//�X�s����
		Quarter = 2,//�N�E�H�[�^�\��
		Turn = 3,//��]��
		Half = 4,//�n�[�t��
		Down = 5,//�_�E����
		WakeUp = 6,//�N���オ�莞
		Stan = 7, //�ӂ����
		KnockBack = 4,//��e��
	};
public:
	//�J�v�Z������͗�A�L�����N�^�[�̑̌^�ɉ����Đݒ��ύX���鎖
	EnemyBullet(IWorld* world, const std::string& name, const Vector3& position, BaseEnemy* enemy,MODEL_ID id, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));

	void hitOther(const Vector3& bound);
private:
	// ���b�Z�[�W����
	virtual void onMessage(EventMessage message, void* param) override;
	// �X�V
	virtual void onUpdate(float deltaTime)override;
	// �`��
	virtual void onDraw() const override;
	// �Փ˂���
	virtual void onCollide(Actor& other) override;

	Vector3 mathBound(Actor & other);

	//��~���̃X�e�b�v�A�j���[�V�����X�V����
	virtual void stepAnimUpdate(float deltaTime)override;

	//�x�[�X�p
private:

	Vector3* getPositionPtr();
	Matrix* getRotationPtr();
	//�A�j���[�V�����̕ύX
	void changeAnimation(EnemyBullet_Animation animID, float animFrame = 0.0f, float animSpeed = 1.0f,bool isLoop  = true);

private:
	//�A�j���[�V����
	AnimationDx animation_;
	BaseEnemy* enemy_;
};