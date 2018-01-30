#pragma once

#include"../BaseEnemy.h"
#include"../../../ScoreManager/ScoreData.h"

class Enemy_Round:public BaseEnemy {
public:
	Enemy_Round();
	Enemy_Round(IWorld* world, const std::string& name, const Vector3& position, int playerNumber);

	virtual std::shared_ptr<BaseEnemy> Create(IWorld* world, const Vector3& position, int playerNumber)override;

	virtual void to_Normal() override;
	virtual void JustStep() override;
	virtual void updateNormal(float deltaTime) override;
	virtual void onShadowDraw()const override;
	void setNearestPoint();
	void nextPosition();
	void Step();
	//自分と1位が距離内か？
	bool Distance_First();
	//自分が1位かどうか？
	bool RankedFirst();

	//範囲内の敵の数
	int Around_Enemy(float distance);

private:
	std::vector<Vector3> points_;
	//ポイントキー
	int nextKey_;
	//ステップ
	int nextStep;
	//1位のScoreData
	ScoreData firstdata;
};