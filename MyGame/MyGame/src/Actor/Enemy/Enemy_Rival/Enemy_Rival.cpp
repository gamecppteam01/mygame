#include "Enemy_Rival.h"
#include"../../../World/IWorld.h"
#include"../../../ScoreManager/ScoreMap.h"
#include"../../../Math/MathHelperSupport.h"
#include"../../../Math/Random.h"
#include"../../../ScoreManager/ScoreManager.h"
#include"../../Player/Player.h"
#include"../../../Sound/TempoManager.h"
#include"../../../Math/Easing.h"

//移動MAXタイマー
static const float moveMaxTimer_ = 3.0f;

static const float attackResetDistance = 40.0f;
Enemy_Rival::Enemy_Rival() :
	BaseEnemy("Enemy"),scoreManager_(nullptr),prevAttackType_(AttackType::None),prevRivalState_(RivalState::MoveMode),nextKey_(0)
{
}
Enemy_Rival::Enemy_Rival(IWorld * world, const std::string & name, const Vector3 & position, int playerNumber, const IBodyPtr & body) :
	BaseEnemy(world, name, position, playerNumber, body, MODEL_ID::RIVALENEMY_MODEL, MODEL_ID::RIVALENEMY_BULLET_MODEL) {

	////roundPoint_ = world_->getCanChangedScoreMap().getRoundPoint();
	////targetPos_ = world_->getCanChangedScoreMap().getNearestBonusPoint(centerPosition_);
	/*roundPoint_ = world_->getCanChangedScoreMap().getRoundPoint();
	nextPoint_ = getNearestPoint(centerPosition_);*/
	points_.clear();
	points_ = world_->getCanChangedScoreMap().getEnemy_Round_CrawlPoint();
	setNearestPoint();

	world_->findActors("Enemy", players_);

	//基本的なダウン値
	defDownCount = 20;
	//ダウンするまでのカウント
	downCount_ = defDownCount;


	//playersから自身を削除
	players_.remove_if([&](std::weak_ptr<Actor>& ptr)->bool {
		return ptr.lock()->getCharacterNumber() == getCharacterNumber();
	});
	players_.push_front(world_->findActor("Player"));

	scoreManager_ = &world->getCanChangedScoreManager();
	initialize();
}

std::shared_ptr<BaseEnemy> Enemy_Rival::Create(IWorld * world, const Vector3 & position, int playerNumber)
{
	return std::make_shared<Enemy_Rival>(world, "Enemy", position, playerNumber);
}

void Enemy_Rival::initialize() {
	m_LightStateUpdateFunc[LightState::Extinction] = [this](float deltaTime) {ExtinctionUpdate(deltaTime); };
	m_LightStateUpdateFunc[LightState::CenterLighting] = [this](float deltaTime) {CenterLightingUpdate(deltaTime); };
	m_LightStateUpdateFunc[LightState::SpotLighting] = [this](float deltaTime) {SpotLighting(deltaTime); };
	lightState_ = LightState::Extinction;
	rivalState_ = RivalState::MoveMode;
	attackType_ = AttackType::None;
	startPos_ = centerPosition_;
}

void Enemy_Rival::onMessage(EventMessage message, void * param){
	switch (message)
	{
	case EventMessage::Lighting:
		lightPosition_ = (Vector3&)param;
		nextPosition_ = lightPosition_ + Vector3::Up * 6 ;
		lightState_ = LightState::CenterLighting;
		rivalState_ = RivalState::AttackMode;
		moveTimer_ = 0.0f;
		break;
	case EventMessage::Extinction:
		lightState_ = LightState::Extinction;
		moveTimer_ = 0.0f;
		break;
	}
}

void Enemy_Rival::onDraw() const
{
	BaseEnemy::onDraw();
	DebugDraw::DebugDrawFormatString(200, 300, GetColor(255, 255, 255), "%f", moveTimer_);

	Vector2 myPos = Vector2(centerPosition_.x, centerPosition_.z);
	Vector2 pointPos = Vector2(nextPosition_.x, nextPosition_.z);

	//ポイントに到達したら
	float dis = Vector2::Distance(myPos, pointPos);
	DebugDraw::DebugDrawFormatString(200, 200, GetColor(255, 255, 255), "%f", dis);

	DebugDraw::DebugDrawFormatString(200, 100, GetColor(255, 255, 255), "%f", stopTimer_);


}

void Enemy_Rival::onShadowDraw() const
{
	//判定の中心に描画位置を合わせる
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	animation_.Draw(Matrix(Matrix::Identity)*Matrix(rotation_).Translation(drawPosition));
}


