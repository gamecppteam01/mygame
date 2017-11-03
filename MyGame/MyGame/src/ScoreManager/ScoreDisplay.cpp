#include "ScoreDisplay.h"
#include<iostream>
#include<algorithm>

using namespace std;

ScoreDisplay::ScoreDisplay(ScoreManager* scoreManager){
	scoreManager_ = scoreManager;
	Score();
}

ScoreDisplay::~ScoreDisplay()
{
}

void ScoreDisplay::initialize()
{

}

void ScoreDisplay::Score()
{
	scoreManager_->getScoreDataList(ScoreData_);
	auto score_less = [](const ScoreData& x, const ScoreData& y) { return x.score_ > y.score_; };
	ScoreData_.sort(score_less);
	for (auto i:ScoreData_) {
		i.rank_ = static_cast<int>(distance(begin(ScoreData_), lower_bound(begin(ScoreData_), end(ScoreData_), i, score_less))) + 1;
	}
	//‘¼‚ÌList‚É“ü‚ê‚é
	int a = 1;
	for(auto i:ScoreData_){
		FontManager::GetInstance().DrawTextApplyFont(0, 100 + a * 35, GetColor(255, 255, 255), FONT_ID::JAPANESE_FONT, "PLAYER%d:", i.playerNumber_);
		NumberManager::GetInstance().drawT(Vector2(100 , 100 + a * 35), i.score_, 5);
		a++;
	}
}