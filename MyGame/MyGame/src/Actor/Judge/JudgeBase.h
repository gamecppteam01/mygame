#pragma once
#include"../Actor.h"

class JudgeBase : public Actor {
public:
	//�R���X�g���N�^
	JudgeBase(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body);
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
	virtual bool Judgement(ActorPtr& target) = 0;

protected:
	//����p���ɂ��邩�H
	bool is_Scorp_Angle(ActorPtr& target,float angle = 45.0f) const;
	//��苗�����ɂ��邩�H
	bool is_In_Distans(ActorPtr& target,float distance = 50.0f) const;
};
