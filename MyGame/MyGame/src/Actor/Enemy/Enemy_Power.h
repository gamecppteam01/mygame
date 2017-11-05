#pragma once
#include "BaseEnemy.h"

class Enemy_Power : public BaseEnemy {
public:
	//コンストラクタ
	Enemy_Power(IWorld* world, const std::string& name, const Vector3& position, int playerNumber, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));

private:
	//ステップ通知時の処理
	virtual void JustStep()override;

	virtual void updateNormal(float deltaTime)override;

	virtual void to_Normal()override;
	virtual void to_Attack(BaseEnemy::Enemy_Animation anim)override;

private:
	//狙う場所
	Vector3 targetPos_{ Vector3::Zero };

	//選手群
	std::list<ActorPtr> players_;
	
};