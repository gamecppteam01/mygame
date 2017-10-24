#pragma once

#include "IWorld.h"
#include <functional>
#include"../Actor/ActorManager.h"
#include"../Field/FieldPtr.h"
#include"../Camera/CameraPtr.h"
#include"../Graphic/Light.h"
#include"../Light/LightType.h"
#include"../UI/UIManager.h"
#include"../Judge/StepTimer.h"
#include"../ScoreManager/ScoreManager.h"
#include"../ScoreManager/ScoreMap.h"

// ���[���h�N���X
class World : public IWorld {
public:
	// �R���X�g���N�^
	World();
	//������
	void Initialize();
	//�����̕K�v�ȃN���X�̏�����
	virtual void FindInitialize()override;
	// �X�V
	void update(float deltaTime);
	// �`��
	void draw() const;
	// ���b�Z�[�W����
	void handleMessage(EventMessage message, void* param);
	
	// �t�B�[���h�̒ǉ�
	void addField(const FieldPtr& field);
	//�J�����̒ǉ�
	void addCamera(const CameraPtr& camera);
	void addLight(DirectionalLight light);
	void addLight(SpotLight light);
	void addLight(PointLight light);
	//UI�̒ǉ�
	void addUI(UIPtr ui);
	virtual void addStepTimeListener(const ActorPtr& actor) override;
	// �t�B�[���h�̎擾
	virtual FieldPtr getField() const override;
	virtual CameraPtr getCamera() override;
	virtual StepTimer getStepTimer()const override;
	virtual ScoreManager getScoreManager()const override;
	virtual ScoreManager& getCanChangedScoreManager()override;
	virtual ScoreMap& getCanChangedScoreMap()override;
	// �A�N�^�[�̒ǉ�
	virtual void addActor(ActorGroup group, const ActorPtr& actor) override;
	// �A�N�^�[�̌���
	virtual ActorPtr findActor(const std::string& name) override;
	//�A�N�^�[�̈ꊇ����
	virtual void findActors(const std::string& name,std::list<ActorPtr>& actorList) override;
	// ���b�Z�[�W�̑��M
	virtual void sendMessage(EventMessage message, void* param = nullptr)  override;
	// �C�x���g���X�i�[�̒ǉ�
	void addEventMessageListener(std::function<void(EventMessage, void*)> listener);
	void end();
	
	// �R�s�[�֎~
	World(const World& other) = delete;
	World& operator = (const World& other) = delete;
private:
	FieldPtr field_;
	CameraPtr camera_;
	Light  light_;
	ActorManager actors_;
	UIManager uiManager_;
	ScoreManager scoreManager_;
	//�X�R�A�{�����o�}�b�v
	ScoreMap scoreMap_;
	//�X�e�b�v�ʒm
	StepTimer stepTimer_;
	// �C�x���g���X�i�[
	std::function<void(EventMessage, void*)> listener_;
};
