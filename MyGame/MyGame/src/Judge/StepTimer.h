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
	//�ʒm�Ώۂ�ǉ�����
	void addActor(const ActorPtr& actor);
	//�ΏۃA�N�^�[�ɒʒm����(Notification:�ʒm�̎��)
	void notifyActor(Notification notifyType);
	//�^�C�}�[�̃��Z�b�g
	void restartStepTimer();
	float getStepTimer()const { return stepTimer_; }
	//�W���X�g���蒆���ǂ���
	bool isJustTime()const;
private:
	void update_Count(float deltaTime);
	void update_Just(float deltaTime);

	void to_Count();
	void to_Just();

	void change_State(TimerMode next);
private:
	//�R���{�̃W���X�g���ԃ^�C�}�[
	float stepTimer_;
	//StepTimer���Ď�����A�N�^�[
	std::vector<ActorPtr> actors_;
	//�G�t�F�N�g�����ʒm��
	MethodTimer effectNotifier_;
	//�X�V���
	TimerMode state_;

	std::map<TimerMode, std::function<void(float)>> updateFuncMap_;
};