#include "Enemy_Rival.h"
#include"../../../World/IWorld.h"
#include"../../../ScoreManager/ScoreMap.h"
#include"../../../Math/MathHelperSupport.h"
#include"../../../Math/Random.h"
#include"../../../ScoreManager/ScoreManager.h"
#include"../../Player/Player.h"
#include"../../../Sound/TempoManager.h"
#include"../../../Math/Easing.h"

static const float attackResetDistance = 40.0f;
Enemy_Rival::Enemy_Rival(IWorld * world, const std::string & name, const Vector3 & position, int playerNumber, const IBodyPtr & body) :
	BaseEnemy(world, name, position, playerNumber, body, MODEL_ID::BALANCEENEMY_MODEL, MODEL_ID::BALANCEENEMY_BULLET_MODEL) {

	roundPoint_ = world_->getCanChangedScoreMap().getRoundPoint();
	targetPos_ = world_->getCanChangedScoreMap().getNearestBonusPoint(centerPosition_);

	world_->findActors("Enemy", players_);

	//playersから自身を削除
	players_.remove_if([&](std::weak_ptr<Actor>& ptr)->bool {
		return ptr.lock()->getCharacterNumber() == getCharacterNumber();
	});
	players_.push_front(world_->findActor("Player"));

}

void Enemy_Rival::onDraw() const
{
	BaseEnemy::onDraw();
	world_->setLateDraw([this] {
		switch (chooseAttackTargetMode_)
		{
		case Enemy_Rival::chooseAttackTargetMode::NotAttack:
			DebugDraw::DebugDrawFormatString(400, 300, GetColor(255, 255, 255), "NotAttack");
			break;
		case Enemy_Rival::chooseAttackTargetMode::AttackMove:
			DebugDraw::DebugDrawFormatString(400, 300, GetColor(255, 255, 255), "AttackMove");
			break;
		case Enemy_Rival::chooseAttackTargetMode::Attack:
			DebugDraw::DebugDrawFormatString(400, 300, GetColor(255, 255, 255), "Attack");
			break;
		case Enemy_Rival::chooseAttackTargetMode::Return:
			DebugDraw::DebugDrawFormatString(400, 300, GetColor(255, 255, 255), "Return");
			break;
		case Enemy_Rival::chooseAttackTargetMode::Step:
			DebugDraw::DebugDrawFormatString(400, 300, GetColor(255, 255, 255), "Step");
			break;
		case Enemy_Rival::chooseAttackTargetMode::StepMove:
			DebugDraw::DebugDrawFormatString(400, 300, GetColor(255, 255, 255), "StepMove");
			break;
		default:
			break;
		}
		DebugDraw::DebugDrawFormatString(350, 300, GetColor(255, 255, 255), "%d", rhythmTimeCount_);
		
		DebugDraw::DebugDrawFormatString(600, 400, GetColor(255, 255, 255), "%f:%f:%f", centerPosition_.x, centerPosition_.y, centerPosition_.z);
	});
}

void Enemy_Rival::JustStep() {
	speedEaseTimer_ = 0.0f;

	nonTargetResetTimer_.Action();
	if (state_ == Enemy_State::Track) {
		justStepTrack();
		return;
	}
	if (!isCanStep())return;//ステップ不可なら無視

	rhythmTimeCount_++;

	//プレイヤーを取得しておく
	auto player = world_->findActor("Player");

	//通常時は6拍子毎
	int rhythmTime = 6;
	if (rhythmTimeCount_ < rhythmTime) {
		//if (state_ == Enemy_State::Normal)return;
		//攻撃するかを決定する
		chooseStepIsAttack();
		return;
	}
	rhythmTimeCount_ = 0;

	//移動先のポイントを検索する
	Vector3 nextPos = world_->getCanChangedScoreMap().getNearestBonusPoint(centerPosition_);
	//一位の情報を取得する
	auto targetScore = world_->getScoreManager().getFirst();

	if (targetScore.target_.lock()->getCharacterNumber() == getCharacterNumber()) {
		toNextStepTrackMode(chooseAttackTargetMode::StepMove);
		change_State_and_Anim(Enemy_State::Track, Enemy_Animation::Move_Forward);

		//change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Move_Forward);
		return;
	}
	//一位のレートが上がっていたら
	if (targetScore.scoreRate_ > 1.0f) {
		attackStartDefaultPos_ = player->position();
		attackTargetDefaultPos_ = player->position();
		//一位を攻撃対象にする
		attackTarget_ = targetScore.target_;
		Enemy_Animation nextAnim;
		//攻撃の射程圏内なら
		if (Vector3::Distance(centerPosition_, attackTarget_.lock()->position()) <= attackDistance) {
			toNextStepTrackMode(chooseAttackTargetMode::AttackMove);
			nextAnim = Enemy_Animation::Move_Forward;
		}
		else {
			toNextStepTrackMode(chooseAttackTargetMode::Attack);
			nextAnim = Enemy_Animation::Idle;
		}
		change_State_and_Anim(Enemy_State::Track, Enemy_Animation::Move_Forward);
		return;
	}
	toNextStepTrackMode(chooseAttackTargetMode::StepMove);
	change_State_and_Anim(Enemy_State::Track, Enemy_Animation::Move_Forward);

	////攻撃対象を一位のキャラクターに設定する
	//auto target = world_->getScoreManager().getFirst().target_;
	////移動先から範囲内にいたら攻撃モードへ移行
	//if (Vector3::Distance(target.lock()->position(), nextPos) <= attackDistance) {
	//	chooseStepAttackTopPlayer(target.lock(), nextPos);
	//	return;
	//}


	//int r = Random::GetInstance().Range(0, 9);
	//if (r < 3) {
	//	//ターン
	//	world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_TURN);
	//}
	//else {
	//	//クォーター
	//	world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_QUARTER);
	//
	//}
	//change_State_and_Anim(Enemy_State::Step, Enemy_Animation::Move_Forward);

}


