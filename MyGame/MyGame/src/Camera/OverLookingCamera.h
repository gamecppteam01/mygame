#pragma once
#include"../Actor/Actor.h"

class OverLookingCamera :public Actor {
public:
	OverLookingCamera(IWorld* world = nullptr, const std::string& name = "Camera", const Vector3& position = Vector3::Zero, const IBodyPtr& body = std::make_shared<DummyBody>());

	void setTarget(ActorPtr& target);

	//ターゲットが設定されている場合、初期位置をセットする
	void setFirstPos();
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
	void cameraMove(float deltaTime);
private:
	ActorPtr target_;

	Vector3 prevPosition_;
	Vector3 targetTranslate_;
};