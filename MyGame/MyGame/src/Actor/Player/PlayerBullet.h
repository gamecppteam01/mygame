#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationDx.h"

class Player;

//プレイヤーの攻撃(女)
class PlayerBullet:public Actor {
	friend class Player;
	friend class TutorialPlayer;
public:
	//アニメーションのキー番号(各値は、実際にmv1に設定されているアニメーションと関連付ける事)
	enum class PlayerBullet_Animation {
		Move_Forward = 0,//前移動時
		Idle = 1,//待機時
		Shoot = 1,//左ステップ時
		Quarter=2,
		ShootEnd=9,
		Step_Left=8,
		Turn = 3,//回転時
		Half=4,
		Attack = 12,//攻撃時
		KnockBack = 0,//被弾時
		Down = 5,//ダウン時
		Reversal=6,//起き上がり時
		Stumble=7,
		//Jump = 17,//ジャンプ時
	};

public:
	PlayerBullet(IWorld* world, const Vector3& position, Player* player);
	//初期化
	virtual void initialize() override;

	void hitEnemy(const std::string& hitName, const Vector3& velocity);
	//プレイヤーを取得する
	const Player* getPlayer()const;
	Player* getCCPlayer();

	virtual Vector3& position()override;

	//停止時のステップアニメーション更新命令
	virtual void stepAnimUpdate(float deltaTime)override;

private:
	// メッセージ処理
	virtual void onMessage(EventMessage message, void* param);
	// 更新処理
	virtual void onUpdate(float deltaTime);
	// 描画処理
	virtual void onDraw() const;
	// 衝突した時の処理
	virtual void onCollide(Actor& other);

//プレイヤー用
private:
	Vector3* getPositionPtr();
	Matrix* getRotationPtr();
	//アニメーションの変更
	void changeAnimation(PlayerBullet_Animation animID, float animFrame = 0.0f, float animeSpeed = 1.0f, bool isLoop = true,float blend=1.0f);
	Player* player_;
private:

	//プレイヤーのアニメーション
	AnimationDx animation_;

};