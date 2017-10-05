#pragma once
#include"Enemy.h"
#include"../Body/BoundingCapsule.h"

class EnemyBullet;

class BaseEnemy :public Enemy {
public:
	//アニメーションのキー番号(各値は、実際にmv1に設定されているアニメーションと関連付ける事)
	enum class Enemy_Animation {
		Idle = 0,//待機時
		Move_Forward = 2,//前移動時
		Step_Left = 8,//左ステップ時
		Attack = 11,//攻撃時
		KnockBack = 14,//被弾時
		Down = 15,//ダウン時
	  Turn = 11,//回転時
	};

public:
	//カプセル判定は例、キャラクターの体型に応じて設定を変更する事
	BaseEnemy(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));
private:
	// メッセージ処理
	virtual void onMessage(EventMessage message, void* param) override;
	// 更新
	virtual void onUpdate(float deltaTime)override;
	// 描画
	virtual void onDraw() const override;
	// 衝突した
	virtual void onCollide(Actor& other) override;

private:
	//索敵
	void searchTarget(float deltaTime);
	//パートナーの更新
	void bulletUpdate(float deltaTime);

	//アニメーションの変更
	void changeAnimation(Enemy_Animation animID);

private:
	Vector3 velocity_;
	//本体
	std::shared_ptr<EnemyBullet> bullet_;
	//女の位置、男側で直に書き換える
	Vector3* bulletPosition_{};
	//女の回転、男側で直に書き換える
	Matrix* bulletRotation_{};
	//女の移動ベクトル
	Vector3 bulletVelocity_;
	//回転力
	float turnPower_;

	ActorPtr target_;
};