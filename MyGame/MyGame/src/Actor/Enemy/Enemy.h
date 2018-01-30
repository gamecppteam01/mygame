#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationDX.h"


class Enemy :public Actor {
public:
	explicit Enemy(const std::string& name);
	Enemy(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body);
	virtual ~Enemy(){}
private:
	// メッセージ処理
	virtual void onMessage(EventMessage message, void* param);
	// 更新
	virtual void onUpdate(float deltaTime);
	// 描画
	virtual void onDraw() const;
	// 衝突した
	virtual void onCollide(Actor& other);

protected:
	//蓄積する移動量を格納する
	Vector3 velocity_;
	//重力
	float gravity_;
	//3Dモデルアニメーション
	AnimationDx animation_;
};