void Enemy_Rival::updateNormal(float deltaTime)
{
	//3拍目は動かない
	if (world_->getCanChangedTempoManager().getBeatCount() % 3 == 2) {
		speedEaseTimer_ = 0.0f;
		return;
	}

	//2拍分の時間
	float maxEaseTime = world_->getCanChangedTempoManager().getOneBeatTime()*2.0f;
	//0.5拍を取得、ここを勢いの頂点とする
	float quarter=maxEaseTime*0.25f;
	
	speedEaseTimer_ += deltaTime;
	float maxp = 2.f;
	float answer = mathSpeedUnderPower(speedEaseTimer_, maxp, maxEaseTime, quarter);

	//float answer = 1.f-std::abs(speedEaseTimer_ - quarter)*5.f;
	/*
	float ptime = speedEaseTimer_ / maxEaseTime;
	float pease = Easing::EaseInOutCubic(speedEaseTimer_, 0.0f, 1.0f, maxEaseTime);
	float pnormal = Easing::Linear(speedEaseTimer_, 0.0f, 1.0f, maxEaseTime);

	speedEaseTimer_ += deltaTime;
	float time = speedEaseTimer_ / maxEaseTime;
	float ease = Easing::EaseInOutCubic(speedEaseTimer_, 0.0f, 1.0f, maxEaseTime);
	float normal = Easing::Linear(speedEaseTimer_, 0.0f, 1.0f, maxEaseTime);

	float answer = (ease - pease);
	answer = powf(answer, 2);
	answer *= 300.0f;
	*/

	OutputDebugString(std::to_string(answer).c_str());
	OutputDebugString("\n");

	Vector3 vel = (targetPos_ - centerPosition_);
	vel.y = 0.0f;
	centerPosition_ += vel.Normalize()*movePower*answer;

	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);

	//ポイントに近づいたら次のポイントに移動
	if (Vector2::Distance(Vector2(centerPosition_.x, centerPosition_.z), Vector2(targetPos_.x,targetPos_.z)) <= 10.0f)setNextPosition();

}

