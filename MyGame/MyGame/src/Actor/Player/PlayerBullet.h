#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationDx.h"

//�v���C���[�̍U��(��)
class PlayerBullet:public Actor {
	friend class Player;
public:
	//�A�j���[�V�����̃L�[�ԍ�(�e�l�́A���ۂ�mv1�ɐݒ肳��Ă���A�j���[�V�����Ɗ֘A�t���鎖)
	enum class PlayerBullet_Animation {
		Idle = 0,//�ҋ@��
		Move_Forward = 2,//�O�ړ���
		Step_Left = 8,//���X�e�b�v��
		Attack = 11,//�U����
		KnockBack = 14,//��e��
		Down = 15,//�_�E����
		//Jump = 17,//�W�����v��
		Turn = 11,//��]��
		Animation_Count//���p�A�j���[�V�������𐔂��邽�߂̗񋓒l(Count����ԂƂ��ė��p���Ȃ�����)
	};

public:
	PlayerBullet(IWorld* world, const Vector3& position);
	//������
	virtual void initialize() override;

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
	void changeAnimation(PlayerBullet_Animation animID, float animSpeed = 1.0f);

private:

	//�v���C���[�̃A�j���[�V����
	AnimationDx animation_;

};