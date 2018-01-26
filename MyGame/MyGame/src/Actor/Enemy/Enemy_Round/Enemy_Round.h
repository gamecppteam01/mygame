#pragma once

#include"../BaseEnemy.h"
#include"../Base/AvoidSearch.h"

class Enemy_Round:public BaseEnemy {
public:
	Enemy_Round();
	Enemy_Round(IWorld* world, const std::string& name, const Vector3& position, int playerNumber);

	virtual std::shared_ptr<BaseEnemy> Create(IWorld* world, const Vector3& position, int playerNumber)override;

	virtual void JustStep()override;
	virtual void to_Normal() override;

	virtual void onDraw()const override;
	virtual void updateNormal(float deltaTime) override;
	virtual void onShadowDraw()const override;
	void setNearestPoint();
	void nextPosition();
	void selectPoint();

	virtual void setCountDown(int downCount);

private:
	std::vector<Vector3> points_;
	//ポイントキー
	int nextKey_;
	std::list<TestDP> score_;

	Vector3 avoidDirection_{ Vector3::Zero };//回避移動ベクトル
};