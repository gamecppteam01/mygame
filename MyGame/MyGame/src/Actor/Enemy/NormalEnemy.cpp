#include "NormalEnemy.h"
#include"../../World/IWorld.h"
#include"../../ScoreManager/ScoreManager.h"
#include"../../ScoreManager/ScoreMap.h"
#include"../../Actor/Player/Player.h"
#include"../../Math/Random.h"

NormalEnemy::NormalEnemy(IWorld * world, const std::string & name, const Vector3 & position,int playerNumber, const IBodyPtr & body):
	BaseEnemy(world,name,position,playerNumber,body), nextPoint_(0){

	roundPoint_ = world_->getCanChangedScoreMap().getRoundPoint();
	nextPoint_ = getNearestPoint(position_);
}

void NormalEnemy::JustStep()
{
	//通常時は6拍子毎
	int rhythmTime = 6;
	if (world_->getScoreManager().GetCharacterScoreRate(playerNumber_) > 1.0f) {
		//ボーナス時は3拍子毎
		rhythmTime = 3;
	}

	rhythmTimeCount_++;
	if (rhythmTimeCount_ < rhythmTime)return;
	//if (Random::GetInstance().Range(1, 100) <= 50)return;

	rhythmTimeCount_ = 0;

	std::vector<int> stepAnim{
		(int)Enemy_Animation::KnockBack,
		(int)Enemy_Animation::Move_Forward,
		(int)Enemy_Animation::Step_Left,
		(int)Enemy_Animation::Turn
	};

	//攻撃射程圏内なら
	if (Vector3::Distance(getNearestActor()->position(), position_) <= attackDistance) {
		change_State_and_Anim(Enemy_State::Attack,Enemy_Animation::Idle);
		return;
	}
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

void NormalEnemy::updateNormal(float deltaTime)
{
	std::shared_ptr<Player> player = std::static_pointer_cast<Player>(world_->findActor("Player"));
	if (Vector3::Distance(position_, player->position()) <= 30.0f&&world_->getScoreManager().GetCharacterScoreRate(player->getPlayerNumber()) >= 1.05f) {
		if (change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Turn))updateAttack(deltaTime);
		return;
	}

	float rate = 1.0f;
	Vector3 nextPosition = world_->getCanChangedScoreMap().getNextPoint(position_, &rate);

	if (rate > 1.05f) {
		velocity_ += (nextPosition - position_).Normalize()*movePower;
	}
	else {
		velocity_ += (roundPoint_[nextPoint_] - position_).Normalize()*movePower;
	}
	gravity_ -= 0.05f;

	Vector3 jumpVector = Vector3(0.0f, gravity_, 0.0f);
	velocity_ += jumpVector;

	Vector2 myPos = Vector2(position_.x, position_.z);
	Vector2 pointPos = Vector2(roundPoint_[nextPoint_].x, roundPoint_[nextPoint_].z);

	//ポイントに到達したら
	if (Vector2::Distance(myPos, pointPos) <= 10.0f) {
		nextPoint_=(nextPoint_+1)% roundPoint_.size();
	}
}

void NormalEnemy::to_Normal()
{
	nextPoint_ = getNearestPoint(position_);
}

int NormalEnemy::getNearestPoint(const Vector3 & position)
{
	int result = 0;
	for (int i = 0; i < roundPoint_.size(); i++) {
		//対象ポイントが現在のポイントより近ければ
		if (Vector3::Distance(position, roundPoint_[result]) > Vector3::Distance(position, roundPoint_[i])) {
			//ポイントを更新
			result = i;
		}
	}
	return result;
}
