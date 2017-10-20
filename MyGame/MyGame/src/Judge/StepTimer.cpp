#include "StepTimer.h"
#include"../Actor/Actor.h"

StepTimer::StepTimer() :stepTimer_(0.0f) {
}

StepTimer::~StepTimer()
{
	actors_.clear();
}

void StepTimer::initialize() {
	stepTimer_ = 0.0f;
	actors_.clear();
}

void StepTimer::update(float deltaTime) {
	stepTimer_ += deltaTime;

	if (stepInterval < 5.0f)return;
	//ŠÔŠuŽžŠÔ‚ð’´‚¦‚½Žž‚Ì‚Ý‰º‚Ìˆ—‚ðs‚¤
	stepTimer_ = 0.0f;

	notifyActor();
}

void StepTimer::addActor(const ActorPtr & actor)
{
	actors_.push_back(actor);
}

void StepTimer::notifyActor()
{
	for (auto& a : actors_) {
		a->receiveNotification(Notification::Call_JustStep);
	}

}
