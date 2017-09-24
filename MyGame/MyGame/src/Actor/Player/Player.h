#pragma once
#include"../Actor.h"
#include"../../Graphic/Animation.h"
#include<map>
#include<functional>
enum class EventMessage;

class Player :public Actor {
public:
	enum class Player_State {
		Idle,//�ҋ@
		Move,//�ړ�
		//Jump,//�W�����v
		Step,//�Z
		Attack,//�U��
		KnockBack,//��e
		Down,//�_�E����
		Turn,//��]
		State_Count//�X�e�[�g���𐔂��邽�߂̗񋓒l(Count����ԂƂ��ė��p���Ȃ�����)
	};
	//�A�j���[�V�����̃L�[�ԍ�(�e�l�́A���ۂ�mv1�ɐݒ肳��Ă���A�j���[�V�����Ɗ֘A�t���鎖)
	enum class Player_Animation {
		Idle=0,//�ҋ@��
		Move_Forward=2,//�O�ړ���
		Step_Left=8,//���X�e�b�v��
		Attack=11,//�U����
		KnockBack=14,//��e��
		Down=15,//�_�E����
		//Jump = 17,//�W�����v��
		Turn=11,//��]��
		Animation_Count//���p�A�j���[�V�������𐔂��邽�߂̗񋓒l(Count����ԂƂ��ė��p���Ȃ�����)
	};

public:
	Player(IWorld* world,const std::string& name,const Vector3& position);


private:
	virtual void initialize()override;
	// ���b�Z�[�W����
	virtual void onMessage(EventMessage message, void* param);
	// �X�V
	virtual void onUpdate(float deltaTime);
	// �`��
	virtual void onDraw() const;
	// �Փ˂���
	virtual void onCollide(Actor& other);

//�v���C���[�̈ړ��֌W
private:
	//���͂ɂ��ړ�(�ړ��ɑΉ������L�[�����͂���Ă����ꍇ��true��Ԃ�)
	bool inputTransformUpdate(float deltaTime);
	//�d�͋y�уW�����v���X�V����
	void gravityUpdate(float deltaTime);
	//�t�B�[���h�Ƃ̓����蔻����s���A�ʒu��␳����
	void correctPosition();

//��Ԋ֌W
private:
	//��ԕύX�ƃA�j���[�V�����ύX�𓯎��ɍs��
	bool change_State_and_Anim(Player_State state, Player_Animation animID, float animSpeed = 1.0f);

	//��Ԃ̍X�V
	bool change_State(Player_State state);

	//�ҋ@���X�V
	void idle_Update(float deltaTime);
	//�ړ����X�V
	void move_Update(float deltaTime);
	//�W�����v���X�V
	//void jump_Update(float deltaTime);
	//�Z���X�V
	void step_Update(float deltaTime);
	//�U�����X�V
	void attack_Update(float deltaTime);
	//��e���X�V
	void knockback_Update(float deltaTime);
	//��e���X�V
	void down_Update(float deltaTime);
	//��]���X�V
	void turn_Update(float deltaTime);

	//�ҋ@��Ԃւ̈ڍs����
	void to_IdleMode();
	//�ړ���Ԃւ̈ڍs����
	void to_MoveMode();
	//void to_JumpMode();
	//�Z��Ԃւ̈ڍs����
	void to_StepMode();
	//�U����Ԃւ̈ڍs����
	void to_AttackMode();
	//��e��Ԃւ̈ڍs����
	void to_KnockBackMode();
	//��e��Ԃւ̈ڍs����
	void to_DownMode();
	//��]��Ԃւ̈ڍs����
	void to_TurnMode();
private:
	void changeAnimation(Player_Animation animID, float animSpeed = 1.0f);

private:
	//�ړ��x�N�g��
	Vector3 velocity_;
	//������x�N�g��
	float upVelocity_;
	//�d��
	float gravity_;
	//�v���C���[�̃A�j���[�V����
	Animation animation_;

	Player_State state_;

	std::map<Player_State, std::function<void(float)>> playerUpdateFunc_;
	std::map<Player_State, std::function<void()>> playerToNextModeFunc_;

	//��]��
	float turnPower_;

private:
	Vector3 defaultPosition_;
};