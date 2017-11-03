#pragma once
#include<memory>
#include"../Actor/Actor.h"
//スコア情報一括管理構造体
struct ScoreData {
	ScoreData() {

	}
	ScoreData(int score, int playerNumber, float rate, int rank, const ActorPtr& target) {
		score_ = score;
		playerNumber_ = playerNumber;
		scoreRate_ = rate;
		rank_ = rank;
		target_ = target;
	}
	//スコア倍率
	float scoreRate_;
	//得点
	int score_;
	//対象の出場番号
	int playerNumber_;
	//ランク
	int rank_;
	//対象
	std::weak_ptr<Actor> target_;
};