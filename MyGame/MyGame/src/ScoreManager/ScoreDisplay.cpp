#include "ScoreDisplay.h"
#include<iostream>
#include<algorithm>

using namespace std;

ScoreDisplay::ScoreDisplay(ScoreManager* score):scoreManager_(score){
}

ScoreDisplay::~ScoreDisplay()
{
	finalize();
}

void ScoreDisplay::initialize()
{

}

void ScoreDisplay::setScoreManager(ScoreManager * score)
{
	scoreManager_ = score;
}

void ScoreDisplay::finalize()
{
	scoreManager_ = nullptr;
}

void ScoreDisplay::Score()const
{
	std::list<ScoreData> scores;
	scoreManager_->getScoreDataList(scores);
	auto score_less = [](const ScoreData& x, const ScoreData& y) { return x.score_ > y.score_; };
	scores.sort(score_less);
	//for (auto i: scores) {
	//	i.rank_ = static_cast<int>(distance(begin(ScoreData_), lower_bound(begin(ScoreData_), end(ScoreData_), i, score_less))) + 1;
	//}
	//‘¼‚ÌList‚É“ü‚ê‚é
	int a = 1;
	for(auto i: scores){
		FontManager::GetInstance().DrawTextApplyFont(0, 100 + a * 35, GetColor(255, 255, 255), FONT_ID::JAPANESE_FONT, "PLAYER%d:", i.playerNumber_);
		NumberManager::GetInstance().drawT(Vector2(100 , 100 + a * 35), i.score_, 5);
		a++;
	}
}