#pragma once
#include"../Actor/Actor.h"

class OverLookingCamera :public Actor {
public:
	OverLookingCamera(IWorld* world = nullptr, const std::string& name = "Camera", const Vector3& position = Vector3::Zero, const IBodyPtr& body = std::make_shared<DummyBody>());

	void setTarget(ActorPtr& target);

	//�^�[�Q�b�g���ݒ肳��Ă���ꍇ�A�����ʒu���Z�b�g����
	void setFirstPos();
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
	void cameraMove(float deltaTime);
private:
	ActorPtr target_;

	Vector3 prevPosition_;
	Vector3 targetTranslate_;
};