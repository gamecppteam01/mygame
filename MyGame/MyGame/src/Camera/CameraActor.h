#pragma once
#include"../Actor/Actor.h"

class CameraActor :public Actor {
public:
	CameraActor(IWorld* world=nullptr, const std::string& name="Camera", const Vector3& position=Vector3::Zero, const IBodyPtr& body = std::make_shared<DummyBody>());

	void setTarget(ActorPtr& target);

private:
	// メッセージ処理
	virtual void onMessage(EventMessage message, void* param);
	// 更新処理
	virtual void onUpdate(float deltaTime);
	// 描画処理
	virtual void onDraw() const;
	// 衝突した時の処理
	virtual void onCollide(Actor& other);

private:
	ActorPtr target_;
};