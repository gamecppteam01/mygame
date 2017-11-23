#pragma once

#include "IWorld.h"
#include <functional>
#include"../Actor/ActorManager.h"
#include"../Field/FieldPtr.h"
#include"../Camera/CameraPtr.h"
#include"../Graphic/Light.h"
#include"../Light/LightType.h"
#include"../UI/UIManager.h"
#include"../ScoreManager/ScoreManager.h"
#include"../ScoreManager/ScoreMap.h"
#include"../Sound/TempoManager.h"
#include"../Graphic/ShadowMap.h"

// ���[���h�N���X
class World : public IWorld {
public:
	// �R���X�g���N�^
	World();
	~World();
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
	virtual void addUI(UIPtr ui) override;
	UIPtr findUI(const std::string& name);
	virtual void addStepTimeListener(const ActorPtr& actor) override;
	// �t�B�[���h�̎擾
	virtual FieldPtr getField() const override;
	virtual CameraPtr getCamera() override;
	virtual ScoreManager getScoreManager()const override;
	virtual ScoreManager& getCanChangedScoreManager()override;
	virtual ScoreMap& getCanChangedScoreMap()override;
	virtual TempoManager& getCanChangedTempoManager()override;
	virtual TempoManager getTempoManager()const override;
	// �A�N�^�[�̒ǉ�
	virtual void addActor(ActorGroup group, const ActorPtr& actor) override;
	// �A�N�^�[�̌���
	virtual ActorPtr findActor(const std::string& name) override;
	//�A�N�^�[�̈ꊇ����
	virtual void findActors(const std::string& name, std::list<ActorPtr>& actorList) override;
	//�A�N�^�[�̈ꊇ����
	virtual void findActors(const std::string& name, std::list<std::weak_ptr<Actor>>& actorList) override;
	// ���b�Z�[�W�̑��M
	virtual void sendMessage(EventMessage message, void* param = nullptr)  override;
	//�ꎞ��~
	void worldStop();
	//�ĊJ
	void worldStart();
	// �C�x���g���X�i�[�̒ǉ�
	void addEventMessageListener(std::function<void(EventMessage, void*)> listener);
	void end();
	
	virtual void setLateDraw(std::function<void()> draw, bool isBeforeUI = true) override;
	void setShadowMap(const bool flag);

	// �R�s�[�֎~
	World(const World& other) = delete;
	World& operator = (const World& other) = delete;

private:
	void normaldraw() const;
	void shadowdraw() const;
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

	std::list<std::function<void()>> lateDrawFuncList_;
	std::list<std::function<void()>> lateDrawFuncListAfterUI_;

	TempoManager tempo_;
	// �C�x���g���X�i�[
	std::function<void(EventMessage, void*)> listener_;
	//�V���h�E�}�b�v
	ShadowMap shadowmap_;
	int ShadowMapHandle;
	bool shadowflag_{ false };
	bool IsPause_{ false };
};
