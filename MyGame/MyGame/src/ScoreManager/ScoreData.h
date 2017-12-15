#pragma once
#include<memory>
#include"../Actor/Actor.h"
//�X�R�A���ꊇ�Ǘ��\����
struct ScoreData {
	ScoreData() {

	}
	ScoreData(int score, int playerNumber, float rate, int rank, const ActorPtr& target) {
		score_ = score;
		playerNumber_ = playerNumber;
		scoreRate_ = rate;
		rank_ = rank;
		time_ = 0.0f;
		notice_ = false;
		target_ = target;
	}
	//�X�R�A�{��
	float scoreRate_;
	//���_
	int score_;
	//�Ώۂ̏o��ԍ�
	int playerNumber_;
	//�����N
	int rank_;
	//����
	float time_;
	//���ڃt���O
	bool notice_;
	//�Ώ�
	std::weak_ptr<Actor> target_;
};