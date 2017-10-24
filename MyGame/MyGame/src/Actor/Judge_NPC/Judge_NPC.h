#pragma once
#include"../Actor.h"

enum class Judge_State {
	Search,
	Regard,
};

class Judge_NPC : public Actor {
public:
	//�R���X�g���N�^
	Judge_NPC(IWorld* world, const std::string& name, const Vector3& position,float scope_angle = 45.0f);
	//������
	virtual void initialize()override;
	// ���b�Z�[�W����
	virtual void onMessage(EventMessage message, void* param);
	// �X�V
	virtual void onUpdate(float deltaTime);
	// �`��
	virtual void onDraw() const;
	// �Փ˂���
	virtual void onCollide(Actor& other);

	float getAngle()const;
private:
	//��ԍX�V
	void StateUpdate(float deltaTime);
	//�T���X�V
	void SearchUpdate(float deltaTime);
	//�����X�V
	void RegardUpdate(float deltaTime);
	//����p���ɂ��邩�H
	bool is_Scorp_Angle(ActorPtr& target) const;
	//��苗�����ɂ��邩�H
	bool is_In_Distans(ActorPtr& target) const;

private:
	//���
	Judge_State m_State;
	//����p
	float m_Scope_angle;
	//����]�p
	float yaw;
	//�p�x
	float m_Angle;
	//1�J�E���g
	float m_Count;
	//�^�C�}�[
	float m_Timer;
};