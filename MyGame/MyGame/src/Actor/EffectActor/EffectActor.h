#pragma once
#include"../Actor.h"

class Effect;

class EffectActor :public Actor {
public:
	//Actorに必要な引数を貰う
	EffectActor(IWorld* world, const std::string& name, const Vector3& position, std::shared_ptr<Effect> effect);
	virtual ~EffectActor(){}
protected:
	// 更新処理
	virtual void onUpdate(float deltaTime);
	// 描画処理
	virtual void onDraw() const;

private:
	//必要に応じて引数を追加
	std::shared_ptr<Effect> effect_;
};