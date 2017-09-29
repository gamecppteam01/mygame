#pragma once

#include"../Actor.h"

//n�_�Ԃ̒��S�̃|�C���g�Ɉʒu����A�N�^�[
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