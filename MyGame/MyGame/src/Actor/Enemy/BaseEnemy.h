#pragma once
#include"Enemy.h"
#include"../Body/BoundingCapsule.h"
#include"../../Method/MethodTimer.h"
#include"../../Define.h"
class EnemyBullet;

class BaseEnemy :public Enemy {
	friend class EnemyBullet;
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
		Attack,//攻撃
		Down,//転倒

	};
public:
	//カプセル判定は例、キャラクターの体型に応じて設定を変更する事
	BaseEnemy(IWorld* world, const std::string& name, const Vector3& position,int playerNumber, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));
	virtual ~BaseEnemy(){}
	void hitOther(const Vector3& velocity);

	//選手番号を取得する
	int getPlayerNumber()const { return playerNumber_; }

	//
	Enemy_State getEnemyState()const { return state_; }

	//転倒カウントのセット
	virtual void setCountDown();

	virtual Vector3& position()override {
		return centerPosition_;
	}
protected:
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

	//一番近いキャラクターを受け取る
	ActorPtr getNearestActor();
	

	//topTime:最大値になる時間
	float mathSpeed(float current,float maxSpeed, float maxTime, float topTime);

	float mathSpeedUnderPower(float current, float maxSpeed, float maxTime, float topTime);
protected:
	//ステップ通知時の処理
	virtual void JustStep()override;
	//弾きを設定
	void setBoundPower(float powerRate);
	//索敵
	void searchTarget(float deltaTime);
	//パートナーの更新
	void bulletUpdate(float deltaTime);

	//指定位置への移動
	void addVelocity_NextPosition(float deltaTime);

	//アニメーションの変更
	void changeAnimation(Enemy_Animation animID,float animFrame=0.0f,float animSpeed=1.0f,bool isLoop=true);
	//状態の更新
	bool change_State(Enemy_State state,BaseEnemy::Enemy_Animation anim);
	//状態変更とアニメーション変更を同時に行う
	bool change_State_and_Anim(Enemy_State state, Enemy_Animation animID);

	virtual void to_Normal();
	virtual void to_Step(Enemy_Animation anim);
	virtual void to_Track();
	virtual void to_Attack(Enemy_Animation anim);
	virtual void to_Down();

	virtual void updateNormal(float deltaTime);
	virtual void updateStep(float deltaTime);
	virtual void updateTrack(float deltaTime);
	virtual void updateAttack(float deltaTime);
	virtual void updateDown(float deltaTime);

	//ステップ可能か
	bool isCanStep()const;
protected:
	float stepTime_{ 0.0f };
	Vector3 velocity_;
	//はじかれ時のベクトル
	Vector3 bound_{ Vector3::Zero };
	//次に向かう対象
	Vector3 nextPosition_;
	//2キャラの中心
	Vector3 centerPosition_{ Vector3::Zero };
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

	//イージングタイマー
	float speedEaseTimer_{ 0.0f };

	ActorPtr target_;

	//選手番号
	int playerNumber_;

	//ダウンするまでのカウント
	int downCount_;
	//ダウンカウントの変更タイマー
	MethodTimer downTimer_;
	//攻撃対象からの除外設定解除タイマー
	MethodTimer nonTargetResetTimer_;
	//ダウンしている時間
	float downTime_;

	//攻撃対象
	std::weak_ptr<Actor> attackTarget_;

	Enemy_State state_{ Enemy_State::Normal };

	//前に当たった相手の番号
	int prevHitActorNumber_{ 0 };

	//拍子タイマー
	int rhythmTimeCount_{ 0 };

	float boundPower_{ 15.0f };

protected:
	//攻撃する範囲
	const float attackDistance{ 30.0f };
	//ポジション追跡時の移動の勢い
	const float movePower{ 0.7f };
	//ダウンする時間
	const float downTime{ 3.0f };
	//男と女の距離
	const Vector3 bulletDistance{ 0.0f,0.0f,6.0f };

	const float attackPower{ 1.0f };
	const std::vector<std::pair<Enemy_Animation, int>> stepAnim{
		{Enemy_Animation::KnockBack,SCORE_QUARTER },//クォーター
		{Enemy_Animation::Idle,0},//ハーフ
		{Enemy_Animation::Step_Left,SCORE_TURN },//ターン
		{Enemy_Animation::Idle,0		  }//スピン
	};

};