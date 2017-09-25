#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationDx.h"
#include<map>
#include<functional>
#include<array>

enum class EventMessage;
class PlayerBullet;

class Player :public Actor {
public:
	enum class Player_State {
		Idle,//�ҋ@
		Move,//�ړ�
		//Jump,//�W�����v
		Step,//�Z
		Attack,//�U��
		Shoot,//����
		ShootEnd,//���ˏI��
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
		Attack = 11,//�U����
		Shoot = 12,//���ˎ�
		ShootEnd=13,//���ˏI��
		KnockBack=14,//��e��
		Down=15,//�_�E����
		//Jump = 17,//�W�����v��
		Turn=11,//��]��
	};
	//�X�e�b�v�̎��
	enum class Step_Type {
		Chasse,//�V���b�Z
		Turn,//�^�[��
		Whisk,//�z�C�X�N
		SplitCubanBreak,//�X�v���b�g�L���[�o���u���C�N
		Empty,//��
		Dance_Count//�_���X�̐�
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
	//���ˎ��X�V
	void shoot_Update(float deltaTime);
	//���ˏI�����X�V
	void shootend_Update(float deltaTime);
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
	//���ˏ�Ԃւ̈ڍs����
	void to_ShootMode();
	//���ˏI����Ԃւ̈ڍs����
	void to_ShootEndMode();
	//��e��Ԃւ̈ڍs����
	void to_KnockBackMode();
	//��e��Ԃւ̈ڍs����
	void to_DownMode();
	//��]��Ԃւ̈ڍs����
	void to_TurnMode();
private:
	void changeAnimation(Player_Animation animID, float animSpeed = 1.0f);


//�e(��)�֌W
private:
	//�����v���C���[�ɒǏ]���邩�ǂ���
	bool isCanTracking() const;
	void bulletUpdate(float deltaTime);
private:
	//�j�֘A
	//�ړ��x�N�g��
	Vector3 velocity_;
	//������x�N�g��
	float upVelocity_;
	//�d��
	float gravity_;
	//�v���C���[�̃A�j���[�V����
	AnimationDx animation_;
	//���
	Player_State state_;
	//�X�e�b�v���i�[����
	std::array<Step_Type, 3> stepCombo_;
	//���֘A
	//���{��
	std::shared_ptr<PlayerBullet> bullet_{};
	//���̈ʒu�A�j���Œ��ɏ���������
	Vector3* bulletPosition_{};
	//���̈ړ��x�N�g��
	Vector3 bulletVelocity_;
	//��]��
	float turnPower_;


	std::map<Player_State, std::function<void(float)>> playerUpdateFunc_;
	std::map<Player_State, std::function<void()>> playerToNextModeFunc_;

private:
	Vector3 defaultPosition_;
};