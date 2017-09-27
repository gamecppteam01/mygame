#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationDx.h"

//プレイヤーの攻撃(女)
class PlayerBullet:public Actor {
	friend class Player;
public:
	//アニメーションのキー番号(各値は、実際にmv1に設定されているアニメーションと関連付ける事)
	enum class PlayerBullet_Animation {
		Idle = 0,//待機時
		Move_Forward = 2,//前移動時
		Step_Left = 8,//左ステップ時
		Attack = 11,//攻撃時
		KnockBack = 14,//被弾時
		Down = 15,//ダウン時
		//Jump = 17,//ジャンプ時
		Turn = 11,//回転時
		Animation_Count//利用アニメーション数を数えるための列挙値(Countを状態として利用しないこと)
	};

public:
	PlayerBullet(IWorld* world, const Vector3& position);
	//初期化
	virtual void initialize() override;

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
	void changeAnimation(PlayerBullet_Animation animID, float animSpeed = 1.0f);

private:

	//プレイヤーのアニメーション
	AnimationDx animation_;

};