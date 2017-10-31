#include "ScoreBase.h"
#include"../Actor/Actor.h"
#include"../Actor/Player/Player.h"
#include"../Actor/Enemy/BaseEnemy.h"

ScoreBase::ScoreBase(IWorld* world):world_(world)
{
	Initialize();
}

ScoreBase::~ScoreBase()
{
	scoreList_.clear();
}

void ScoreBase::Initialize()
{
	scoreList_.clear();
	ActorPtr p = world_->findActor("Player");
	if (p != nullptr) {
		std::shared_ptr<Player> player = std::static_pointer_cast<Player>(p);
		scoreList_[player->getPlayerNumber()] = ScoreDataCell(1.0f, 0, player->getPlayerNumber(), p);
	}

	std::list<ActorPtr> enemyList;
	world_->findActors("Enemy", enemyList);
	for (auto& e : enemyList) {
		if (e == nullptr)continue;
		std::shared_ptr<BaseEnemy> enemy = std::static_pointer_cast<BaseEnemy>(e);
		scoreList_[enemy->getPlayerNumber()] = ScoreDataCell(1.0f, 0, enemy->getPlayerNumber(), e);
	}
	
}

void ScoreBase::AddScore(int playerNumber, int score)
{
	scoreList_.at(playerNumber).score_ += score*scoreList_.at(playerNumber).scoreRate_;
}

void ScoreBase::ChangeScoreRate(int playerNumber, float scoreRate)
{
	scoreList_.at(playerNumber).scoreRate_ = scoreRate;
}

//登録されているキャラ数を返す
int ScoreBase::GetCharacterCount() const { return scoreList_.size(); }

//キャラクターのスコアを返す
int ScoreBase::GetCharacterScore(int playerNumber) {
	//キャラが登録されてなかったら0を返す
	if (scoreList_.count(playerNumber) == 0)return 0;
	return scoreList_[playerNumber].score_; 
}

