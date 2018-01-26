#include "Enemy_Notice.h"
#include"../../../World/IWorld.h"
#include"../../../ScoreManager/ScoreManager.h"
#include"../../../ScoreManager/ScoreMap.h"
#include"../../../Actor/Player/Player.h"
#include"../../../Math/Random.h"
#include"../../../Sound/TempoManager.h"
#include"../EnemyBullet.h"
#include"../../../DataManager/DataManager.h"

//1キャラ当たりのサイズ
static float charaPos{ 20.0f };

Enemy_Notice::Enemy_Notice():
	BaseEnemy("Enemy")
{
}

Enemy_Notice::Enemy_Notice(IWorld * world, const std::string & name, const Vector3 & position, int playerNumber, const IBodyPtr & body)
	: BaseEnemy(world, name, position, playerNumber, body, MODEL_ID::NOTICEENEMY_MODEL, MODEL_ID::NOTICEENEMY_BULLET_MODEL), nextPoint_(0), nextPosition_(position), isGoBonus_(false) {
	roundPoint_ = world_->getCanChangedScoreMap().getRoundPoint();
	nextPoint_ = getNearestPoint(centerPosition_);
	//最初のステート
	state_ = Notice_State::Normal;
	charaPos_ = charaPos;
	downCount_ = 10;
}

std::shared_ptr<BaseEnemy> Enemy_Notice::Create(IWorld * world, const Vector3 & position, int playerNumber)
{
	return std::make_shared<Enemy_Notice>(world, "Enemy", position, playerNumber);
}

void Enemy_Notice::onMessage(EventMessage message, void * param) {
	switch (message)
	{
	//ライトが光っていたら
	case EventMessage::Lighting:
		state_ = Notice_State::Steal;
		nextPosition_ = (Vector3&)param;
		lightPosition_ = nextPosition_;
		changeFlag_ = false;
		break;
	//ライトが消えていたら
	case EventMessage::Extinction:
		state_ = Notice_State::Normal;
		changeFlag_ = true;
		break;
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

	Vector2 pointPos;
	Vector2 myPos;
	Vector2 lightPos;
	switch (state_)
	{
		//巡回
	case Enemy_Notice::Normal:
		myPos = Vector2(centerPosition_.x, centerPosition_.z);
		pointPos = Vector2(nextPosition_.x, nextPosition_.z);
		lightPos = Vector2(lightPosition_.x, lightPosition_.z);
		//ポイントに到達したら
		if (Vector2::Distance(myPos, pointPos) <= 10.0f && !isGoBonus_) {
			setNextPosition();
		}
		break;
		//ライトを狙う
	case Enemy_Notice::Steal:
		lightFlag_ = true;
		
		//スポットライト取得
		if (data_->notice_ == true && Vector2::Distance(myPos,lightPos) <= 10.0f) {
			world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_QUARTER);
			change_State_and_Anim(Enemy_State::Fever, Enemy_Animation::Quarter, false);
			lightFlag_ = false;
		}
		break;
	}

	if (lightFlag_ = true) {
		lightPos = Vector2(lightPosition_.x, lightPosition_.z);

		//センターライト内にいたら
		if (Vector2::Distance(myPos, lightPos) <= 10.0f) {
			//すべてのキャラを取得
			std::list<ScoreData*> datas_; datas_.clear();
			world_->getCanChangedScoreManager().getScoreDataList(datas_);

			//自分自身を削除
			datas_.remove_if([&](ScoreData* data)->bool {return data->playerNumber_ == playerNumber_; });
			

			Vector3 myPos = Vector3(centerPosition_.x, centerPosition_.y, centerPosition_.z);
			for (auto a : datas_) {
				
				if (animation_.IsAnimEnd() == true && stepFlag_ == true ) {
					changeAnimation(Enemy_Animation::Idle, 0.0f, 1.0f, false);
					OutputDebugString("IDLE\n");
					stepFlag_ = false;
				}

				//近くに敵がいたとき
				//敵が一体だったら
				if (timer_ % 60 == 0 && world_->getCanChangedScoreManager().getPlayerNumberList().size() <= 1 && BaseEnemy::is_In_Distans(a->target_.lock(), myPos, charaPos_ * 4)) {
					attackType_ = BaseEnemy::AttackType::Half;
					if (animation_.IsAnimEnd() == true && stepFlag_ == false) {
						//Halfを行う
						change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Half, false);
						stepFlag_ = true;
					}
				}
				//敵が一体以上だったら
				if (timer_ % 60 == 0 && world_->getCanChangedScoreManager().getPlayerNumberList().size() >= 2 && BaseEnemy::is_In_Distans(a->target_.lock(), myPos, charaPos_ * 4)) {
					attackType_ = BaseEnemy::AttackType::Spin;
					if (animation_.IsAnimEnd() == true && stepFlag_ == false) {
						//Spinを行う
						change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Spin, false);
						stepFlag_ = true;
					}
				}
			}
		}
	}
	timer_++;
}

void Enemy_Notice::updateFever(float deltaTime) {

	//ステップの間にアイドルを挟む
	if (animation_.IsAnimEnd() == true && stepFlag_ == true && changeFlag_ == false) {
		changeAnimation(Enemy_Animation::Idle, 0.0f, 1.0f, false);
		OutputDebugString("IDLE\n");
		rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);
		stepFlag_ = false;
	}

	if (animation_.IsAnimEnd() == true && changeFlag_ == true && stepFlag_ == false) {
		change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Idle, true);
		setNextPosition();
	}

	//スポットライトを獲得したら
	//クオーター、クオーター、ターンを繰り返す
	if (timer_ % 60 == 0 && animation_.IsAnimEnd() == true && stepFlag_ == false && stepCount_ <= 1) {
		world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_QUARTER);
		changeAnimation(Enemy_Animation::Quarter, 0.0f, 1.0f, false);
		OutputDebugString("QUARTER\n");
		stepFlag_ = true;
		stepCount_++;
	}
	if (timer_ % 60 == 0 && animation_.IsAnimEnd() == true && stepFlag_ == false && stepCount_ == 2) {
		world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_TURN);
		OutputDebugString("TURN\n");
		changeAnimation(Enemy_Animation::Turn, 0.0f, 1.0f, false);
		stepFlag_ = true;
		stepCount_ = 0;
	}

	timer_++;
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

void Enemy_Notice::updateWakeUp(float deltaTime)
{
		wakwUpTime_ += deltaTime;

		if (wakwUpTime_ >= animation_.GetAnimMaxTime())
			change_State_and_Anim(prevState_, Enemy_Animation::Move_Forward, false);

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
