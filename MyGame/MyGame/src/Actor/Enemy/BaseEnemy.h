#pragma once
#include"Enemy.h"
#include"../Body/BoundingCapsule.h"
#include"../../Method/MethodTimer.h"
#include"../../Define.h"
class EnemyBullet;

class BaseEnemy :public Enemy {
	friend class EnemyBullet;
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
		Attack,//�U��
		Down,//�]�|

	};
public:
	//�J�v�Z������͗�A�L�����N�^�[�̑̌^�ɉ����Đݒ��ύX���鎖
	BaseEnemy(IWorld* world, const std::string& name, const Vector3& position,int playerNumber, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));
	virtual ~BaseEnemy(){}
	void hitOther(const Vector3& velocity);

	//�I��ԍ����擾����
	int getPlayerNumber()const { return playerNumber_; }

	//
	Enemy_State getEnemyState()const { return state_; }

	//�]�|�J�E���g�̃Z�b�g
	virtual void setCountDown();

	virtual Vector3& position()override {
		return centerPosition_;
	}
protected:
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

	//��ԋ߂��L�����N�^�[���󂯎��
	ActorPtr getNearestActor();
	

	//topTime:�ő�l�ɂȂ鎞��
	float mathSpeed(float current,float maxSpeed, float maxTime, float topTime);

	float mathSpeedUnderPower(float current, float maxSpeed, float maxTime, float topTime);
protected:
	//�X�e�b�v�ʒm���̏���
	virtual void JustStep()override;
	//�e����ݒ�
	void setBoundPower(float powerRate);
	//���G
	void searchTarget(float deltaTime);
	//�p�[�g�i�[�̍X�V
	void bulletUpdate(float deltaTime);

	//�w��ʒu�ւ̈ړ�
	void addVelocity_NextPosition(float deltaTime);

	//�A�j���[�V�����̕ύX
	void changeAnimation(Enemy_Animation animID,float animFrame=0.0f,float animSpeed=1.0f,bool isLoop=true);
	//��Ԃ̍X�V
	bool change_State(Enemy_State state,BaseEnemy::Enemy_Animation anim);
	//��ԕύX�ƃA�j���[�V�����ύX�𓯎��ɍs��
	bool change_State_and_Anim(Enemy_State state, Enemy_Animation animID);

	virtual void to_Normal();
	virtual void to_Step(Enemy_Animation anim);
	virtual void to_Track();
	virtual void to_Attack(Enemy_Animation anim);
	virtual void to_Down();

	virtual void updateNormal(float deltaTime);
	virtual void updateStep(float deltaTime);
	virtual void updateTrack(float deltaTime);
	virtual void updateAttack(float deltaTime);
	virtual void updateDown(float deltaTime);

	//�X�e�b�v�\��
	bool isCanStep()const;
protected:
	float stepTime_{ 0.0f };
	Vector3 velocity_;
	//�͂����ꎞ�̃x�N�g��
	Vector3 bound_{ Vector3::Zero };
	//���Ɍ������Ώ�
	Vector3 nextPosition_;
	//2�L�����̒��S
	Vector3 centerPosition_{ Vector3::Zero };
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

	//�C�[�W���O�^�C�}�[
	float speedEaseTimer_{ 0.0f };

	ActorPtr target_;

	//�I��ԍ�
	int playerNumber_;

	//�_�E������܂ł̃J�E���g
	int downCount_;
	//�_�E���J�E���g�̕ύX�^�C�}�[
	MethodTimer downTimer_;
	//�U���Ώۂ���̏��O�ݒ�����^�C�}�[
	MethodTimer nonTargetResetTimer_;
	//�_�E�����Ă��鎞��
	float downTime_;

	//�U���Ώ�
	std::weak_ptr<Actor> attackTarget_;

	Enemy_State state_{ Enemy_State::Normal };

	//�O�ɓ�����������̔ԍ�
	int prevHitActorNumber_{ 0 };

	//���q�^�C�}�[
	int rhythmTimeCount_{ 0 };

	float boundPower_{ 15.0f };

protected:
	//�U������͈�
	const float attackDistance{ 30.0f };
	//�|�W�V�����ǐՎ��̈ړ��̐���
	const float movePower{ 0.7f };
	//�_�E�����鎞��
	const float downTime{ 3.0f };
	//�j�Ə��̋���
	const Vector3 bulletDistance{ 0.0f,0.0f,6.0f };

	const float attackPower{ 1.0f };
	const std::vector<std::pair<Enemy_Animation, int>> stepAnim{
		{Enemy_Animation::KnockBack,SCORE_QUARTER },//�N�H�[�^�[
		{Enemy_Animation::Idle,0},//�n�[�t
		{Enemy_Animation::Step_Left,SCORE_TURN },//�^�[��
		{Enemy_Animation::Idle,0		  }//�X�s��
	};

};