#pragma once
#include"../JudgeBase.h"
#include"../../../Graphic/AnimationDx.h"

enum class Judge_State {
	Search,
	Regard,
};

class Judge_NPC : public JudgeBase {
public:
	//コンストラクタ
	Judge_NPC(IWorld* world, const Vector3& position,const Matrix& rotation);
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
	//角度の取得
	float getAngle()const;
private:
	//状態更新
	void StateUpdate(float deltaTime);
	//探索更新
	void SearchUpdate(float deltaTime);
	//注視更新
	void RegardUpdate(float deltaTime);

private:
	//状態
	Judge_State m_State;
	//横回転角
	float yaw;
	//角度
	float m_Angle;
	//1カウント
	float m_Count;
	//タイマー
	float m_Timer;

	AnimationDx animation_;
};