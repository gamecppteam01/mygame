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
	//コンストラクタ
	Judgement_SpotLight(IWorld* world, const Vector3& position, LightHandle& light);
	//初期化
	virtual void initialize()override;
	// メッセージ処理
	virtual void onMessage(EventMessage message, void* param) override;
	// 更新
	virtual void onUpdate(float deltaTime) override;
	// 描画
	virtual void onDraw() const override;
	// 衝突した
	virtual void onCollide(Actor& other) override;
	//判定
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

	//ライトハンドルクラス
	LightHandle m_LightHandle;
	//ステイト
	State m_State;
	//タイマー
	float m_Timer{ 2.0f };
	int effectHandole{ -1 };
	//選手データ
	std::list<ScoreData> m_Data;
	std::map<int, ScoreData> m_DataList;
	//ターゲット
	std::weak_ptr<Actor> m_Target;
	//ライトデータ
	std::map<LightMood, Spot_Data> m_LightData;
	//カウント
	int m_Count{ 0 };
	//現在の時間
	float m_NowTimer{ 0.0f };
	//最大の時間
	float m_MaxTimer{ 1.0f };

	//float out_angle{ 0.7f }, in_angle{ 0.6f }, atten0{ 0.75f }, atten1{ 0.003f };

	std::map<State, std::function<void(float deltaTime)>> m_StateUpdateFunc;
};