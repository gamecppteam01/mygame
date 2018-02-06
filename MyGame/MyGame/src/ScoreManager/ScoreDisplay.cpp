#include "ScoreDisplay.h"
#include "../DataManager/DataManager.h"
#include "../Graphic/Sprite.h"
#include<iostream>
#include<algorithm>

using namespace std;

static const std::vector<std::vector<SPRITE_ID>> Player_Name{
	{ SPRITE_ID::RANK_PLAYER_SPRITE, SPRITE_ID::RANK_NAME1_SPRITE ,SPRITE_ID::RANK_NAME5_SPRITE ,SPRITE_ID::RANK_NAME14_SPRITE,SPRITE_ID::RANK_NAME2_SPRITE },
	{ SPRITE_ID::RANK_PLAYER_SPRITE, SPRITE_ID::RANK_NAME4_SPRITE ,SPRITE_ID::RANK_NAME6_SPRITE ,SPRITE_ID::RANK_NAME7_SPRITE ,SPRITE_ID::RANK_NAME8_SPRITE ,SPRITE_ID::RANK_NAME3_SPRITE },
	{ SPRITE_ID::RANK_PLAYER_SPRITE, SPRITE_ID::RANK_NAME12_SPRITE,SPRITE_ID::RANK_NAME9_SPRITE ,SPRITE_ID::RANK_NAME11_SPRITE,SPRITE_ID::RANK_NAME10_SPRITE,SPRITE_ID::RANK_NAME13_SPRITE }
};

ScoreDisplay::ScoreDisplay(ScoreManager* score):scoreManager_(score){
}

ScoreDisplay::~ScoreDisplay()
{
	finalize();
}

void ScoreDisplay::initialize()
{
	stage_ = DataManager::GetInstance().getStage();
}

void ScoreDisplay::setScoreManager(ScoreManager * score)
{
	scoreManager_ = score;
}

void ScoreDisplay::finalize()
{
	scoreManager_ = nullptr;
}

void ScoreDisplay::Score(const Vector2& position, int digit)const
{
	std::list<ScoreData*> scores;
	scoreManager_->getScoreDataList(scores);
	auto score_less = [](const ScoreData* x, const ScoreData* y) { return x->score_ > y->score_; };
	scores.sort(score_less);
	//for (auto i: scores) {
	//	i.rank_ = static_cast<int>(distance(begin(ScoreData_), lower_bound(begin(ScoreData_), end(ScoreData_), i, score_less))) + 1;
	//}
	//‘¼‚ÌList‚É“ü‚ê‚é
	int a = 1;
	for(auto i: scores){
		Sprite::GetInstance().Draw(Player_Name.at(stage_ - 1).at(i->playerNumber_ - 1), Vector2(position.x, position.y + a * 40), Sprite::GetInstance().GetSize(Player_Name.at(stage_ - 1).at(i->playerNumber_ - 1)) / 2, Vector2(0.2, 0.2));
		Rank_SpriteID(a,Vector2(position.x - 100,position.y + a * 40),0.18f);
		//FontManager::GetInstance().DrawTextApplyFont(position.x, position.y + a * 40, GetColor(255, 255, 255), FONT_ID::DEFAULT_FONT, "PLAYER%d:", i->playerNumber_);
		//NumberManager::GetInstance().DrawNumber_digit(Vector2(position.x + 30 + 22.5 * digit, position.y + a * 40), i->score_ , digit);
		a++;
	}
}

void ScoreDisplay::Score(const std::list<ScoreData>& score,const Vector2& position,int digit)
{
	std::list<ScoreData> scores = score;
	auto score_less = [](const ScoreData& x, const ScoreData& y) { return x.score_ > y.score_; };
	scores.sort(score_less);
	//for (auto i: scores) {
	//	i.rank_ = static_cast<int>(distance(begin(ScoreData_), lower_bound(begin(ScoreData_), end(ScoreData_), i, score_less))) + 1;
	//}
	//‘¼‚ÌList‚É“ü‚ê‚é
	int a = 1;
	for (auto i : scores) {
		FontManager::GetInstance().DrawTextApplyFont(position.x, position.y + a * 35, GetColor(255, 255, 255), FONT_ID::DEFAULT_FONT, "PLAYER%d:", i.playerNumber_);
		NumberManager::GetInstance().DrawNumber_digit(Vector2(position.x + 30 + 22.5 * digit, position.y + a * 35), i.score_, digit);
		a++;
	}

}

void ScoreDisplay::Rank_SpriteID(const int num, const Vector2& position, const float size)const{
	switch (num)
	{
	case 1:
		Sprite::GetInstance().Draw(SPRITE_ID::RANK_ONE_SPRITE, Vector2(position.x, position.y), Sprite::GetInstance().GetSize(SPRITE_ID::RANK_ONE_SPRITE) / 2, Vector2(size,size));
		break;
	case 2:
		Sprite::GetInstance().Draw(SPRITE_ID::RANK_TWO_SPRITE, Vector2(position.x, position.y), Sprite::GetInstance().GetSize(SPRITE_ID::RANK_TWO_SPRITE) / 2, Vector2(size, size));
		break;
	case 3:
		Sprite::GetInstance().Draw(SPRITE_ID::RANK_THREE_SPRITE, Vector2(position.x, position.y), Sprite::GetInstance().GetSize(SPRITE_ID::RANK_THREE_SPRITE) / 2, Vector2(size, size));
		break;
	default:
		break;
	}
}
