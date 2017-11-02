#pragma once
#include "../BaseEnemy.h"

class Enemy_Quick : public BaseEnemy {
public:
	//コンストラクタ
	Enemy_Quick(IWorld* world, const std::string& name, const Vector3& position, int playerNumber, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));
	
private:
	//ステップ通知時の処理
	virtual void JustStep()override;

	virtual void updateNormal(float deltaTime)override;

	virtual void to_Normal()override;
	//索敵
	void searchTarget(float deltaTime);

private:
	float m_MoveSpeed{ 3.0f };
	float m_Timer;
};