#pragma once

#include "../Actor/ActorPtr.h"
#include"../Field/FieldPtr.h"
#include"../Camera/CameraPtr.h"
#include"../Game/ID.h"
#include <string>
#include<list>

enum class ActorGroup;
class StepTimer;
class ScoreBase;
// ���[���h���ۃC���^�[�t�F�[�X
class IWorld {
public:
	// ���z�f�X�g���N�^
	virtual ~IWorld() {}
	// �A�N�^�[�̒ǉ�
	virtual void addActor(ActorGroup group, const ActorPtr& actor) = 0;
	// �A�N�^�[�̌���
	virtual ActorPtr findActor(const std::string& name) = 0;
	// �A�N�^�[�̕�������
	virtual void findActors(const std::string& name, std::list<ActorPtr>& actorList) = 0;
	// ���b�Z�[�W�̑��M
	virtual void sendMessage(EventMessage message, void* param = nullptr) = 0;
	// �t�B�[���h�̎擾
	virtual FieldPtr getField() const = 0;
	virtual CameraPtr getCamera() = 0;
	virtual StepTimer getStepTimer()const = 0;
	virtual ScoreBase getScoreBase()const = 0;
	virtual ScoreBase& getCanChangedScoreBase() = 0;
	virtual void addStepTimeListener(const ActorPtr& actor) = 0;
};