void Enemy_Rival::updateNormal(float deltaTime)
{
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);

	m_LightStateUpdateFunc[lightState_](deltaTime);
	

}

void Enemy_Rival::to_Normal()
{
	prevAttackType_ = attackType_;
	attackType_ = AttackType::None;
	count_ = 0;
	moveTimer_ = 0.0f;
	stopTimer_ = 0.0f;
}

void Enemy_Rival::to_Step(Enemy_Animation anim) {
	//対応したアニメーションの終了時間を取得する
	stepTime_ = animation_.GetAnimMaxTime((int)anim);

	//setNextPosition();
	moveCount_ = 0;
	prevRivalState_ = rivalState_;
	rivalState_ = RivalState::AttackMode;
}

void Enemy_Rival::to_Attack(Enemy_Animation anim)
{
	attackPower_ = 8;
	if (lightState_ != LightState::CenterLighting) {
		attackTarget_ = getNearestActor();
	}
	spinAngle_ = 0.0f;
	stepTime_ = 1.5f;
	prevRivalState_ = rivalState_;
	rivalState_ = RivalState::MoveMode;
	if (scoreManager_->getFirst().score_ <= scoreManager_->GetCharacterScore(playerNumber_) && lightState_ == LightState::Extinction) {
		setNextPosition();
	}
	else if(lightState_ == LightState::Extinction){
		nextPosition_ = scoreManager_->getFirst().target_.lock()->position();
	}
	startPos_ = centerPosition_;
}

//void Enemy_Rival::spin(float deltaTime){
//	velocity_ = Vector3::Zero;
//	angle_ += 3.5f;
//	Vector3 baseRotatePos = bulletDistance + bulletDistance*(1 - (MathHelper::Abs(180.f - angle_) / 180.0f)) * 6;
//	position_ = centerPosition_ + (baseRotatePos *rotation_* Matrix::CreateRotationY(-angle_));
//
//	Vector3 rotatePos = -bulletDistance + -bulletDistance*(1 - (MathHelper::Abs(180.f - angle_) / 180.0f))*6;
//	*bulletPosition_ = centerPosition_ + (rotatePos *rotation_* Matrix::CreateRotationY(-angle_));
//}

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
void Enemy_Rival::setNearestPoint()
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


void Enemy_Rival::setNextPosition()
{
	////ターゲットカウントを-1する
	//nextPoint_=(nextPoint_+roundPoint_.size()-1)%roundPoint_.size();
	//
	//float rate = 1.0f;
	//Vector3 nextPosition = world_->getCanChangedScoreMap().getNextPoint(centerPosition_, &rate);
	//if (rate >= 1.05f) {
	//	nextPosition_ = nextPosition +Vector3(Random::GetInstance().Range(-20.f, 20.f), 0.0f, Random::GetInstance().Range(-20.f, 20.f));
	//	return;
	//}
	//nextPosition_ = roundPoint_[nextPoint_];
	nextKey_ = (nextKey_ - 1 + points_.size()) % points_.size();
	nextPosition_ = points_[nextKey_];
	stopTimer_ = 0.0f;
}

void Enemy_Rival::ExtinctionUpdate(float deltaTime) {
	float t = 0;
	float dis;
	Vector2 myPos;
	Vector2 pointPos;
	std::list<ScoreData*> datas;

	switch (rivalState_)
	{
		//攻撃モード
	case Enemy_Rival::RivalState::AttackMode:
		scoreManager_->getScoreDataList(datas);
		//datasから自身を削除
		datas.remove_if([&](ScoreData* data)->bool {
			return data->playerNumber_ == getPlayerNumber();
		});

		for (auto d : datas) {
			dis = Vector3::Distance(d->target_.lock()->position(), position_);
			if (dis <= 40.0f) {
				attackType_ = AttackType::Spin;
			}
			else if (Vector3::Distance(d->target_.lock()->position(), position_) <= 60.0f) {
				count_++;
				attackType_ = AttackType::Half;
			}
		}
		if (attackType_ == AttackType::Spin) {
			change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Spin);
		}
		else if (attackType_ == AttackType::Half && count_ == 1) {
			change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Half);
		}
		else {
			if (scoreManager_->getFirst().score_ <= scoreManager_->GetCharacterScore(playerNumber_)) {
				setNextPosition();
			}
			else {
				nextPosition_ = scoreManager_->getFirst().target_.lock()->position();
			}
			startPos_ = centerPosition_;
			prevRivalState_ = rivalState_;
			rivalState_ = RivalState::MoveMode;
		}
		break;

		//移動モード
	case Enemy_Rival::RivalState::MoveMode:
		t = moveTimer_ / moveMaxTimer_;
		centerPosition_ = Vector3::Lerp(startPos_, nextPosition_, t);

		velocity_ = Vector3::Zero;
		myPos = Vector2(centerPosition_.x, centerPosition_.z);
		pointPos = Vector2(nextPosition_.x, nextPosition_.z);

		//ポイントに到達したら
		dis = Vector2::Distance(myPos, pointPos);
		if (dis <= 1.0f) {
			stopTimer_ += deltaTime;
			if (stopTimer_ <= 1.0f) return;
			moveTimer_ = 0.0f;
			prevRivalState_ = rivalState_;
			moveCount_++;
			rivalState_ = RivalState::StepMode;
		}
		moveTimer_ = min(moveTimer_ + deltaTime, moveMaxTimer_);
		break;

		//ステップモード
	case Enemy_Rival::RivalState::StepMode:
		if (moveCount_ >= 2) {
			if (stepCount_ >= 2) {
				stepCount_ = 0;
				world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_TURN);
				change_State_and_Anim(Enemy_State::Step, Enemy_Animation::Turn);
			}
			else {
				stepCount_++;
				world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_QUARTER);
				change_State_and_Anim(Enemy_State::Step, Enemy_Animation::Quarter);
			}
		}
		else {
			rivalState_ = RivalState::AttackMode;
			setNextPosition();
		}
		break;
	}
}

