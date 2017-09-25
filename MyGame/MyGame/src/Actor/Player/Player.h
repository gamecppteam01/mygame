#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationDx.h"
#include<map>
#include<functional>
#include<array>

enum class EventMessage;
class PlayerBullet;

class Player :public Actor {
public:
	enum class Player_State {
		Idle,//待機
		Move,//移動
		//Jump,//ジャンプ
		Step,//技
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
		Idle=0,//待機時
		Move_Forward=2,//前移動時
		Step_Left=8,//左ステップ時
		Attack = 11,//攻撃時
		Shoot = 12,//発射時
		ShootEnd=13,//発射終了
		KnockBack=14,//被弾時
		Down=15,//ダウン時
		//Jump = 17,//ジャンプ時
		Turn=11,//回転時
	};
	//ステップの種類
	enum class Step_Type {
		Chasse,//シャッセ
		Turn,//ターン
		Whisk,//ホイスク
		SplitCubanBreak,//スプリットキューバンブレイク
		Empty,//空
		Dance_Count//ダンスの数
	};

public:
	Player(IWorld* world,const std::string& name,const Vector3& position);


private:
	virtual void initialize()override;
	// メッセージ処理
	virtual void onMessage(EventMessage message, void* param);
	// 更新
	virtual void onUpdate(float deltaTime);
	// 描画
	virtual void onDraw() const;
	// 衝突した
	virtual void onCollide(Actor& other);

//プレイヤーの移動関係
private:
	//重力及びジャンプを更新する
	void gravityUpdate(float deltaTime);
	//フィールドとの当たり判定を行い、位置を補正する
	void correctPosition();

//状態関係
private:
	//状態変更とアニメーション変更を同時に行う
	bool change_State_and_Anim(Player_State state, Player_Animation animID, float animSpeed = 1.0f);

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

	//待機状態への移行処理
	void to_IdleMode();
	//移動状態への移行処理
	void to_MoveMode();
	//void to_JumpMode();
	//技状態への移行処理
	void to_StepMode();
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
private:
	void changeAnimation(Player_Animation animID, float animSpeed = 1.0f);


//弾(女)関係
private:
	//女がプレイヤーに追従するかどうか
	bool isCanTracking() const;
	void bulletUpdate(float deltaTime);
private:
	//男関連
	//移動ベクトル
	Vector3 velocity_;
	//上方向ベクトル
	float upVelocity_;
	//重力
	float gravity_;
	//プレイヤーのアニメーション
	AnimationDx animation_;
	//状態
	Player_State state_;
	//ステップを格納する
	std::array<Step_Type, 3> stepCombo_;
	//女関連
	//女本体
	std::shared_ptr<PlayerBullet> bullet_{};
	//女の位置、男側で直に書き換える
	Vector3* bulletPosition_{};
	//女の移動ベクトル
	Vector3 bulletVelocity_;
	//回転力
	float turnPower_;


	std::map<Player_State, std::function<void(float)>> playerUpdateFunc_;
	std::map<Player_State, std::function<void()>> playerToNextModeFunc_;

private:
	Vector3 defaultPosition_;
};