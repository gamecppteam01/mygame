#include "Judgement_SpotLight.h"
#include"../../../World/IWorld.h"
#include"../../ActorGroup.h"
#include"../../../Math/Math.h"
#include"../../../Graphic/DebugDraw.h"
#include"../../../Define.h"
#include"../../../Graphic/EffekseerManager.h"
#include"../../../ScoreManager/ScoreManager.h"
#include"../../../ScoreManager/ScoreData.h"
#include"../../../Input/Keyboard.h"
#include"../../../DataManager/DataManager.h"
#include<list>
#include<minmax.h>

//コンストラクタ
Judgement_SpotLight::Judgement_SpotLight(IWorld * world, const Vector3 & position, LightHandle& light)
	:JudgeBase(world, "SpotLight", position), m_LightHandle(light) {
	initialize();
}

//初期化
void Judgement_SpotLight::initialize() {
	m_State = State::SetUp;
	m_LightHandle.setLightEnableHandle("Spot", false);
	m_StateUpdateFunc[State::SetUp] = [this](float deltaTime) {SetUp(deltaTime); };
	m_StateUpdateFunc[State::Ready] = [this](float deltaTime) {ReadyUpdate(deltaTime); };
	m_StateUpdateFunc[State::CenterLighting] = [this](float deltaTime) {CenterLightingUpdate(deltaTime); };
	m_StateUpdateFunc[State::SetUpSpotLighting] = [this](float deltaTime) {SetUpSpotLighting(deltaTime); };
	m_StateUpdateFunc[State::Failure] = [this](float deltaTime) {FailureUpdate(deltaTime); };
	m_StateUpdateFunc[State::SpotLighting] = [this](float deltaTime) {SpotLightingUpdate(deltaTime); };

	m_LightData[CenterLight] = Spot_Data("Spot", Vector3(0.0f, 100.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f), 0.7f, 0.6f, 500.0f, 0.75f, 0.003f, 0.0f);
	m_LightData[SpotLight] = Spot_Data("Spot", Vector3(0.0f, 100.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f), 0.5f, 0.4f, 500.0f, 0.75f, 0.012f, 0.0f);
}

//メッセージ処理
void Judgement_SpotLight::onMessage(EventMessage message, void * param) {
}

//更新
void Judgement_SpotLight::onUpdate(float deltaTime) {
	m_StateUpdateFunc[m_State](deltaTime);
}

//描画
void Judgement_SpotLight::onDraw() const {
}

//衝突処理
void Judgement_SpotLight::onCollide(Actor & other) {
}

//判定
bool Judgement_SpotLight::Judgement(ActorPtr& target) {

	switch (m_State)
	{
	case State::CenterLighting:
		if (is_In_Distans(target) == true) {
			IsInEnemy_ = true;
			count_++;
			DataManager::GetInstance().setCount(count_);
		}
		return false;
		break;
	case State::SpotLighting:
		if (is_In_Distans(target) == true) {
			return true;
		}
		return false;
	default:
		break;
	}
	//if (m_State == State::SpotLighting) count_ = 0;
	//if (m_State != State::SpotLighting) return false;

	//if (is_In_Distans(target) == true) {
	//	return true;
	//}
	//return false;

}

bool Judgement_SpotLight::Judgement(const Vector3 & target) {
	if (m_State != State::SpotLighting) return false;

	Vector2 myPos = Vector2(position_.x, position_.z);
	Vector2 targetPos = Vector2(target.x, target.z);
	if (Vector2::Distance(myPos, targetPos) <= 28.0f) {
		return true;
	}
	return false;
}

bool Judgement_SpotLight::In_Range(ActorPtr & target)
{
	if (m_State != State::CenterLighting) return false;
	
	if (is_In_Distans(target) == true) {
		return true;
	}
	return false;
}

bool Judgement_SpotLight::getIsNotice(int num) const
{
	if (m_DataList.count(num) == 0)return false;
	return m_DataList.at(num)->notice_;
}

void Judgement_SpotLight::SetUp(float deltaTime) {
	position_ = Vector3::Up * 2.0f;
	m_LightHandle.setLightPositionHandle("Spot", Vector3(0.0f, 100.0f, 0.0f));
	m_LightHandle.setLightAngleHandle("Spot", m_LightData[CenterLight].cone_outangle_, m_LightData[CenterLight].cone_inangle_);
	m_LightHandle.setLightRangeAttenHandle("Spot", 500.0f, m_LightData[CenterLight].atten0_, m_LightData[CenterLight].atten1_, m_LightData[CenterLight].atten2_);
	m_Count = 0;
	m_NowTimer = 0.0f;

	for (auto& d : m_DataList) {
		d.second->time_ = 0.0f;
		d.second->notice_ = false;
	}

	if (m_Timer <= 0.0f) {
		m_Timer = 2.0f;
		m_State = State::Ready;
		return;
	}
	m_Timer -= deltaTime;
}

