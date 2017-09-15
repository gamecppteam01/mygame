#pragma once
#include"Actor.h"

enum class EventMessage;

class ActorTemplate :public Actor {
public:
	//Actorに必要な引数を貰う
	ActorTemplate(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body);

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
	//必要に応じて引数を追加

};