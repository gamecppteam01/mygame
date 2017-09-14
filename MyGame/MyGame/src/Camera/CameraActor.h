#pragma once
#include"../Actor/Actor.h"

class CameraActor :public Actor {
public:
	CameraActor(IWorld* world=nullptr, const std::string& name="Camera", const Vector3& position=Vector3::Zero, const IBodyPtr& body = std::make_shared<DummyBody>());

	void setTarget(ActorPtr& target);

private:
	// ���b�Z�[�W����
	virtual void onMessage(EventMessage message, void* param);
	// �X�V����
	virtual void onUpdate(float deltaTime);
	// �`�揈��
	virtual void onDraw() const;
	// �Փ˂������̏���
	virtual void onCollide(Actor& other);

private:
	ActorPtr target_;
};