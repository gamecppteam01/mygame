#pragma once
#include"../JudgeBase.h"
#include"../../../Graphic/AnimationDx.h"

enum class Judge_State {
	Search,
	Regard,
};

class Judge_NPC : public JudgeBase {
public:
	//�R���X�g���N�^
	Judge_NPC(IWorld* world, const Vector3& position,const Matrix& rotation);
	//������
	virtual void initialize()override;
	// ���b�Z�[�W����
	virtual void onMessage(EventMessage message, void* param) override;
	// �X�V
	virtual void onUpdate(float deltaTime) override;
	// �`��
	virtual void onDraw() const override;
	// �Փ˂���
	virtual void onCollide(Actor& other) override;
	//����
	virtual bool Judgement(ActorPtr& target) override;
	virtual bool Judgement(const Vector3& target) override;
	//�p�x�̎擾
	float getAngle()const;
private:
	//��ԍX�V
	void StateUpdate(float deltaTime);
	//�T���X�V
	void SearchUpdate(float deltaTime);
	//�����X�V
	void RegardUpdate(float deltaTime);

private:
	//���
	Judge_State m_State;
	//����]�p
	float yaw;
	//�p�x
	float m_Angle;
	//1�J�E���g
	float m_Count;
	//�^�C�}�[
	float m_Timer;

	AnimationDx animation_;
};