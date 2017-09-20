#pragma once
#include"../Actor/Actor.h"

class LightActor : public Actor {
public:
	LightActor(IWorld* world = nullptr, const std::string& name = "Light", const Vector3& position = Vector3::Zero, const IBodyPtr& body = std::make_shared<DummyBody>());

private:
	// ���b�Z�[�W����
	virtual void onMessage(EventMessage message, void* param);
	// �X�V����
	virtual void onUpdate(float deltaTime);
	// �`�揈��
	virtual void onDraw() const;
	// �Փ˂������̏���
	virtual void onCollide(Actor& other);
};
