#pragma once
#include"../JudgeBase.h"
#include"../../../Light/LightHandle.h"
#include"../../../ScoreManager/ScoreData.h"
#include"../../../Light/LightHandle_Data.h"
#include<map>
#include<functional>
#include<list>

class Judgement_SpotLight : public JudgeBase {
public:
	enum class State {
		SetUp,
		Ready,
		CenterLighting,
		SetUpSpotLighting,
		Failure,
		SpotLighting,
	};
	enum LightMood {
		CenterLight = 1,
		SpotLight,
	};
public:
	//�R���X�g���N�^
	Judgement_SpotLight(IWorld* world, const Vector3& position, LightHandle& light);
	//������
	virtual void initialize()override;
	// ���b�Z�[�W����
	virtual void onMessage(EventMessage message, void* param) override;
	// �X�V
	virtual void onUpdate(float deltaTime) override;
	// �`��
	virtual void onDraw() const override;
	// �Փ˂���
	virtual void onCollide(Actor& other) override;
	//����
	virtual bool Judgement(ActorPtr& target) override;
	virtual bool Judgement(const Vector3& target) override;

private:
	void SetUp(float deltaTime);
	void ReadyUpdate(float deltaTime);
	void CenterLightingUpdate(float deltaTime);
	void SetUpSpotLighting(float deltaTime);
	void FailureUpdate(float deltaTime);
	void SpotLightingUpdate(float deltaTime);
	void TimeCount(float deltaTime);
	void TimeJudge(ScoreData& data);

private:
	float m_Distance;

	//���C�g�n���h���N���X
	LightHandle m_LightHandle;
	//�X�e�C�g
	State m_State;
	//�^�C�}�[
	float m_Timer{ 2.0f };
	int effectHandole{ -1 };
	//�I��f�[�^
	std::list<ScoreData> m_Data;
	std::map<int, ScoreData> m_DataList;
	//�^�[�Q�b�g
	std::weak_ptr<Actor> m_Target;
	//���C�g�f�[�^
	std::map<LightMood, Spot_Data> m_LightData;
	//�J�E���g
	int m_Count{ 0 };
	//���݂̎���
	float m_NowTimer{ 0.0f };
	//�ő�̎���
	float m_MaxTimer{ 1.0f };

	//float out_angle{ 0.7f }, in_angle{ 0.6f }, atten0{ 0.75f }, atten1{ 0.003f };

	std::map<State, std::function<void(float deltaTime)>> m_StateUpdateFunc;
};