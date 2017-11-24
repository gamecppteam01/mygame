#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationDx.h"
#include<map>
#include<functional>
#include<array>
#include"../../Method/MethodTimer.h"
#include"Step_Type.h"
#include"GyroRotateChecker.h"
#include"../../Define.h"
#include"../../Sound/MusicScoreManager.h"
class PlayerBullet;

class Player :public Actor {
public:

	enum class Player_State {
		Idle,//待機
		Move,//移動
		//Jump,//ジャンプ
		Step,//技
		Step_Success,//技成功
		Stumble,//よろけモード
		Attack,//攻撃
		Shoot,//発射
		ShootEnd,//発射終了
		KnockBack,//被弾
		Down,//ダウン時
		Turn,//回転
		State_Count//ステート数を数えるための列挙値(Countを状態として利用しないこと)
	};
	//アニメーションのキー番号(各値は、実際にmv1に設定されているアニメーションと関連付ける事)
	enum class Player_Animation {
		Move_Forward = 0,//前移動時
		Idle = 1,//待機時
		Step_Left = 8,//左ステップ時
		Attack = 11,//攻撃時
		Shoot = 12,//発射時
		ShootEnd = 13,//発射終了
		KnockBack = 14,//被弾時
		Down = 15,//ダウン時
		Turn = 17,//回転時
	};

public:
	Player(IWorld* world,const std::string& name,const Vector3& position,int playerNumber);

//外部公開関数
public:
	void addVelocity(const Vector3& velocity);
	void hitEnemy(const std::string& hitName, const Vector3& velocity);
	//選手番号を取得する
	int getPlayerNumber()const { return playerNumber_; }
	//よろけ方向を取得する
	Vector2 getStumbleDirection()const { return stumbleDirection_; }
	//現在の状態を取得する
	Player_State getState()const { return state_; }
	//現在のステップの種類を返す(1=クォーター,2=ハーフ,3=ターン,4=スピン)
	int getStep()const { return nextStep_; }

	virtual Vector3& position()override { return centerPosition_; }
	Vector3 getCenterPos()const { return centerPosition_; }
	//スコア倍率を取得する
	float getPlayerScoreRate()const;
	//汎用のタイマーを渡す
	float getTimer()const { return timeCount_; }
private:
	void createBullet();
	virtual void initialize()override;
	virtual void onPause()override;
	virtual void onRestart()override;
	// メッセージ処理
	virtual void onMessage(EventMessage message, void* param);
	// 更新
	virtual void onUpdate(float deltaTime);
	// 描画
	virtual void onDraw() const;
	// 衝突した
	virtual void onCollide(Actor& other);

	virtual void onCollideResult()override;

//通知処理関連
private:
	//ステップ通知時の処理
	virtual void JustStep()override;
	//エフェクト生成通知の処理
	virtual void CreateJustEffect()override;
	
	// フィールドとの衝突判定(足場と当たった場合はtrueを返す)
	virtual bool field(Vector3& result = Vector3()) override;

//プレイヤーの移動関係
private:
	//重力及びジャンプを更新する
	void gravityUpdate(float deltaTime);
	//フィールドとの当たり判定を行い、位置を補正する
	void correctPosition();

//状態関係
private:
	//状態変更とアニメーション変更を同時に行う
	bool change_State_and_Anim(Player_State state, Player_Animation animID, float animFrame = 0.0f, float animSpeed = 1.0f, bool isLoop = true);

	//状態の更新
	bool change_State(Player_State state);

	//待機時更新
	void idle_Update(float deltaTime);
	//移動時更新
	void move_Update(float deltaTime);
	//ジャンプ時更新
	//void jump_Update(float deltaTime);
	//技時更新
	void step_Update(float deltaTime);
	//技成立時更新
	void stepSuccess_Update(float deltaTime);
	//攻撃時更新
	void attack_Update(float deltaTime);
	//発射時更新
	void shoot_Update(float deltaTime);
	//発射終了時更新
	void shootend_Update(float deltaTime);
	//被弾時更新
	void knockback_Update(float deltaTime);
	//被弾時更新
	void down_Update(float deltaTime);
	//回転時更新
	void turn_Update(float deltaTime);
	//よろけ時更新
	void stumble_Update(float deltaTime);

	//待機状態への移行処理
	void to_IdleMode();
	//移動状態への移行処理
	void to_MoveMode();
	//void to_JumpMode();
	//技状態への移行処理
	void to_StepMode();
	//技完成状態への移行処理
	void to_StepSuccessMode();
	//攻撃状態への移行処理
	void to_AttackMode();
	//発射状態への移行処理
	void to_ShootMode();
	//発射終了状態への移行処理
	void to_ShootEndMode();
	//被弾状態への移行処理
	void to_KnockBackMode();
	//被弾状態への移行処理
	void to_DownMode();
	//回転状態への移行処理
	void to_TurnMode();
	//よろけ状態への移行処理
	void to_StumbleMode();

