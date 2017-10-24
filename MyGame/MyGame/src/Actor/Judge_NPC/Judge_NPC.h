#pragma once
#include"../Actor.h"

enum class Judge_State {
	Search,
	Regard,
};

class Judge_NPC : public Actor {
public:
	//コンストラクタ
	Judge_NPC(IWorld* world, const std::string& name, const Vector3& position,float scope_angle = 45.0f);
	//初期化
	virtual void initialize()override;
	// メッセージ処理
	virtual void onMessage(EventMessage message, void* param);
	// 更新
	virtual void onUpdate(float deltaTime);
	// 描画
	virtual void onDraw() const;
	// 衝突した
	virtual void onCollide(Actor& other);

	float getAngle()const;
private:
	//状態更新
	void StateUpdate(float deltaTime);
	//探索更新
	void SearchUpdate(float deltaTime);
	//注視更新
	void RegardUpdate(float deltaTime);
	//視野角内にいるか？
	bool is_Scorp_Angle(ActorPtr& target) const;
	//一定距離内にいるか？
	bool is_In_Distans(ActorPtr& target) const;

private:
	//状態
	Judge_State m_State;
	//視野角
	float m_Scope_angle;
	//横回転角
	float yaw;
	//角度
	float m_Angle;
	//1カウント
	float m_Count;
	//タイマー
	float m_Timer;
};