#pragma once
#include"Enemy.h"
#include"../Body/BoundingCapsule.h"

class EnemyBullet;

class BaseEnemy :public Enemy {
public:
	//アニメーションのキー番号(各値は、実際にmv1に設定されているアニメーションと関連付ける事)
	enum class Enemy_Animation {
		Idle = 0,//待機時
		Move_Forward = 1,//前移動時
		Step_Left = 2,//左ステップ時
		Turn = 3,//回転時
		KnockBack = 4,//被弾時
		Down = 5,//ダウン時
	};
	enum class Enemy_State {
		Normal,//通常時更新
		Step,//ステップを開始する
		Track,//追跡中
	};
public:
	//カプセル判定は例、キャラクターの体型に応じて設定を変更する事
	BaseEnemy(IWorld* world, const std::string& name, const Vector3& position,int playerNumber, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));
	void hitOther(const Vector3& velocity);

	//選手番号を取得する
	int getPlayerNumber()const { return playerNumber_; }
private:
	// メッセージ処理
	virtual void onMessage(EventMessage message, void* param) override;
	// 更新
	virtual void onUpdate(float deltaTime)override;
	// 描画
	virtual void onDraw() const override;
	// 衝突した
	virtual void onCollide(Actor& other) override;
	
	// 衝突した後
	virtual void onCollideResult() override;

	Vector3 mathBound(Actor& other);

	// フィールドとの衝突判定(足場と当たった場合はtrueを返す)
	virtual bool field(Vector3& result = Vector3()) override;

	//フィールドとの当たり判定を行い、位置を補正する
	void correctPosition();

private:
	//ステップ通知時の処理
	virtual void JustStep()override;

	//索敵
	void searchTarget(float deltaTime);
	//パートナーの更新
	void bulletUpdate(float deltaTime);

	//指定位置への移動
	void addVelocity_NextPosition(float deltaTime);

	//アニメーションの変更
	void changeAnimation(Enemy_Animation animID);
	//状態の更新
	bool change_State(Enemy_State state);
	//状態変更とアニメーション変更を同時に行う
	bool change_State_and_Anim(Enemy_State state, Enemy_Animation animID);

	void to_Normal();
	void to_Step();
	void to_Track();

	void updateNormal(float deltaTime);
	void updateStep(float deltaTime);
	void updateTrack(float deltaTime);
private:
	float stepTime_{ 0.0f };
	Vector3 velocity_;
	//はじかれ時のベクトル
	Vector3 bound_{ Vector3::Zero };
	//次に向かう対象
	Vector3 nextPosition_;
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

	//選手番号
	int playerNumber_;

	Enemy_State state_{ Enemy_State::Normal };
};