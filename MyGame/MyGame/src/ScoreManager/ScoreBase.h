#pragma once

#include"../Actor/ActorPtr.h"
#include"../World/IWorld.h"
#include<map>

//�X�R�A���ꊇ�Ǘ��\����
struct ScoreData {
	ScoreData() {

	}
	ScoreData(float rate, int score, int playerNumber,const ActorPtr& target):
		scoreRate_(rate), score_(score), playerNumber_(playerNumber), target_(target) {

	}
	//�X�R�A�{��
	float scoreRate_;
	//���_
	int score_;
	//�Ώۂ̏o��ԍ�
	int playerNumber_;
	//�Ώ�
	std::weak_ptr<Actor> target_;
};

class ScoreBase {
public:
	ScoreBase(IWorld* world);
	~ScoreBase();
	void Initialize();
	//�X�R�A���Z
	void AddScore(int playerNumber,int score);
	//�X�R�A�{����ύX����
	void ChangeScoreRate(int playerNumber, float scoreRate);
private:
	std::map<int,ScoreData> scoreList_;

	IWorld* world_;
};