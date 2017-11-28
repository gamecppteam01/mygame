#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationDx.h"

class Player;

//�v���C���[�̍U��(��)
class PlayerBullet:public Actor {
	friend class Player;
public:
	//�A�j���[�V�����̃L�[�ԍ�(�e�l�́A���ۂ�mv1�ɐݒ肳��Ă���A�j���[�V�����Ɗ֘A�t���鎖)
	enum class PlayerBullet_Animation {
		Move_Forward = 0,//�O�ړ���
		Idle = 1,//�ҋ@��
		Shoot = 1,//���X�e�b�v��
		ShootEnd=9,
		Step_Left=10,
		Turn = 11,//��]��
		Attack = 12,//�U����
		KnockBack = 14,//��e��
		Down = 15,//�_�E����
		//Jump = 17,//�W�����v��
	};

public:
	PlayerBullet(IWorld* world, const Vector3& position, Player* player);
	//������
	virtual void initialize() override;

	void hitEnemy(const std::string& hitName, const Vector3& velocity);
	//�v���C���[���擾����
	const Player* getPlayer()const;

	virtual Vector3& position()override;
private:
	// ���b�Z�[�W����
	virtual void onMessage(EventMessage message, void* param);
	// �X�V����
	virtual void onUpdate(float deltaTime);
	// �`�揈��
	virtual void onDraw() const;
	// �Փ˂������̏���
	virtual void onCollide(Actor& other);

//�v���C���[�p
private:
	Vector3* getPositionPtr();
	Matrix* getRotationPtr();
	//�A�j���[�V�����̕ύX
	void changeAnimation(PlayerBullet_Animation animID, float animFrame = 0.0f, float animeSpeed = 1.0f, bool isLoop = true);
	Player* player_;
private:

	//�v���C���[�̃A�j���[�V����
	AnimationDx animation_;

};