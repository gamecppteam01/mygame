#pragma once
#include"../EffectActor.h"

class TrackingEffectActor :public EffectActor {
public:
	//Actorに必要な引数を貰う
	TrackingEffectActor(IWorld* world, const std::string& name, const Vector3& position, std::shared_ptr<Effect> effect,const ActorPtr& target);

private:
	// 更新処理
	virtual void onUpdate(float deltaTime)override;

	//追跡関数
	void Tracking();
private:
	ActorPtr target_;
};