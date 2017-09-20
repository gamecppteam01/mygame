#pragma once
#include"../Actor/Actor.h"

class LightActor : public Actor {
public:
	LightActor(IWorld* world = nullptr, const std::string& name = "Light", const Vector3& position = Vector3::Zero, const IBodyPtr& body = std::make_shared<DummyBody>());

private:
	// メッセージ処理
	virtual void onMessage(EventMessage message, void* param);
	// 更新処理
	virtual void onUpdate(float deltaTime);
	// 描画処理
	virtual void onDraw() const;
	// 衝突した時の処理
	virtual void onCollide(Actor& other);
};
