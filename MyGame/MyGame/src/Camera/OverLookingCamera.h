#pragma once
#include"../Actor/Actor.h"

class OverLookingCamera :public Actor {
public:
	OverLookingCamera(IWorld* world = nullptr, const std::string& name = "Camera", const Vector3& position = Vector3::Zero, const IBodyPtr& body = std::make_shared<DummyBody>());

	void setTarget(ActorPtr& target);

	//�^�[�Q�b�g���ݒ肳��Ă���ꍇ�A�����ʒu���Z�b�g����
	void setFirstPos();


	void ZoomIn(int pointKey,int easeKey);
	void ZoomOut();

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

	void zoom_default(float deltaTime);
	void zoom_in(float deltaTime);
	void zoom_out(float deltaTime);

private:
	//�Ώۂ����둤�ɗ���鋗��(z���ړ�)
	float backwardLength_{ 100.0f };
	//�Ώۂ���㑤�ɗ���鋗��(y���ړ�)
	float upLength_{ 100.0f };
	Vector3 targetVector_{ Vector3{0.0f,-30.0f,-20.0f} };

	int zoomType_{ 0 };
	float timeCount_{ 0.0f };

	std::vector<std::function<void(float)>> zoomFuncList_;

	std::vector<std::function<void()>> easeFuncList_;


	int pointKey_{ 0 };
	int easeKey_{ 0 };

	ActorPtr target_;

	Vector3 prevPosition_;
	Vector3 targetTranslate_;
};