void Enemy_Rival::CenterLightingUpdate(float deltaTime){
	float t = 0;
	float dis;
	Vector2 myPos;
	Vector2 pointPos;
	std::list<ScoreData*> datas;
	std::list<int> numbers;

	switch (rivalState_)
	{
		//攻撃モード
	case Enemy_Rival::RivalState::AttackMode:
		scoreManager_->getScoreDataList(datas);
		//datasから自身を削除
		datas.remove_if([&](ScoreData* data)->bool {
			return data->playerNumber_ == getPlayerNumber();
		});
		//if (prevAttackType_ == AttackType::Spin) {
		//	stopTimer_ += deltaTime;
		//	if (stopTimer_ <= 1.0f) return;
		//}
		for (auto d : datas) {
			dis = Vector3::Distance(centerPosition_, lightPosition_);
			if (Vector3::Distance(d->target_.lock()->position(), position_) <= 40.0f && Vector3::Distance(centerPosition_, lightPosition_) <= 20.0f) {
				attackType_ = AttackType::Spin;
			}
			else if (Vector3::Distance(d->target_.lock()->position(), position_) <= 60.0f) {
				numbers = scoreManager_->getPlayerNumberList();
				numbers.remove_if([&](int number)->bool {return number == getPlayerNumber(); });
				if (numbers.size() < 1)return;
					attackTarget_ = scoreManager_->getScoreData(numbers.front())->target_;
			}
		}
		if (attackType_ == AttackType::Spin) {
			change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Spin);
		}
		else if (attackType_ == AttackType::Half && numbers.size() != 0) {
			attackType_ = AttackType::Half;
			change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Half);
		}
		else {
			nextPosition_ = lightPosition_ + Vector3::Up * 6;
			startPos_ = centerPosition_;
			prevRivalState_ = rivalState_;
			rivalState_ = RivalState::MoveMode;
		}
		break;

		//移動モード
	case Enemy_Rival::RivalState::MoveMode:
		t = moveTimer_ / (moveMaxTimer_ - 1);
		centerPosition_ = Vector3::Lerp(startPos_, nextPosition_, t);

		velocity_ = Vector3::Zero;
		myPos = Vector2(centerPosition_.x, centerPosition_.z);
		pointPos = Vector2(nextPosition_.x, nextPosition_.z);

		//ポイントに到達したら
		dis = Vector2::Distance(myPos, pointPos);
		if (dis <= 1.0f) {
			stopTimer_ += deltaTime;
			if (stopTimer_ <= 1.0f) return;
			moveTimer_ = 0.0f;
			prevRivalState_ = rivalState_;
			moveCount_++;
			rivalState_ = RivalState::AttackMode;
		}
		moveTimer_ = min(moveTimer_ + deltaTime, (moveMaxTimer_ - 1));
		break;

		//ステップモード
	case Enemy_Rival::RivalState::StepMode:
		break;
	}

	ScoreData* data_ = scoreManager_->getScoreData(playerNumber_);
	if (data_->notice_ == true) {
		lightState_ = LightState::SpotLighting;
		//world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_TURN);
		//change_State_and_Anim(Enemy_State::Fever, Enemy_Animation::Turn, false);
	}
}

void Enemy_Rival::SpotLighting(float deltaTime)
{
}
