#pragma once

#include "../Actor/ActorPtr.h"
#include"../Field/FieldPtr.h"
#include"../Camera/CameraPtr.h"
#include"../UI/UIPtr.h"
#include"../Game/ID.h"
#include <string>
#include<list>
#include<functional>

enum class ActorGroup;
class ScoreManager;
class ScoreMap;
class TempoManager;
class FieldGrid;
// ���[���h���ۃC���^�[�t�F�[�X
class IWorld {
public:
	// ���z�f�X�g���N�^
	virtual ~IWorld() {}
	//�������K�v�ȃN���X�̏�����
	virtual void FindInitialize() = 0;
	// �A�N�^�[�̒ǉ�
	virtual void addActor(ActorGroup group, const ActorPtr& actor) = 0;
	// �A�N�^�[�̌���
	virtual ActorPtr findActor(const std::string& name) = 0;
	// �A�N�^�[�̕�������
	virtual void findActors(const std::string& name, std::list<ActorPtr>& actorList) = 0;
	// �A�N�^�[�̕�������
	virtual void findActors(const std::string& name, std::list<std::weak_ptr<Actor>>& actorList) = 0;
	// ���b�Z�[�W�̑��M
	virtual void sendMessage(EventMessage message, void* param = nullptr) = 0;
	//�`��֐��I����ɕ`����Z�b�g����֐�
	virtual void setLateDraw(std::function<void()> draw, bool isBeforeUI=true) = 0;

	virtual void addUI(UIPtr ui) = 0;

	// �t�B�[���h�̎擾
	virtual FieldPtr getField() const = 0;
	virtual CameraPtr getCamera() = 0;
	virtual ScoreManager getScoreManager()const = 0;
	virtual ScoreManager& getCanChangedScoreManager() = 0;
	virtual ScoreMap& getCanChangedScoreMap() = 0;
	virtual void addStepTimeListener(const ActorPtr& actor) = 0;
	virtual TempoManager& getCanChangedTempoManager() = 0;
	virtual TempoManager getTempoManager()const = 0;
	virtual UIPtr findUI(const std::string& name) = 0;
	virtual FieldGrid& getGrid() = 0;
};
