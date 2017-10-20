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
	//�ʒm�Ώۂ�ǉ�����
	void addActor(const ActorPtr& actor);
	//�ΏۃA�N�^�[�ɒʒm����
	void notifyActor();
	float getStepTimer()const { return stepTimer_; }
private:
	//�R���{�̃W���X�g���ԃ^�C�}�[
	float stepTimer_;
	//StepTimer���Ď�����A�N�^�[
	std::vector<ActorPtr> actors_;
	
private:
	//�X�e�b�v�̔���Ԋu
	const float stepInterval{ 5.0f };
};