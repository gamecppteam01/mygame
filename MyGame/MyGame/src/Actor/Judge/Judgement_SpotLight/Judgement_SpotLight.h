#pragma once
#include"../JudgeBase.h"

class Judgement_SpotLight : public JudgeBase {
public:
	//�R���X�g���N�^
	Judgement_SpotLight(IWorld* world, const std::string& name, const Vector3& position);
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

private:
	float m_Distance;
};