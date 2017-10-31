#pragma once
#include"../Actor.h"

class JudgeBase : public Actor {
public:
	//コンストラクタ
	JudgeBase(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body);
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
	virtual bool Judgement(ActorPtr& target) = 0;
	virtual bool Judgement(const Vector3& position) = 0;

protected:
	//視野角内にいるか？
	bool is_Scorp_Angle(ActorPtr& target, float angle = 45.0f) const;
	bool is_Scorp_Angle(const Vector3& target, float angle = 45.0f) const;
	//一定距離内にいるか？
	bool is_In_Distans(ActorPtr& target, float distance = 50.0f) const;

};
