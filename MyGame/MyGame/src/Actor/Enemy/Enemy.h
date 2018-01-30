#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationDX.h"


class Enemy :public Actor {
public:
	explicit Enemy(const std::string& name);
	Enemy(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body);
	virtual ~Enemy(){}
private:
	// ���b�Z�[�W����
	virtual void onMessage(EventMessage message, void* param);
	// �X�V
	virtual void onUpdate(float deltaTime);
	// �`��
	virtual void onDraw() const;
	// �Փ˂���
	virtual void onCollide(Actor& other);

protected:
	//�~�ς���ړ��ʂ��i�[����
	Vector3 velocity_;
	//�d��
	float gravity_;
	//3D���f���A�j���[�V����
	AnimationDx animation_;
};
