#include "BetweenPositionActor.h"

BetweenPositionActor::BetweenPositionActor() :
	Actor("Point")
{
}

void BetweenPositionActor::addTarget(ActorPtr target)
{
	targets_.push_back(target);

	Vector3 result=Vector3::Zero;
	for (auto& i : targets_) {
		result = i->position();
	}
	result /= targets_.size();

	position_ = result;
}

float BetweenPositionActor::getDistance() const
{
	if (targets_.size() == 0)return 0;

	float result = 0;
	for (int i = 0; i < targets_.size(); i++) {
		int next = (i + 1)%targets_.size();
		result += Vector3::Distance(targets_[i]->position(),targets_[next]->position());
	}
	result /= targets_.size();
	return result;
}

void BetweenPositionActor::onUpdate(float deltaTime)
{
	Vector3 result = Vector3::Zero;
	for (auto& i : targets_) {
		result = i->position();
	}
	result /= targets_.size();

	position_ = result;

}