void Judgement_SpotLight::ReadyUpdate(float deltaTime) {
	//データの取得
	//データリストが0なら実行
	if (m_DataList.size() == 0) { 
		world_->getCanChangedScoreManager().getScoreDataMap(m_DataList); }

	if (m_Timer <= 0.0f) {
		EffekseerManager::GetInstance().StopEffect3D(effectHandole);
		m_Timer = 15.0f;
		m_State = State::CenterLighting;
		return;
	}

	m_Timer -= deltaTime;

	if (EffekseerManager::GetInstance().isPlayEffect3D(effectHandole))return;
	effectHandole = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::POINT_UP_EFFECT, Vector3::Zero, Vector3::Zero, Vector3::One*0.7f);
	EffekseerManager::GetInstance().SetPosPlayEffect3D(effectHandole, Vector3{ 0.0f,0.0f,0.0f });

}

void Judgement_SpotLight::CenterLightingUpdate(float deltaTime) {
	float t = m_NowTimer / m_MaxTimer;
	Color color = Color::Lerp(Color(0.5f, 0.5f, 0.5f, 0.5f), Color(0.1f, 0.1f, 0.1f, 0.1f), t);
	m_LightHandle.setGlobalAmbientLight(color);
	world_->sendMessage(EventMessage::Lighting, (void*)&position_);

	//暗くなったらセンターライトの点灯
	if (m_NowTimer >= m_MaxTimer) { m_LightHandle.setLightEnableHandle("Spot", true); }

	//範囲内に入っていたらタイムを計る
	TimeCount(deltaTime);

	if (m_Count >= 1) {
		m_Timer = 8.0f;
		m_NowTimer = 0.0f;
		m_State = State::SetUpSpotLighting;
		return;
	}
	else if (m_Timer <= 0.0f) {
		m_State = State::Failure;
		return;
	}
	m_Timer -= deltaTime;
	m_NowTimer = min(m_NowTimer + deltaTime, m_MaxTimer);
}

void Judgement_SpotLight::SetUpSpotLighting(float deltaTime) {
	float t = m_NowTimer / m_MaxTimer;
	position_ = Vector3::Lerp(position_, m_Target.lock()->position(), t);
	m_LightHandle.setLightPositionHandle("Spot", Vector3(position_.x, 100.0f, position_.z));
	float out_a = MathHelper::Lerp(m_LightData[CenterLight].cone_outangle_, m_LightData[SpotLight].cone_outangle_, t);
	float in_a = MathHelper::Lerp(m_LightData[CenterLight].cone_inangle_, m_LightData[SpotLight].cone_inangle_, t);
	m_LightHandle.setLightAngleHandle("Spot", out_a, in_a);
	float atten0 = MathHelper::Lerp(m_LightData[CenterLight].atten0_, m_LightData[CenterLight].atten0_, t);
	float atten1 = MathHelper::Lerp(m_LightData[CenterLight].atten1_, m_LightData[CenterLight].atten1_, t);
	m_LightHandle.setLightRangeAttenHandle("Spot", 500.0f, atten0, atten1, 0.0f);

	m_NowTimer = min(m_NowTimer + deltaTime, m_MaxTimer);
	if (m_NowTimer >= m_MaxTimer) {
		m_State = State::SpotLighting; 
	}
}

void Judgement_SpotLight::FailureUpdate(float deltaTime) {
	//スポットライトの消灯
	m_LightHandle.setLightEnableHandle("Spot", false);
	float t = m_NowTimer / m_MaxTimer;
	Color color = Color::Lerp(Color(0.1f, 0.1f, 0.1f, 0.1f), Color(0.5f, 0.5f, 0.5f, 0.5f), t);
	m_LightHandle.setGlobalAmbientLight(color);
	m_Timer = 30.0f;
	m_NowTimer = min(m_NowTimer + deltaTime, m_MaxTimer);
	if (m_NowTimer >= m_MaxTimer){
		m_State = State::SetUp;
		world_->sendMessage(EventMessage::Extinction);
	}
}

void Judgement_SpotLight::SpotLightingUpdate(float deltaTime) {
	position_ = m_Target.lock()->position();
	m_LightHandle.setLightPositionHandle("Spot", Vector3(position_.x, 100.0f, position_.z));

	if (m_Timer <= 0.0f) {
		m_NowTimer = 0.0f;
		m_State = State::Failure;
		for (auto& d : m_DataList) {
			d.second->notice_ = false;
		}
	}
	m_Timer -= deltaTime;
}

void Judgement_SpotLight::TimeCount(float deltaTime) {
	for (auto& d : m_DataList) {
		if (is_In_Distans(d.second->target_.lock())) {
			//3秒経っているか
			TimeJudge(d.second);
			d.second->time_ += deltaTime;
		}
		else {
			d.second->time_ = 0.0f;
		}
	}
}

void Judgement_SpotLight::TimeJudge(ScoreData* data) {
	//対象の時間数が3秒を超えていたらカウントを追加
	if (data->time_ >= 3.0f) {
		m_Count++;
		data->notice_ = true;

		//カウントが2以上で強制的に1番をターゲットにする
		if (m_Count >= 2) {
			m_Target = m_DataList[1]->target_;
			m_DataList[1]->notice_ = true;
		}
		else {
			m_Target = data->target_;
		}

	}
}

bool Judgement_SpotLight::IsInEnemy()
{
	return IsInEnemy_;
}

int Judgement_SpotLight::getCountEnemy()
{
	return count_;
}
