#pragma once
#include"../JudgeBase.h"

class Judgement_SpotLight : public JudgeBase {
public:
	//コンストラクタ
	Judgement_SpotLight(IWorld* world, const std::string& name, const Vector3& position);
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
	float m_Distance;
};