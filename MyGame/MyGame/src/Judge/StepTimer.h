#pragma once

#include"../Actor/ActorPtr.h"
#include<vector>
#include<map>
#include"JudgeDefine.h"
#include"../Method/MethodTimer.h"
#include"../Game/ID.h"
#include <functional>

class StepTimer {
private:
	enum class TimerMode {
		Mode_Count,
		Mode_Just
	};
public:
	StepTimer();
	~StepTimer();
	void initialize();
	void update(float deltaTime);
	//通知対象を追加する
	void addActor(const ActorPtr& actor);
	//対象アクターに通知する(Notification:通知の種類)
	void notifyActor(Notification notifyType);
	//タイマーのリセット
	void restartStepTimer();
	float getStepTimer()const { return stepTimer_; }
	//ジャスト判定中かどうか
	bool isJustTime()const;
private:
	void update_Count(float deltaTime);
	void update_Just(float deltaTime);

	void to_Count();
	void to_Just();

	void change_State(TimerMode next);
private:
	//コンボのジャスト時間タイマー
	float stepTimer_;
	//StepTimerを監視するアクター
	std::vector<ActorPtr> actors_;
	//エフェクト生成通知者
	MethodTimer effectNotifier_;
	//更新状態
	TimerMode state_;

	std::map<TimerMode, std::function<void(float)>> updateFuncMap_;
};