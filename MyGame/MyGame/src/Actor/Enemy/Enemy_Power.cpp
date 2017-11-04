#include "Enemy_Power.h"
#include"../../World/IWorld.h"
#include"../../ScoreManager/ScoreMap.h"
#include"../../Math/MathHelperSupport.h"
#include"../../Math/Random.h"
#include"../../ScoreManager/ScoreManager.h"

Enemy_Power::Enemy_Power(IWorld * world, const std::string & name, const Vector3 & position, int playerNumber, const IBodyPtr & body) :
	BaseEnemy(world, name, position, playerNumber, body){

	targetPos_ = world_->getCanChangedScoreMap().getNearestBonusPoint(position_);

	world_->findActors("Enemy", players_);

	//playersから自身を削除
	players_.remove_if([&](ActorPtr& ptr)->bool {
		return ptr->getCharacterNumber() == getCharacterNumber();
	});
	players_.push_front(world_->findActor("Player"));

}

void Enemy_Power::JustStep() {
	rhythmTimeCount_++;

	targetPos_ = world_->getCanChangedScoreMap().getNearestBonusPoint(position_);

	bool isAttack = false;
	float nearest = Vector3::Distance(position_, players_.front()->position());
	for (const auto& p : players_) {
		//範囲内に選手がいなければ次へ
		if (MathHelperSupport::MathDistance_Segment_Point(position_, targetPos_, p->position()) > attackDistance)continue;
		float dist = Vector3::Distance(position_, p->position());
		if (dist <= nearest&&prevHitActorNumber_ != p->getCharacterNumber()) {
			nearest = dist;
			attackTarget_ = p;
			prevHitActorNumber_ = attackTarget_->getCharacterNumber();
			isAttack = true;
		}
	}
	if (isAttack) {
		change_State_and_Anim(Enemy_State::Attack, stepAnim[1].first);
		return;
	}
	//通常時は3拍子毎
	int rhythmTime = 3;
	if (rhythmTimeCount_ < rhythmTime)return;
	rhythmTimeCount_ = 0;

	//ボーナス時は3拍子毎

	int r = Random::GetInstance().Range(0, 9);
	if (r < 3) {
		//ターン
		world_->getCanChangedScoreManager().addScore(playerNumber_, 200);
	}
	else {
		//クォーター
		world_->getCanChangedScoreManager().addScore(playerNumber_, 100);

	}
	change_State_and_Anim(Enemy_State::Step, Enemy_Animation::Move_Forward);

}


void Enemy_Power::updateNormal(float deltaTime)
{
	position_ += (targetPos_ - position_).Normalize()*movePower;
	
	
}

void Enemy_Power::to_Normal()
{
	targetPos_ = world_->getCanChangedScoreMap().getNearestBonusPoint(position_);

}

void Enemy_Power::to_Attack(BaseEnemy::Enemy_Animation anim)
{
	stepTime_ = 1.5f;

}
