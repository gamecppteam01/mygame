#pragma once
#include"BaseEnemy.h"

class Player;
class NormalEnemy :public BaseEnemy {
public:
	NormalEnemy(IWorld* world,const std::string& name,const Vector3& position,int playerNumber,const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));

private:
	//ステップ通知時の処理
	virtual void JustStep()override;

	virtual void updateNormal(float deltaTime)override;

	virtual void to_Normal()override;
private:
	int getNearestPoint(const Vector3& position);

	//次の目的地を設定する
	void setNextPosition();
private:
	//次のポイント
	int nextPoint_;
	//次の目的地
	Vector3 nextPosition_;

	std::weak_ptr<Player> player_;
	//ボーナス
	bool isGoBonus_{ false };

	//ステージ周回ポイント配列
	std::vector<Vector3> roundPoint_;
};