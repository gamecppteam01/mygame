#include "Enemy_Notice.h"
#include"../../../World/IWorld.h"
#include"../../../ScoreManager/ScoreManager.h"
#include"../../../ScoreManager/ScoreMap.h"
#include"../../../Actor/Player/Player.h"
#include"../../../Math/Random.h"
#include"../../../Sound/TempoManager.h"
#include"../EnemyBullet.h"

Enemy_Notice::Enemy_Notice():
	BaseEnemy("Enemy")
{
}

Enemy_Notice::Enemy_Notice(IWorld * world, const std::string & name, const Vector3 & position, int playerNumber, const IBodyPtr & body)
	: BaseEnemy(world, name, position, playerNumber, body, MODEL_ID::NOTICEENEMY_MODEL, MODEL_ID::NOTICEENEMY_BULLET_MODEL), nextPoint_(0), nextPosition_(position), isGoBonus_(false) {
	roundPoint_ = world_->getCanChangedScoreMap().getRoundPoint();
	nextPoint_ = getNearestPoint(centerPosition_);
	state_ = Notice_State::Normal;
}

std::shared_ptr<BaseEnemy> Enemy_Notice::Create(IWorld * world, const Vector3 & position, int playerNumber)
{
	return std::make_shared<Enemy_Notice>(world, "Enemy", position, playerNumber);
}

void Enemy_Notice::onMessage(EventMessage message, void * param) {
	switch (message)
	{
	case EventMessage::Lighting:
		state_ = Notice_State::Steal;
		nextPosition_ = (Vector3&)param;
		lightPosition_ = nextPosition_;
		changeFlag_ = false;
		break;
	case EventMessage::Extinction:
		state_ = Notice_State::Normal;
		changeFlag_ = true;
		break;
	}
}

void Enemy_Notice::JustStep() {
	nonTargetResetTimer_.Action();
	if (!isCanStep())return;

	ActorPtr act = getNearestActor();
	//攻撃射程圏内なら
	if (Vector2::Distance(Vector2(getNearestActor()->position().x, getNearestActor()->position().z), Vector2(centerPosition_.x, centerPosition_.z)) <= attackDistance&&
		prevHitActorNumber_ != act->getCharacterNumber()) {
		change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Spin);
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
		if (isGoBonus_ && state_ == Notice_State::Normal) {
			setNextPosition();
		}
		return;
	}

	rhythmTimeCount_ = 0;
	if (state_ != Notice_State::Normal) return;
	int r = Random::GetInstance().Range(0, 9);
	if (r < probability_) {
		//ターン
		world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_TURN);
		change_State_and_Anim(Enemy_State::Step, Enemy_Animation::Turn, false);
	}
	else {
		//クォーター
		world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_QUARTER);
		change_State_and_Anim(Enemy_State::Step, Enemy_Animation::Quarter, false);
	}
}

void Enemy_Notice::updateNormal(float deltaTime) {
	//3拍目は動かない
	if (world_->getCanChangedTempoManager().getBeatCount() % 3 == 2)return;

	data_ = world_->getCanChangedScoreManager().getScoreData(playerNumber_);

	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);

	velocity_ += (nextPosition_ - centerPosition_).Normalize()*movePower;
	gravity_ -= 0.05f;

	Vector3 jumpVector = Vector3(0.0f, gravity_, 0.0f);
	velocity_ += jumpVector;

	Vector2 myPos;
	Vector2 pointPos;
	switch (state_)
	{
	case Enemy_Notice::Normal:
		myPos = Vector2(centerPosition_.x, centerPosition_.z);
		pointPos = Vector2(nextPosition_.x, nextPosition_.z);

		//ポイントに到達したら
		if (Vector2::Distance(myPos, pointPos) <= 10.0f && !isGoBonus_) {
			setNextPosition();
		}
		break;
	case Enemy_Notice::Steal:
		if (data_->notice_ == true) {
			world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_TURN);
			change_State_and_Anim(Enemy_State::Fever, Enemy_Animation::Turn, false);
		}
		break;
	}
}

void Enemy_Notice::updateFever(float deltaTime) {

	int r = Random::GetInstance().Range(0, 9);
	if (animation_.IsAnimEnd() == true) {
		if (r < probability_ && stepFlag_ == false) {
			//ターン
			world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_TURN);
			changeAnimation(Enemy_Animation::Turn, 0.0f, 1.0f, false);
			stepFlag_ = true;
			OutputDebugString("TURN\n");
		}
		else if(stepFlag_ == false){
			//クォーター
			world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_QUARTER);
			changeAnimation(Enemy_Animation::Quarter, 0.0f, 1.0f, false);
			stepFlag_ = true;
			OutputDebugString("QUARTER\n");
		}
	}
	if (animation_.IsAnimEnd() == true && stepFlag_ == true && changeFlag_ == false) {
		changeAnimation(Enemy_Animation::Idle, 0.0f, 1.0f, false);
		OutputDebugString("IDLE\n");
		rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);
		stepFlag_ = false;
	}
	if (animation_.IsAnimEnd() == true && changeFlag_ == true) {
		change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Idle, true);
		setNextPosition();
	}
}

void Enemy_Notice::to_Normal() {
	switch (state_)
	{
	case Enemy_Notice::Normal:
		nextPoint_ = getNearestPoint(centerPosition_);
		nextPosition_ = roundPoint_[nextPoint_];
		isGoBonus_ = false;
		probability_ = 3;
		break;
	case Enemy_Notice::Steal:
		nextPosition_ = lightPosition_;
		break;
	}
}

void Enemy_Notice::to_Fever() {
	probability_ = 3;
}

int Enemy_Notice::getNearestPoint(const Vector3 & position) {
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

void Enemy_Notice::setNextPosition() {
	//ターゲットカウントを-1する
	nextPoint_ = (nextPoint_ + roundPoint_.size() - 1) % roundPoint_.size();

	float rate = 1.0f;
	Vector3 nextPosition = world_->getCanChangedScoreMap().getNextPoint(centerPosition_, &rate);
	if (rate >= 1.05f) {
		isGoBonus_ = true;
		nextPosition_ = nextPosition + Vector3(Random::GetInstance().Range(-20.f, 20.f), 0.0f, Random::GetInstance().Range(-20.f, 20.f));
		return;
	}
	nextPosition_ = roundPoint_[nextPoint_];
}
