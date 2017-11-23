#include "Enemy_Round.h"
#include"../../../World/IWorld.h"
#include"../../../ScoreManager/ScoreMap.h"
#include"../../../ScoreManager/ScoreManager.h"

Enemy_Round::Enemy_Round(IWorld * world, const std::string & name, const Vector3 & position, int playerNumber):
	BaseEnemy(world,name,position,playerNumber)
{
	points_.clear();
	points_=world_->getCanChangedScoreMap().getEnemy_Round_CrawlPoint();
	setNearestPoint();
}

void Enemy_Round::JustStep()
{
	rhythmTimeCount_++;
	if(rhythmTimeCount_ >= 2) {
		rhythmTimeCount_ = 0;
		nextPosition();
	}

	//ターゲット指定のリセットはとりあえずやる
	nonTargetResetTimer_.Action();
	//ステップ出来るときだけステップする
	if (!isCanStep())return;

	change_State_and_Anim(Enemy_State::Step, stepAnim[0].first);
	world_->getCanChangedScoreManager().addScore(playerNumber_, stepAnim[0].second);


}

void Enemy_Round::to_Normal()
{
	//setNearestPoint();
}

void Enemy_Round::updateNormal(float deltaTime)
{
	Vector3 pos = (nextPosition_ - position_).Normalize()*movePower;
	centerPosition_ += pos;
	if (Vector3::Distance(centerPosition_, nextPosition_) <= 10.0f) nextPosition();
}

void Enemy_Round::setNearestPoint()
{
	nextPosition_ = points_.front();
	nextKey_ = 0;
	int i = 0;
	for (auto& p : points_) {
		if (Vector3::Distance(nextPosition_, position_) > Vector3::Distance(p, position_)) {
			nextPosition_ = p;
			nextKey_ = i;
		}
		i++;
	}
}

void Enemy_Round::nextPosition()
{
	nextKey_ = (nextKey_ - 1+ points_.size()) % points_.size();
	nextPosition_ = points_[nextKey_];


}