void Enemy_Rival::updateTrack(float deltaTime)
{
	switch (chooseAttackTargetMode_)
	{
	case Enemy_Rival::chooseAttackTargetMode::NotAttack: {
		//巡回を終了する
		if (change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Move_Forward))updateNormal(deltaTime);
		return;
		break; 
	}
	case Enemy_Rival::chooseAttackTargetMode::AttackMove: {
		//3拍目は動かない
		if (world_->getCanChangedTempoManager().getBeatCount() % 3 == 2)return;
		
		//2拍分の時間
		float maxEaseTime = world_->getCanChangedTempoManager().getOneBeatTime()*2.0f;
		//0.5拍を取得、ここを勢いの頂点とする
		float quarter = maxEaseTime*0.25f;
		speedEaseTimer_ += deltaTime;
		float maxp = 2.f;
		float answer = mathSpeedUnderPower(speedEaseTimer_, maxp, maxEaseTime, quarter);

		//攻撃位置に移動する
		centerPosition_ += (targetPos_ - centerPosition_).Normalize()*movePower*answer;
		//攻撃位置に到達したら
		if (Vector3::Distance(centerPosition_, targetPos_) <= 10.0f) {
			toNextStepTrackMode(chooseAttackTargetMode::Attack);
		}
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::Attack: {
		stepTime_ -= deltaTime;
		//ステップが終了したら待機状態に戻る
		if (stepTime_ <= 0.0f) {
			//敵が範囲外にいったら
			if (Vector3::Distance(attackTarget_.lock()->position(), attackTargetDefaultPos_) >= 40.0f) {
				toNextStepTrackMode(chooseAttackTargetMode::Return);
			}
			else {
				toNextStepTrackMode(chooseAttackTargetMode::AttackMove);
			}
			return;
		}
		centerPosition_ += (attackTarget_.lock()->position() - centerPosition_).Normalize() *attackPower;
		
		//ここから回転
		Vector3 baseRotatePos = bulletDistance;
		position_ = centerPosition_ + (baseRotatePos *rotation_* Matrix::CreateRotationY(-stepTime_*5.0f));
		//回転を更新
		rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -20.0f*turnPower_);

		Vector3 rotatePos = -bulletDistance;
		*bulletPosition_ = centerPosition_ + (rotatePos *rotation_* Matrix::CreateRotationY(-stepTime_*5.0f));

		break;
	}
	//スコア取得位置に戻る												  
	case Enemy_Rival::chooseAttackTargetMode::Return: {
		//3拍目は動かない
		if (world_->getCanChangedTempoManager().getBeatCount() % 3 == 2)return;

		//2拍分の時間
		float maxEaseTime = world_->getCanChangedTempoManager().getOneBeatTime()*2.0f;
		//0.5拍を取得、ここを勢いの頂点とする
		float quarter = maxEaseTime*0.25f;
		speedEaseTimer_ += deltaTime;
		float maxp = 2.f;
		float answer = mathSpeedUnderPower(speedEaseTimer_, maxp, maxEaseTime, quarter);

		centerPosition_ += (attackStartDefaultPos_ - centerPosition_).Normalize()*movePower*answer;
		//ステップ位置へ移動する
		if (Vector3::Distance(centerPosition_, attackStartDefaultPos_) <= 10.0f)toNextStepTrackMode(chooseAttackTargetMode::StepMove);
		break; 
	}
	case Enemy_Rival::chooseAttackTargetMode::Step:{
		stepTime_ -= deltaTime;
		//時間が来たら
		if (stepTime_ > 0.0f) return;
		//通常アニメに戻る
		defAnimSetTimer_.Action();
		//ステップが全部終わったら
		if (stepQueue_.empty()) {
			//通常の巡回に戻る
			toNextStepTrackMode(chooseAttackTargetMode::NotAttack);
			return;
		}
		
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::StepMove:{
		//3拍目は動かない
		if (world_->getCanChangedTempoManager().getBeatCount() % 3 == 2)return;
		

		//2拍分の時間
		float maxEaseTime = world_->getCanChangedTempoManager().getOneBeatTime()*2.0f;
		//0.5拍を取得、ここを勢いの頂点とする
		float quarter = maxEaseTime*0.25f;
		speedEaseTimer_ += deltaTime;
		float maxp = 2.f;
		float answer = mathSpeedUnderPower(speedEaseTimer_, maxp, maxEaseTime, quarter);

		//ステップ開始位置に移動する
		centerPosition_ += (targetPos_ - centerPosition_).Normalize()*movePower*answer;
		//目的地に到達したらステップを開始する
		if (Vector3::Distance(centerPosition_, targetPos_) <= 10.0f) {
			toNextStepTrackMode(chooseAttackTargetMode::Step);
		}
		break;
	}
	default: {
		if (change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Move_Forward))updateNormal(deltaTime);
		break;
	}
	}
}

void Enemy_Rival::to_Normal()
{
	targetPos_ = world_->getCanChangedScoreMap().getNearestBonusPoint(centerPosition_);
	//setNextPosition();
	speedEaseTimer_ = 0.0f;
}

