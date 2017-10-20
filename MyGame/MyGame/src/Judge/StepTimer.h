#pragma once

#include"../Actor/ActorPtr.h"
#include<vector>
#include"JudgeDefine.h"

class StepTimer {
public:
	StepTimer();
	~StepTimer();
	void initialize();
	void update(float deltaTime);
	//通知対象を追加する
	void addActor(const ActorPtr& actor);
	//対象アクターに通知する
	void notifyActor();
	float getStepTimer()const { return stepTimer_; }
private:
	//コンボのジャスト時間タイマー
	float stepTimer_;
	//StepTimerを監視するアクター
	std::vector<ActorPtr> actors_;
	
private:
	//ステップの判定間隔
	const float stepInterval{ 5.0f };
};