	//待機状態の終了処理
	void end_IdleMode();
	//移動状態の終了処理
	void end_MoveMode();
	//void to_JumpMode();
	//技状態の終了処理
	void end_StepMode();
	//ステップ成功の終了処理
	void end_StepSuccessMode();
	//攻撃状態の終了処理
	void end_AttackMode();
	//発射状態の終了処理
	void end_ShootMode();
	//発射終了状態の終了処理
	void end_ShootEndMode();
	//被弾状態の終了処理
	void end_KnockBackMode();
	//被弾状態の終了処理
	void end_DownMode();
	//回転状態の終了処理
	void end_TurnMode();
	//よろけの終了処理
	void end_StumbleMode();

private:
		//攻撃ステップ
		void stepAttack(float deltaTime);

private:
	//アニメーションの変更
	void changeAnimation(Player_Animation animID, float animFrame = 0.0f,float animeSpeed=1.0f,bool isLoop=true);

private:
	//ステップに変更する状態か
	bool isChangeStep() const;

	//よろけが発生可能な状態か
	bool isCanStamble()const;
	
	//攻撃状態かどうか
	bool isAttack();
	//姿勢チェックをするかどうか
	bool isRequiredCheckPosture()const;
//弾(女)関係
private:
	//女がプレイヤーに追従するかどうか
	bool isCanTracking() const;
	void bulletUpdate(float deltaTime);
	//円エフェクトを生成する
	void createCircleEffect();
private:
	//スティックのベクトルを右手座標系に変換
	Vector2 getSticktoMove();

	Vector2 mathStumbleDirection(const Vector2& stumbleDirection);

	bool isJustTiming()const;
private:
	//成立したステップ(0=非成立,1=クォーター,2=ハーフ,3=ターン,4横回転)
	int successStep_;
	//次のステップ
	int nextStep_;
	//選手番号
	int playerNumber_;
	//ステップの周期を測る
	int stepCount_{ 0 };

	float shootAngle_;
	//汎用タイマー
	float timeCount_;
	//ダウンする時間
	float downTime_{ 7.0f };
	//2体の中心
	Vector3 centerPosition_{ Vector3::Zero };
	//よろけ関連
	//ヒットした向き
	Vector2 stumbleDirection_{ Vector2::Zero };
	float stumbleRegistTimer_{ 0.f };
	//男関連
	//移動ベクトル
	Vector3 velocity_;
	//跳ね返りベクトル
	Vector3 bound_;
	//上方向ベクトル
	float upVelocity_;
	//重力
	float gravity_;
	//プレイヤーのアニメーション
	AnimationDx animation_;
	//状態
	Player_State state_;
	//エフェクト生成クラスを呼び出す
	MethodTimer effectCreator_;
	//スコア加算の成否
	bool isJustStep_{ false };
	//攻撃対象
	ActorPtr attackTarget_;

	//よろけから回復するまでの時間
	float stumbleResurrectTime_{ 0.5f };


	//女関連
	//女本体
	std::shared_ptr<PlayerBullet> bullet_{};
	//女の位置、男側で直に書き換える
	Vector3* bulletPosition_{};
	//女の回転、男側で直に書き換える
	Matrix* bulletRotation_{};
	//女の移動ベクトル
	Vector3 bulletVelocity_;
	//回転力
	float turnPower_;
	//エフェクトのサイズ
	std::array<float,3> effectSize_{ 0.0f,0.0f,0.0f };
	//ジャイロの回転チェッククラス
	GyroRotateChecker gyroCheck_;
	//譜面管理クラス
	MusicScoreManager musicScore_;

	std::map<Player_State, std::function<void(float)>> playerUpdateFunc_;
	std::map<Player_State, std::function<void()>> playerEndModeFunc_;
	std::map<Player_State, std::function<void()>> playerToNextModeFunc_;

	std::list<SE_ID> restartSEList_;

private:
	const Vector3 defaultPosition_;

	const std::map<int, std::pair<Player_Animation, int>> stepAnimScoreList_{
		{ 1,{ Player_Animation::Down,SCORE_QUARTER } },
		{ 2,{ Player_Animation::KnockBack,0 } },
		{ 3,{ Player_Animation::Idle,SCORE_TURN } },
		{ 4,{ Player_Animation::Turn,0 } },
	};


};