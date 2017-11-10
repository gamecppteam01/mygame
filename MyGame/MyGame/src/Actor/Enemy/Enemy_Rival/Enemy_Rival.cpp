#include "Enemy_Rival.h"
#include"../../../World/IWorld.h"
#include"../../../ScoreManager/ScoreMap.h"
#include"../../../Math/MathHelperSupport.h"
#include"../../../Math/Random.h"
#include"../../../ScoreManager/ScoreManager.h"
#include"../../Player/Player.h"
#include"../../../Sound/TempoManager.h"

static const float attackResetDistance = 40.0f;
Enemy_Rival::Enemy_Rival(IWorld * world, const std::string & name, const Vector3 & position, int playerNumber, const IBodyPtr & body) :
	BaseEnemy(world, name, position, playerNumber, body) {

	roundPoint_ = world_->getCanChangedScoreMap().getRoundPoint();
	targetPos_ = world_->getCanChangedScoreMap().getNearestBonusPoint(position_);

	world_->findActors("Enemy", players_);

	//playersから自身を削除
	players_.remove_if([&](std::weak_ptr<Actor>& ptr)->bool {
		return ptr.lock()->getCharacterNumber() == getCharacterNumber();
	});
	players_.push_front(world_->findActor("Player"));

}

void Enemy_Rival::JustStep() {
	nonTargetResetTimer_.Action();
	if (!isCanStep())return;//ステップ不可なら無視

	rhythmTimeCount_++;

	//プレイヤーを取得しておく
	auto player = world_->findActor("Player");

	//攻撃対象の場合
	if (chooseAttackTargetMode_ ==chooseAttackTargetMode::Attack) {
		chooseStepAttackTarget(player);
		return;
	}
	//プレイヤーが1位だったら
	if (world_->getScoreManager().GetCharacterScore((std::static_pointer_cast<Player>(player))->getPlayerNumber()) == world_->getScoreManager().getMaxScore()) {
		chooseStepAttackTopPlayer(player);
		return;
	}

	//移動先を決定する
	targetPos_ = world_->getCanChangedScoreMap().getNearestBonusPoint(position_);

	bool isAttack = false;
	float nearest = Vector3::Distance(position_, players_.front().lock()->position());
	for (const auto& p : players_) {
		//範囲内に選手がいなければ次へ
		if (MathHelperSupport::MathDistance_Segment_Point(position_, targetPos_, p.lock()->position()) > attackDistance)continue;
		float dist = Vector3::Distance(position_, p.lock()->position());
		if (dist <= nearest&&prevHitActorNumber_ != p.lock()->getCharacterNumber()) {
			nearest = dist;
			attackTarget_ = p;
			prevHitActorNumber_ = attackTarget_.lock()->getCharacterNumber();
			isAttack = true;
		}
	}
	if (isAttack) {
		change_State_and_Anim(Enemy_State::Attack, stepAnim[1].first);
		return;
	}
	//通常時は6拍子毎
	int rhythmTime = 6;
	if (rhythmTimeCount_ < rhythmTime)return;
	rhythmTimeCount_ = 0;


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


void Enemy_Rival::updateNormal(float deltaTime)
{
	//3拍目は動かない
	if (world_->getCanChangedTempoManager().getBeatCount() % 3 == 2)return;

	position_ += (targetPos_ - position_).Normalize()*movePower;


}

void Enemy_Rival::updateTrack(float deltaTime)
{
	
}

void Enemy_Rival::to_Normal()
{
	targetPos_ = world_->getCanChangedScoreMap().getNearestBonusPoint(position_);

}

void Enemy_Rival::to_Track()
{
}

void Enemy_Rival::to_Attack(BaseEnemy::Enemy_Animation anim)
{
	stepTime_ = 1.5f;

}

int Enemy_Rival::getNearestPoint(const Vector3 & position)
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

void Enemy_Rival::chooseStepAttackTarget(const ActorPtr & player)
{
	Vector3 playerPos = player->position();
	if (Vector3::Distance(player->position(), attackTargetDefaultPos_) >= attackResetDistance) {
		change_State_and_Anim(Enemy_State::Track, Enemy_Animation::Move_Forward);
		chooseAttackTargetMode_ = chooseAttackTargetMode::NotAttack;
	}
	else {
		if (Vector3::Distance(position_, playerPos) <= attackDistance) {
			//プレイヤーに攻撃する
			change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Turn);
			attackTarget_ = player;

		}
		//範囲外なら
		else {
			//プレイヤーのとこに近づく
			targetPos_ = player->position();
		}

	}

}

void Enemy_Rival::chooseStepAttackTopPlayer(const ActorPtr & player)
{
	Vector3 playerPos = player->position();
	//攻撃対象を固定して初期位置を覚えておく
	attackTargetDefaultPos_ = playerPos;
	attackStartDefaultPos_ = position_;
	chooseAttackTargetMode_ = chooseAttackTargetMode::Attack;
	//プレイヤーが攻撃範囲内なら
	if (Vector3::Distance(position_, playerPos) <= attackDistance) {
		//プレイヤーに攻撃する
		change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Turn);
		attackTarget_ = player;

	}
	//範囲外なら
	else {
		//プレイヤーのとこに近づく
		targetPos_ = player->position();
	}

}