void Enemy_Rival::to_Track()
{
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

void Enemy_Rival::justStepTrack()
{

	switch (chooseAttackTargetMode_)
	{
	case Enemy_Rival::chooseAttackTargetMode::NotAttack: {
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::AttackMove: {
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::Attack: {
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::Return: {
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::Step: {
		if (stepQueue_.empty())return;

		//1つアニメーションを取り出す
		int nextStep = stepQueue_.front();
		stepQueue_.pop();
		defAnimSetTimer_.Initialize();
		defAnimSetTimer_.Add([this] {changeAnimation(Enemy_Animation::Move_Forward); });
		changeAnimation(stepAnim[nextStep].first,0.0f,1.0f,false);
		world_->getCanChangedScoreManager().addScore(playerNumber_, stepAnim[nextStep].second);
		//対応したアニメーションの終了時間を取得する
		stepTime_ = animation_.GetAnimMaxTime((int)stepAnim[nextStep].first);
		
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::StepMove: {
		break; 
	}
	default: {
		break; 
	}
	}
}

void Enemy_Rival::toNextStepTrackMode(chooseAttackTargetMode nextMode)
{
	chooseAttackTargetMode_ = nextMode;
	switch (chooseAttackTargetMode_)
	{
	case Enemy_Rival::chooseAttackTargetMode::NotAttack: {
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::AttackMove: {
		targetPos_ = attackTarget_.lock()->position();
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::Attack: {
		stepTime_ = 1.5f;
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::Return: {
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::Step: {
		//行うステップを設定
		stepQueue_.push(0);//クォーター
		stepQueue_.push(2);//ターン
		stepQueue_.push(0);//クォーター

		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::StepMove: {
		//行き先を最も近い巡回ポイントに決定
		targetPos_ = world_->getCanChangedScoreMap().getNearestBonusPoint(centerPosition_);
		break;
	}
	default: {
		break;
	}
	}

}

void Enemy_Rival::chooseStepAttackTarget(const ActorPtr & player)
{
	Vector3 playerPos = player->position();
	if (Vector3::Distance(player->position(), attackTargetDefaultPos_) >= attackResetDistance) {
		change_State_and_Anim(Enemy_State::Track, Enemy_Animation::Move_Forward);
		toNextStepTrackMode(chooseAttackTargetMode::NotAttack);
	}
	else {
		if (Vector3::Distance(centerPosition_, playerPos) <= attackDistance) {
			//プレイヤーに攻撃する
			change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Turn);
			attackTarget_ = player;

		}
		//範囲外なら
		else {
			//プレイヤーのとこに近づく
			attackTarget_ = player;
			targetPos_ = player->position();
			change_State_and_Anim(Enemy_State::Track, Enemy_Animation::Move_Forward);
		}

	}

}

void Enemy_Rival::chooseStepAttackTopPlayer(const ActorPtr & player,const Vector3 basePos)
{
	Vector3 playerPos = player->position();
	//攻撃対象を固定して初期位置を覚えておく
	attackTargetDefaultPos_ = playerPos;
	attackStartDefaultPos_ = basePos;
	//プレイヤーが攻撃範囲内なら
	if (Vector3::Distance(centerPosition_, playerPos) <= attackDistance) {
		toNextStepTrackMode(chooseAttackTargetMode::Attack);
		//プレイヤーに攻撃する
		change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Turn);
		attackTarget_ = player;

	}
	//範囲外なら
	else {
		//プレイヤーのとこに近づく
		targetPos_ = player->position();
		change_State_and_Anim(Enemy_State::Track, Enemy_Animation::Move_Forward);
	}

}

bool Enemy_Rival::chooseStepIsAttack()
{
	//移動先を決定する
	if(state_!=Enemy_State::Normal)targetPos_ = world_->getCanChangedScoreMap().getNearestBonusPoint(centerPosition_);

	bool isAttack = false;
	float nearest = Vector3::Distance(centerPosition_, players_.front().lock()->position());
	for (const auto& p : players_) {
		//範囲内に選手がいなければ次へ
		if (
			(MathHelperSupport::MathDistance_Segment_Point(centerPosition_, targetPos_, p.lock()->position()) > attackDistance)&&//進行方向に敵がいない
			(Vector3::Distance(p.lock()->position(),centerPosition_)>attackDistance)//攻撃範囲内に敵がいない
			)continue;
		float dist = Vector3::Distance(centerPosition_, p.lock()->position());
		if (dist <= attackDistance&&prevHitActorNumber_ != p.lock()->getCharacterNumber()) {
			nearest = dist;
			attackTarget_ = p;
			prevHitActorNumber_ = attackTarget_.lock()->getCharacterNumber();
			isAttack = true;
		}
	}
	if (isAttack) {
		change_State_and_Anim(Enemy_State::Attack, stepAnim[1].first);
	}
	return isAttack;

}

void Enemy_Rival::setNextPosition()
{
	//ターゲットカウントを-1する
	nextPoint_ = (nextPoint_ + roundPoint_.size() - 1) % roundPoint_.size();

	//float rate = 1.0f;
	//Vector3 nextPosition = world_->getCanChangedScoreMap().getNextPoint(position_, &rate);
	//if (rate >= 1.05f) {
	//	isGoBonus_ = true;
	//	nextPosition_ = nextPosition + Vector3(Random::GetInstance().Range(-20.f, 20.f), 0.0f, Random::GetInstance().Range(-20.f, 20.f));
	//	return;
	//}
	targetPos_ = roundPoint_[nextPoint_];

}
void Enemy_Rival::setCountDown()
{
	//ダウンしてなければダウン値蓄積を有効化
	if (state_ == Enemy_State::Down||(state_==Enemy_State::Track&&chooseAttackTargetMode_==chooseAttackTargetMode::Attack))return;
	downTimer_.Initialize();
	downTimer_.Add([this] {downCount_--; });
}
