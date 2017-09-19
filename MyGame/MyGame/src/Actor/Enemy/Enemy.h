#pragma once
#include"../Actor.h"
#include"../../Graphic/Animation.h"

enum class EventMessage;

class Enemy :public Actor {
public:
	Enemy(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body);

private:
	// メッセージ処理
	virtual void onMessage(EventMessage message, void* param);
	// 更新
	virtual void onUpdate(float deltaTime);
	// 描画
	virtual void onDraw() const;
	// 衝突した
	virtual void onCollide(Actor& other);

private:
	//virtual void field() override;

	void checkCollideField();
private:
	//蓄積する移動量を格納する
	Vector3 velocity_;

	float gravity_;

	Animation animation_;
};
