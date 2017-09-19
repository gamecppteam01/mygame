#pragma once
#include"../Actor.h"
#include"../../Graphic/Animation.h"

enum class EventMessage;

class Player :public Actor {
public:
	Player(IWorld* world,const std::string& name,const Vector3& position, const IBodyPtr& body);


private:
	// ���b�Z�[�W����
	virtual void onMessage(EventMessage message, void* param);
	// �X�V
	virtual void onUpdate(float deltaTime);
	// �`��
	virtual void onDraw() const;
	// �Փ˂���
	virtual void onCollide(Actor& other);

private:
	//virtual bool field() override;
private:
	//�~�ς���ړ��ʂ��i�[����
	Vector3 velocity_;

	float gravity_;

	Animation animation_;
};