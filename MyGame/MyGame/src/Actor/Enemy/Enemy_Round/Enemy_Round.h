#pragma once

#include"../BaseEnemy.h"

class Enemy_Round:public BaseEnemy {
public:
	Enemy_Round();
	Enemy_Round(IWorld* world, const std::string& name, const Vector3& position, int playerNumber);

	virtual std::shared_ptr<BaseEnemy> Create(IWorld* world, const Vector3& position, int playerNumber)override;

	virtual void JustStep()override;
	virtual void to_Normal() override;

	virtual void updateNormal(float deltaTime) override;
	virtual void onShadowDraw()const override;
	void setNearestPoint();
	void nextPosition();
private:
	std::vector<Vector3> points_;
	//ポイントキー
	int nextKey_;
};