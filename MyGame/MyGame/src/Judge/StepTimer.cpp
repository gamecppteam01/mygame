#include "StepTimer.h"
#include"../Actor/Actor.h"

StepTimer::StepTimer() :stepTimer_(0.0f), state_(StepTimer::TimerMode::Mode_Count){
	updateFuncMap_[StepTimer::TimerMode::Mode_Count] = [&](float deltaTime) {update_Count(deltaTime); };
	updateFuncMap_[StepTimer::TimerMode::Mode_Just] = [&](float deltaTime) {update_Just(deltaTime); };
}

StepTimer::~StepTimer()
{
	actors_.clear();
}

void StepTimer::initialize() {
	state_ = StepTimer::TimerMode::Mode_Count;
	stepTimer_ = 0.0f;
	actors_.clear();
	effectNotifier_.Initialize();
	effectNotifier_.Add([&] {notifyActor(Notification::Call_CreateJustEffect); });

}

void StepTimer::update(float deltaTime) {
	updateFuncMap_[state_](deltaTime);

}

void StepTimer::addActor(const ActorPtr & actor)
{
	actors_.push_back(actor);
}

void StepTimer::notifyActor(Notification notifyType)
{
	for (auto& a : actors_) {
		a->receiveNotification(notifyType);
	}

}

void StepTimer::restartStepTimer()
{
	stepTimer_ = 0.0f;

	effectNotifier_.Initialize();
	effectNotifier_.Add([&] {notifyActor(Notification::Call_CreateJustEffect); });

}

bool StepTimer::isJustTime() const
{
	return state_ == TimerMode::Mode_Just;
}

void StepTimer::update_Count(float deltaTime)
{
	stepTimer_ += deltaTime;
	//エフェクト生成時間が来たら
	if (stepTimer_ > stepCycle - justEffectStartTime) {
		//エフェクト生成通知を呼び出す
		effectNotifier_.Action();
	}
	if (stepTimer_ < stepCycle)return;
	
	stepTimer_ = 0.0f;
	change_State(TimerMode::Mode_Just);
}

void StepTimer::update_Just(float deltaTime)
{
	stepTimer_ += deltaTime;
	if (stepTimer_ < justTime)return;

	//間隔時間を超えた時はリセット
	restartStepTimer();
	change_State(TimerMode::Mode_Count);

}

void StepTimer::to_Count()
{
}

void StepTimer::to_Just()
{
}

void StepTimer::change_State(TimerMode next)
{
	state_ = next;
	switch (next)
	{
	case StepTimer::TimerMode::Mode_Count:
		to_Count();
		break;
	case StepTimer::TimerMode::Mode_Just:
		to_Just();
		break;
	default:
		break;
	}
}
