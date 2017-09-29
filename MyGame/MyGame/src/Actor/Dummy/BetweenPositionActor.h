#pragma once

#include"../Actor.h"

//n点間の中心のポイントに位置するアクター
class BetweenPositionActor:public Actor {
public:
	BetweenPositionActor();
	void addTarget(ActorPtr target);

	float getDistance()const;
private:
	void onUpdate(float deltaTime)override;
private:
	std::vector<ActorPtr> targets_;

};