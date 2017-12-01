#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationDx.h"
#include<map>
#include<functional>
#include<array>
#include"../../Method/MethodTimer.h"
#include"Step_Type.h"
#include"GyroRotateChecker.h"
#include"../../Define.h"
#include"../../Sound/MusicScoreManager.h"
class PlayerBullet;

class Player :public Actor {
public:

	enum class Player_State {
		Idle,//�ҋ@
		Move,//�ړ�
		//Jump,//�W�����v
		Step,//�Z
		Step_Success,//�Z����
		Stumble,//��낯���[�h
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
		Move_Forward = 0,//�O�ړ���
		Idle = 1,//�ҋ@��
		Step_Left = 8,//���X�e�b�v��
		Quarter=2,
		Attack = 11,//�U����
		Shoot = 1,//���ˎ�
		ShootEnd = 13,//���ˏI��
		KnockBack = 14,//��e��
		Down = 0,//�_�E����
		Turn = 3,//��]��
		Half = 4,
	};

public:
	Player(IWorld* world,const std::string& name,const Vector3& position,int playerNumber);

//�O�����J�֐�
public:
	void addVelocity(const Vector3& velocity);
	void hitEnemy(const std::string& hitName, const Vector3& velocity);
	//�I��ԍ����擾����
	int getPlayerNumber()const { return playerNumber_; }
	//��낯�������擾����
	Vector2 getStumbleDirection()const { return stumbleDirection_; }
	//���݂̏�Ԃ��擾����
	Player_State getState()const { return state_; }
	//���݂̃X�e�b�v�̎�ނ�Ԃ�(1=�N�H�[�^�[,2=�n�[�t,3=�^�[��,4=�X�s��)
	int getStep()const { return nextStep_; }

	virtual Vector3& position()override { return centerPosition_; }
	Vector3 getCenterPos()const { return centerPosition_; }
	//�X�R�A�{�����擾����
	float getPlayerScoreRate()const;
	//�ėp�̃^�C�}�[��n��
	float getTimer()const { return timeCount_; }
private:
	void createBullet();
	virtual void initialize()override;
	virtual void onPause()override;
	virtual void onRestart()override;
	// ���b�Z�[�W����
	virtual void onMessage(EventMessage message, void* param);
	// �X�V
	virtual void onUpdate(float deltaTime);
	// �`��
	virtual void onDraw() const;
	// �Փ˂���
	virtual void onCollide(Actor& other);

	virtual void onCollideResult()override;

//�ʒm�����֘A
private:
	//�X�e�b�v�ʒm���̏���
	virtual void JustStep()override;
	//�G�t�F�N�g�����ʒm�̏���
	virtual void CreateJustEffect()override;
	
	// �t�B�[���h�Ƃ̏Փ˔���(����Ɠ��������ꍇ��true��Ԃ�)
	virtual bool field(Vector3& result = Vector3()) override;

//�v���C���[�̈ړ��֌W
private:
	//�d�͋y�уW�����v���X�V����
	void gravityUpdate(float deltaTime);
	//�t�B�[���h�Ƃ̓����蔻����s���A�ʒu��␳����
	void correctPosition();

//��Ԋ֌W
private:
	//��ԕύX�ƃA�j���[�V�����ύX�𓯎��ɍs��
	bool change_State_and_Anim(Player_State state, Player_Animation animID, float animFrame = 0.0f, float animSpeed = 1.0f, bool isLoop = true);

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
	//�Z�������X�V
	void stepSuccess_Update(float deltaTime);
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
	//��낯���X�V
	void stumble_Update(float deltaTime);

	//�ҋ@��Ԃւ̈ڍs����
	void to_IdleMode();
	//�ړ���Ԃւ̈ڍs����
	void to_MoveMode();
	//void to_JumpMode();
	//�Z��Ԃւ̈ڍs����
	void to_StepMode();
	//�Z������Ԃւ̈ڍs����
	void to_StepSuccessMode();
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
	//��낯��Ԃւ̈ڍs����
	void to_StumbleMode();

