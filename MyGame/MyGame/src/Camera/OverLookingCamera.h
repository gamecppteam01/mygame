#pragma once
#include"../Actor/Actor.h"

class OverLookingCamera :public Actor {
public:
	OverLookingCamera(IWorld* world = nullptr, const std::string& name = "Camera", const Vector3& position = Vector3::Zero, const IBodyPtr& body = std::make_shared<DummyBody>());

	void setTarget(ActorPtr& target);

	//ターゲットが設定されている場合、初期位置をセットする
	void setFirstPos();


	void ZoomIn(int pointKey,int easeKey);
	void ZoomOut();

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

	void zoom_default(float deltaTime);
	void zoom_in(float deltaTime);
	void zoom_out(float deltaTime);

private:
	//対象から後ろ側に離れる距離(z軸移動)
	float backwardLength_{ 100.0f };
	//対象から上側に離れる距離(y軸移動)
	float upLength_{ 100.0f };
	Vector3 targetVector_{ Vector3{0.0f,-30.0f,-20.0f} };

	int zoomType_{ 0 };
	float timeCount_{ 0.0f };

	std::vector<std::function<void(float)>> zoomFuncList_;

	std::vector<std::function<void()>> easeFuncList_;


	int pointKey_{ 0 };
	int easeKey_{ 0 };

	ActorPtr target_;

	Vector3 prevPosition_;
	Vector3 targetTranslate_;
};