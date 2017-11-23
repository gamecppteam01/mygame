#pragma once
#include"Enemy.h"
#include"../Body/BoundingCapsule.h"

class BaseEnemy;
class EnemyBullet :public Enemy {
	friend class BaseEnemy;
public:
	//アニメーションのキー番号(各値は、実際にmv1に設定されているアニメーションと関連付ける事)
	enum class EnemyBullet_Animation {
		Move_Forward = 0,//前移動時
		Idle = 0,//待機時
		Step_Left = 2,//左ステップ時
		Turn = 3,//回転時
		KnockBack = 4,//被弾時
		Down = 5,//ダウン時
	    //Jump = 17,//ジャンプ時
	};
public:
	//カプセル判定は例、キャラクターの体型に応じて設定を変更する事
	EnemyBullet(IWorld* world, const std::string& name, const Vector3& position, BaseEnemy* enemy,MODEL_ID id, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));

	void hitOther(const Vector3& bound);
private:
	// メッセージ処理
	virtual void onMessage(EventMessage message, void* param) override;
	// 更新
	virtual void onUpdate(float deltaTime)override;
	// 描画
	virtual void onDraw() const override;
	// 衝突した
	virtual void onCollide(Actor& other) override;

	Vector3 mathBound(Actor & other);

	//ベース用
private:

	Vector3* getPositionPtr();
	Matrix* getRotationPtr();
	//アニメーションの変更
	void changeAnimation(EnemyBullet_Animation animID);

private:
	//アニメーション
	AnimationDx animation_;
	BaseEnemy* enemy_;
};