	//�ҋ@��Ԃ̏I������
	void end_IdleMode();
	//�ړ���Ԃ̏I������
	void end_MoveMode();
	//void to_JumpMode();
	//�Z��Ԃ̏I������
	void end_StepMode();
	//�X�e�b�v�����̏I������
	void end_StepSuccessMode();
	//�U����Ԃ̏I������
	void end_AttackMode();
	//���ˏ�Ԃ̏I������
	void end_ShootMode();
	//���ˏI����Ԃ̏I������
	void end_ShootEndMode();
	//��e��Ԃ̏I������
	void end_KnockBackMode();
	//��e��Ԃ̏I������
	void end_DownMode();
	//��]��Ԃ̏I������
	void end_TurnMode();
	//��낯�̏I������
	void end_StumbleMode();

private:
		//�U���X�e�b�v
		void stepAttack(float deltaTime);

private:
	//�A�j���[�V�����̕ύX
	void changeAnimation(Player_Animation animID, float animFrame = 0.0f,float animeSpeed=1.0f,bool isLoop=true);

private:
	//�X�e�b�v�ɕύX�����Ԃ�
	bool isChangeStep() const;

	//��낯�������\�ȏ�Ԃ�
	bool isCanStamble()const;
	
	//�U����Ԃ��ǂ���
	bool isAttack();
	//�p���`�F�b�N�����邩�ǂ���
	bool isRequiredCheckPosture()const;
//�e(��)�֌W
private:
	//�����v���C���[�ɒǏ]���邩�ǂ���
	bool isCanTracking() const;
	void bulletUpdate(float deltaTime);
	//�~�G�t�F�N�g�𐶐�����
	void createCircleEffect();
private:
	//�X�e�B�b�N�̃x�N�g�����E����W�n�ɕϊ�
	Vector2 getSticktoMove();

	Vector2 mathStumbleDirection(const Vector2& stumbleDirection);

	bool isJustTiming()const;
private:
	//���������X�e�b�v(0=�񐬗�,1=�N�H�[�^�[,2=�n�[�t,3=�^�[��,4����])
	int successStep_;
	//���̃X�e�b�v
	int nextStep_;
	//�I��ԍ�
	int playerNumber_;
	//�X�e�b�v�̎����𑪂�
	int stepCount_{ 0 };

	float shootAngle_;
	//�ėp�^�C�}�[
	float timeCount_;
	//�_�E�����鎞��
	float downTime_{ 7.0f };
	//2�̂̒��S
	Vector3 centerPosition_{ Vector3::Zero };
	//��낯�֘A
	//�q�b�g��������
	Vector2 stumbleDirection_{ Vector2::Zero };
	float stumbleRegistTimer_{ 0.f };
	//�j�֘A
	//�ړ��x�N�g��
	Vector3 velocity_;
	//���˕Ԃ�x�N�g��
	Vector3 bound_;
	//������x�N�g��
	float upVelocity_;
	//�d��
	float gravity_;
	//�v���C���[�̃A�j���[�V����
	AnimationDx animation_;
	//���
	Player_State state_;
	//�G�t�F�N�g�����N���X���Ăяo��
	MethodTimer effectCreator_;
	//�X�R�A���Z�̐���
	bool isJustStep_{ false };
	//�U���Ώ�
	ActorPtr attackTarget_;

	//��낯����񕜂���܂ł̎���
	float stumbleResurrectTime_{ 0.5f };


	//���֘A
	//���{��
	std::shared_ptr<PlayerBullet> bullet_{};
	//���̈ʒu�A�j���Œ��ɏ���������
	Vector3* bulletPosition_{};
	//���̉�]�A�j���Œ��ɏ���������
	Matrix* bulletRotation_{};
	//���̈ړ��x�N�g��
	Vector3 bulletVelocity_;
	//��]��
	float turnPower_;
	//�G�t�F�N�g�̃T�C�Y
	std::array<float,3> effectSize_{ 0.0f,0.0f,0.0f };
	//�W���C���̉�]�`�F�b�N�N���X
	GyroRotateChecker gyroCheck_;
	//���ʊǗ��N���X
	MusicScoreManager musicScore_;

	std::map<Player_State, std::function<void(float)>> playerUpdateFunc_;
	std::map<Player_State, std::function<void()>> playerEndModeFunc_;
	std::map<Player_State, std::function<void()>> playerToNextModeFunc_;

	std::list<SE_ID> restartSEList_;

private:
	const Vector3 defaultPosition_;

	const std::map<int, std::pair<Player_Animation, int>> stepAnimScoreList_{
		{ 1,{ Player_Animation::Quarter,SCORE_QUARTER } },
		{ 2,{ Player_Animation::Half,0 } },
		{ 3,{ Player_Animation::Turn,SCORE_TURN } },
		{ 4,{ Player_Animation::Shoot,0 } },
	};


};