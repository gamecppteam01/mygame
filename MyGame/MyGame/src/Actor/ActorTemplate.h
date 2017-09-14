#pragma once
#include"Actor.h"

enum class EventMessage;

class ActorTemplate :public Actor {
public:
	//Actor�ɕK�v�Ȉ�����Ⴄ
	ActorTemplate(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body);

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
	//�K�v�ɉ����Ĉ�����ǉ�

};