#include "NormalEnemy.h"
#include"../../World/IWorld.h"
#include"../../ScoreManager/ScoreManager.h"
#include"../../ScoreManager/ScoreMap.h"
#include"../../Actor/Player/Player.h"
#include"../../Math/Random.h"

NormalEnemy::NormalEnemy(IWorld * world, const std::string & name, const Vector3 & position,int playerNumber, const IBodyPtr & body):
	BaseEnemy(world,name,position,playerNumber,body), nextPoint_(0), nextPosition_(position), isGoBonus_(false){

	roundPoint_ = world_->getCanChangedScoreMap().getRoundPoint();
	nextPoint_ = getNearestPoint(position_);

	player_ = std::static_pointer_cast<Player>(world_->findActor("Player"));

}

void NormalEnemy::JustStep()
{
	nonTargetResetTimer_.Action();
	if (!isCanStep())return;

	ActorPtr act = getNearestActor();
	//攻撃射程圏内なら
	if (Vector2::Distance(Vector2(getNearestActor()->position().x, getNearestActor()->position().z), Vector2(position_.x, position_.z)) <= attackDistance&&
		prevHitActorNumber_ != act->getCharacterNumber()) {
		change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Idle);
		return;
	}
	//通常時は6拍子毎
	int rhythmTime = 6;
	if (world_->getScoreManager().GetCharacterScoreRate(playerNumber_) > 1.0f) {
		//ボーナス時は3拍子毎
		rhythmTime = 3;
	}

	rhythmTimeCount_++;
	if (rhythmTimeCount_ < rhythmTime) {
		if (isGoBonus_) {
			setNextPosition();
		}
		return;
	}
	//if (Random::GetInstance().Range(1, 100) <= 50)return;

	rhythmTimeCount_ = 0;

	std::vector<int> stepAnim{
		(int)Enemy_Animation::KnockBack,
		(int)Enemy_Animation::Move_Forward,
		(int)Enemy_Animation::Step_Left,
		(int)Enemy_Animation::Turn
	};

	int r = Random::GetInstance().Range(0, 9);
	if (r < 3) {
		//ターン
		world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_TURN);
	}
	else {
		//クォーター
		world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_QUARTER);

	}
	change_State_and_Anim(Enemy_State::Step, Enemy_Animation::Move_Forward);

}

void NormalEnemy::updateNormal(float deltaTime)
{
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);
	
	if (Vector3::Distance(position_, player_.lock()->position()) <= 30.0f&&world_->getScoreManager().GetCharacterScoreRate(player_.lock()->getPlayerNumber()) >= 1.05f) {
		if (change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Turn))updateAttack(deltaTime);
		return;
	}

	velocity_ += (nextPosition_ - position_).Normalize()*movePower;
	gravity_ -= 0.05f;

	Vector3 jumpVector = Vector3(0.0f, gravity_, 0.0f);
	velocity_ += jumpVector;

	Vector2 myPos = Vector2(position_.x, position_.z);
	Vector2 pointPos = Vector2(nextPosition_.x, nextPosition_.z);

	//ポイントに到達したら
	if (Vector2::Distance(myPos, pointPos) <= 10.0f&&!isGoBonus_) {
		setNextPosition();
	}
}

void NormalEnemy::to_Normal()
{
	nextPoint_ = getNearestPoint(position_);
	nextPosition_ = roundPoint_[nextPoint_];
	isGoBonus_ = false;
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

void NormalEnemy::setNextPosition()
{
	//ターゲットカウントを-1する
	nextPoint_=(nextPoint_+roundPoint_.size()-1)%roundPoint_.size();
	
	float rate = 1.0f;
	Vector3 nextPosition = world_->getCanChangedScoreMap().getNextPoint(position_, &rate);
	if (rate >= 1.05f) {
		isGoBonus_ = true;
		nextPosition_ = nextPosition +Vector3(Random::GetInstance().Range(-20.f, 20.f), 0.0f, Random::GetInstance().Range(-20.f, 20.f));
		return;
	}
	nextPosition_ = roundPoint_[nextPoint_];

}
