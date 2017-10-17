#pragma once
#include"../Actor.h"

enum class EventMessage;

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

private:
	bool is_Scorp_Angle() const;

private:
	//����p
	float m_Scope_angle;
	//����]�p
	float yaw;
	//�p�x
	float m_Angle;
	//���Z�̒l
	float m_Add;
};