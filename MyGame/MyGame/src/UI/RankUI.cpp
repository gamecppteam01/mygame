#include "RankUI.h"
#include "../DataManager/DataManager.h"
#include "../Graphic/Sprite.h"
#include"../UI/CutInText.h"

#include<iostream>
#include<algorithm>

static const std::vector<std::vector<SPRITE_ID>> Player_Name{
	{ SPRITE_ID::RANK_PLAYER_SPRITE, SPRITE_ID::RANK_NAME1_SPRITE ,SPRITE_ID::RANK_NAME5_SPRITE ,SPRITE_ID::RANK_NAME14_SPRITE,SPRITE_ID::RANK_NAME2_SPRITE },
	{ SPRITE_ID::RANK_PLAYER_SPRITE, SPRITE_ID::RANK_NAME4_SPRITE ,SPRITE_ID::RANK_NAME6_SPRITE ,SPRITE_ID::RANK_NAME7_SPRITE ,SPRITE_ID::RANK_NAME8_SPRITE ,SPRITE_ID::RANK_NAME3_SPRITE },
	{ SPRITE_ID::RANK_PLAYER_SPRITE, SPRITE_ID::RANK_NAME12_SPRITE,SPRITE_ID::RANK_NAME9_SPRITE ,SPRITE_ID::RANK_NAME11_SPRITE,SPRITE_ID::RANK_NAME10_SPRITE,SPRITE_ID::RANK_NAME13_SPRITE }
};

RankUI::RankUI(ScoreManager * score,RoundCamera* roundCamera ,const Vector2 & position) 
	:UI{ "RankUI",position },score_(score), roundCamera_(roundCamera){
}


void RankUI::initialize(){
	alpha_ = 0.0f;
	start_ = false;
	stage_ = DataManager::GetInstance().getStage();
}

void RankUI::update(float delta_time){
	if (IsStart()) {
		alpha_ = 1.0f;
	}

}

void RankUI::draw() const{
	Score(position_);
}

void RankUI::Score(const Vector2 & position) const{
	std::list<ScoreData*> scores;
	score_->getScoreDataList(scores);
	auto score_less = [](const ScoreData* x, const ScoreData* y) { return x->score_ > y->score_; };
	scores.sort(score_less);
	int a = 1;
	for (auto i : scores) {
		auto spr = Player_Name.at(stage_ - 1).at(i->playerNumber_ - 1);
		if(spr==SPRITE_ID::RANK_PLAYER_SPRITE)CutInText::DrawRank(Vector2(position.x, position.y + a * 40));
		else Sprite::GetInstance().Draw(spr, Vector2(position.x, position.y + a * 40), Vector2(Sprite::GetInstance().GetSize(Player_Name.at(stage_ - 1).at(i->playerNumber_ - 1)))*0.2f / 2,alpha_ ,Vector2(0.2, 0.2));
		Rank_SpriteID(a, Vector2(position.x - 100, position.y + a * 40), 0.18f);
		a++;
	}
}

void RankUI::Rank_SpriteID(const int num, const Vector2 & position, const float size) const
{
	switch (num)
	{
	case 1:
		Sprite::GetInstance().Draw(SPRITE_ID::RANK_ONE_SPRITE, Vector2(position.x, position.y), Sprite::GetInstance().GetSize(SPRITE_ID::RANK_ONE_SPRITE) / 2,alpha_ ,Vector2(size, size));
		break;
	case 2:
		Sprite::GetInstance().Draw(SPRITE_ID::RANK_TWO_SPRITE, Vector2(position.x, position.y), Sprite::GetInstance().GetSize(SPRITE_ID::RANK_TWO_SPRITE) / 2, alpha_ , Vector2(size, size));
		break;
	case 3:
		Sprite::GetInstance().Draw(SPRITE_ID::RANK_THREE_SPRITE, Vector2(position.x, position.y), Sprite::GetInstance().GetSize(SPRITE_ID::RANK_THREE_SPRITE) / 2, alpha_ , Vector2(size, size));
		break;
	default:
		break;
	}
}

bool RankUI::IsStart()const
{
	return roundCamera_->isEnd();
}
