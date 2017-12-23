#pragma once

#include"../BaseEnemy.h"
#include"../../../ScoreManager/ScoreData.h"

class Enemy_Notice : public BaseEnemy{
private:
	enum Notice_State {
		Normal,
		Steal,
	};
public:
	Enemy_Notice();
	//コンストラクタ
	Enemy_Notice(IWorld* world, const std::string& name, const Vector3& position, int playerNumber, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));
	
	virtual std::shared_ptr<BaseEnemy> Create(IWorld* world, const Vector3& position, int playerNumber);

	// メッセージ処理
	virtual void onMessage(EventMessage message, void* param) override;
private:
	//ステップ通知時の処理
	virtual void JustStep()override;

	virtual void updateNormal(float deltaTime) override;
	virtual void updateFever(float deltaTime) override;

	virtual void to_Normal() override;
	virtual void to_Fever() override;
private:
	int getNearestPoint(const Vector3& position);

	//次の目的地を設定する
	void setNextPosition();
private:
	//ステイト
	Notice_State state_;
	//次のポイント
	int nextPoint_;
	//次の目的地
	Vector3 nextPosition_;
	//ボーナス
	bool isGoBonus_{ false };
	//ライトの座標
	Vector3 lightPosition_;
	//ステップをする確率
	int probability_{ 4 };
	//自分のデータ
	ScoreData* data_;
	//ステージ周回ポイント配列
	std::vector<Vector3> roundPoint_;
	//ステップフラグ
	bool stepFlag_{ false };
	//チェンジフラグ
	bool changeFlag_{ false };

};
