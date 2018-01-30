#pragma once

#include"../Actor/ActorPtr.h"
#include"../World/IWorld.h"
#include<map>

//スコア情報一括管理構造体
struct ScoreDataCell {
	ScoreDataCell() {

	}
	ScoreDataCell(float rate, int score, int playerNumber,const ActorPtr& target):
		scoreRate_(rate), score_(score), playerNumber_(playerNumber), target_(target) {

	}
	//スコア倍率
	float scoreRate_;
	//得点
	int score_;
	//対象の出場番号
	int playerNumber_;
	//対象
	std::weak_ptr<Actor> target_;
};

class ScoreBase {
public:
	explicit ScoreBase(IWorld* world);
	~ScoreBase();
	void Initialize();
	//スコア加算
	void AddScore(int playerNumber,int score);
	//スコア倍率を変更する
	void ChangeScoreRate(int playerNumber, float scoreRate);
	//登録されているキャラ数を返す
	int GetCharacterCount()const;
	//キャラクターのスコアを返す
	int GetCharacterScore(int playerNumber);
private:
	std::map<int,ScoreDataCell> scoreList_;

	IWorld* world_;
};