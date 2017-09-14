#pragma once

#include "Actor.h"
#include"ActorPtr.h"
#include <map>

enum class ActorGroup;
enum class ShapeType;
enum class EventMessage;

class ActorManager {
public:
	// �R���X�g���N�^
	ActorManager();
	// ������
	void initialize();
	// �X�V
	void update(float deltaTime);
	// �`��
	void draw() const;
	// �A�N�^�[�̒ǉ�
	void addActor(ActorGroup group, const ActorPtr& actor);
	// �A�N�^�[�̌���
	ActorPtr findActor(const std::string& name);
	// ���b�Z�[�W����
	void handleMessage(EventMessage message, void* param);
	// �R�s�[�֎~
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator = (const ActorManager& other) = delete;
private:
	// �Փ˔���
	void collide();
private:
	// ���[�g�m�[�h
	Actor root_;
	// �A�N�^�[�O���[�v
	std::map<ActorGroup, ActorPtr> actors_;
};
