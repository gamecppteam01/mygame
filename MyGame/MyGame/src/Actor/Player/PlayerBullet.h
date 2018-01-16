#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationDx.h"

class Player;

//�v���C���[�̍U��(��)
class PlayerBullet:public Actor {
	friend class Player;
	friend class TutorialPlayer;
public:
	//�A�j���[�V�����̃L�[�ԍ�(�e�l�́A���ۂ�mv1�ɐݒ肳��Ă���A�j���[�V�����Ɗ֘A�t���鎖)
	enum class PlayerBullet_Animation {
		Move_Forward = 0,//�O�ړ���
		Idle = 1,//�ҋ@��
		Shoot = 1,//���X�e�b�v��
		Quarter=2,
		ShootEnd=9,
		Step_Left=8,
		Turn = 3,//��]��
		Half=4,
		Attack = 12,//�U����
		KnockBack = 0,//��e��
		Down = 5,//�_�E����
		Reversal=6,//�N���オ�莞
		Stumble=7,
		//Jump = 17,//�W�����v��
	};

public:
	PlayerBullet(IWorld* world, const Vector3& position, Player* player);
	//������
	virtual void initialize() override;

	void hitEnemy(const std::string& hitName, const Vector3& velocity);
	//�v���C���[���擾����
	const Player* getPlayer()const;
	Player* getCCPlayer();

	virtual Vector3& position()override;

	//��~���̃X�e�b�v�A�j���[�V�����X�V����
	virtual void stepAnimUpdate(float deltaTime)override;

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
	void changeAnimation(PlayerBullet_Animation animID, float animFrame = 0.0f, float animeSpeed = 1.0f, bool isLoop = true,float blend=1.0f);
	Player* player_;
private:

	//�v���C���[�̃A�j���[�V����
	AnimationDx animation_;

};