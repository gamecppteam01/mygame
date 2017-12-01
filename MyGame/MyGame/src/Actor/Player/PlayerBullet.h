#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationDx.h"

class Player;

//プレイヤーの攻撃(女)
class PlayerBullet:public Actor {
	friend class Player;
public:
	//アニメーションのキー番号(各値は、実際にmv1に設定されているアニメーションと関連付ける事)
	enum class PlayerBullet_Animation {
		Move_Forward = 0,//前移動時
		Idle = 1,//待機時
		Shoot = 1,//左ステップ時
		Quarter=2,
		ShootEnd=9,
		Step_Left=10,
		Turn = 3,//回転時
		Half=4,
		Attack = 12,//攻撃時
		KnockBack = 14,//被弾時
		Down = 15,//ダウン時
		//Jump = 17,//ジャンプ時
	};

public:
	PlayerBullet(IWorld* world, const Vector3& position, Player* player);
	//初期化
	virtual void initialize() override;

	void hitEnemy(const std::string& hitName, const Vector3& velocity);
	//プレイヤーを取得する
	const Player* getPlayer()const;

	virtual Vector3& position()override;
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
	void changeAnimation(PlayerBullet_Animation animID, float animFrame = 0.0f, float animeSpeed = 1.0f, bool isLoop = true);
	Player* player_;
private:

	//プレイヤーのアニメーション
	AnimationDx animation_;

};