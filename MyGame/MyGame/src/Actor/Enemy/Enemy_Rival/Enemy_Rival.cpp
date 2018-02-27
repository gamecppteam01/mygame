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
//スピン範囲
static const float Spin_Range = 40.0f;
//ハーフ範囲
static const float Half_Range = 60.0f;

Enemy_Rival::Enemy_Rival() :
	BaseEnemy("Enemy"), scoreManager_(nullptr), prevAttackType_(AttackType::None), prevRivalState_(RivalState::MoveMode)
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

void Enemy_Rival::hitOther(const Vector3 & velocity)
{
	BaseEnemy::hitOther(velocity);

	if (lightState_ == LightState::CenterLighting && state_ != Enemy_State::Attack) {
		moveState_ = MoveState::Avoid;
		timer_ = 0.0f;
		stopTimer_ = 0.0f;
		nextPoint_ = { -1,-1 };
		finalPoint_ = { -1,-1 };
		setNextPosition();
	}
}

void Enemy_Rival::initialize() {
	m_LightStateUpdateFunc[LightState::Extinction] = [this](float deltaTime) {ExtinctionUpdate(deltaTime); };
	m_LightStateUpdateFunc[LightState::CenterLighting] = [this](float deltaTime) {CenterLightingUpdate(deltaTime); };
	m_LightStateUpdateFunc[LightState::SpotLighting] = [this](float deltaTime) {SpotLighting(deltaTime); };

	m_MoveUpdate[MoveState::Avoid] = [this](float deltaTime) {AvoidMove(deltaTime); };
	m_MoveUpdate[MoveState::First_Aim] = [this](float deltaTime) {FirstMove(deltaTime); };

	lightState_ = LightState::Extinction;
	rivalState_ = RivalState::MoveMode;
	attackType_ = AttackType::None;
	startPos_ = centerPosition_;
	moveCount_ = 0;
	stepCount_ = 0;
	timer_ = 0.0f;
}

void Enemy_Rival::onMessage(EventMessage message, void * param) {
	switch (message)
	{
	case EventMessage::Lighting:
		lightPosition_ = (Vector3&)param;
		nextPosition_ = lightPosition_ + Vector3::Up * 6;
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
	//DebugDraw::DebugDrawFormatString(200, 300, GetColor(255, 255, 255), "%f", moveTimer_);

	Vector2 myPos = Vector2(centerPosition_.x, centerPosition_.z);
	Vector2 pointPos = Vector2(nextPosition_.x, nextPosition_.z);

	////ポイントに到達したら
	//float dis = Vector2::Distance(myPos, pointPos);
	//DebugDraw::DebugDrawFormatString(200, 200, GetColor(255, 255, 255), "%f", dis);

	DebugDraw::DebugDrawFormatString(200, 100, GetColor(255, 255, 255), "%f", Vector3::Distance(nextPosition_, centerPosition_));

	std::list<ActorPtr> actors;
	world_->findActors("Enemy", actors);
	actors.remove_if([&](auto& a) {return a->getCharacterNumber() == characterNumber_; });
	actors.push_back(world_->findActor("Player"));
	std::list<Vector3> posits;
	for (auto& a : actors) {
		posits.push_back(a->position());
	}
	//AvoidSearch::Search(world_, position_, posits, finalPosition_);

	for (auto& d : score_) {
		DebugDraw::DebugDrawFormatString(d.pos.x, d.pos.y, GetColor(255, 0, 0), "%f", d.score);
	}

	DrawSphere3D(finalPosition_, 5, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
}

void Enemy_Rival::onShadowDraw() const
{
	//判定の中心に描画位置を合わせる
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	animation_.Draw(Matrix(Matrix::Identity)*Matrix(rotation_).Translation(drawPosition));
}

void Enemy_Rival::onCollide(Actor & other)
{
	BaseEnemy::onCollide(other);
}


void Enemy_Rival::updateNormal(float deltaTime)
{
	//rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);

	m_LightStateUpdateFunc[lightState_](deltaTime);

}

void Enemy_Rival::updateFever(float deltaTime) {
	if (timer_ <= 2.0f) {
		m_MoveUpdate[moveState_](deltaTime);
	}
	else {
		if (stepCount_ >= 1) {
			stepCount_ = 0;
			world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_TURN);
			changeAnimation(Enemy_Animation::Turn, 0.0f, 1.0f, false);
		}
		else {
			stepCount_++;
			world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_QUARTER);
			changeAnimation(Enemy_Animation::Quarter, 0.0f, 1.0f, false);
		}
		timer_ = 0.0f;
	}
	//ステップの間にアイドルを挟む
	if (animation_.IsAnimEnd() == true) {
		changeAnimation(Enemy_Animation::Idle, 0.0f, 1.0f, true);
		//OutputDebugString("IDLE\n");
		//rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);
	}

	timer_ += deltaTime;
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

	//nextPoint_ = Point(-1, -1);
	//finalPoint_ = Point(-1, -1);
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

	if (is_First() == true) {
		nextPoint_ = Point(-1, -1);
		finalPoint_ = Point(-1, -1);
		moveState_ = MoveState::Avoid;
		setNextPosition();
	}
	else {
		moveState_ = MoveState::First_Aim;
		nextPosition_ = scoreManager_->getFirst().target_.lock()->position();
		finalPosition_ = nextPosition_;
	}

	prevRivalState_ = rivalState_;
	rivalState_ = RivalState::MoveMode;
}

void Enemy_Rival::to_Fever() {
	timer_ = 0.0f;
	stepCount_ = 0;
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

void Enemy_Rival::selectPoint() {
	std::list<ActorPtr> actors;
	world_->findActors("Enemy", actors);
	actors.remove_if([&](auto& a) {return a->getCharacterNumber() == characterNumber_; });
	actors.push_back(world_->findActor("Player"));
	std::list<Vector3> posits;
	for (auto& a : actors) {
		posits.push_back(a->position());
	}
	if (moveState_ == MoveState::Avoid) {
		finalPosition_ = AvoidSearch::selectPoint(world_, position_, posits, &finalPoint_);
		score_.clear();
		nextPosition_ = AvoidSearch::Search(world_, position_, posits, finalPosition_, basePoint_, &nextPoint_, &score_);
	}
	else if (moveState_ == MoveState::First_Aim) {
		nextPosition_ = scoreManager_->getFirst().target_.lock()->position();
		finalPosition_ = nextPosition_;
	}
}

void Enemy_Rival::setCountDown(int downCount) {
	if (state_ == Enemy_State::Down) return;
	BaseEnemy::setCountDown(downCount);
	selectPoint();
}


void Enemy_Rival::setNextPosition()
{
	std::list<ActorPtr> actors;
	world_->findActors("Enemy", actors);
	actors.remove_if([&](auto& a) {return a->getCharacterNumber() == characterNumber_; });
	actors.push_back(world_->findActor("Player"));
	std::list<Vector3> posits;
	for (auto& a : actors) {
		posits.push_back(a->position());
	}
	if (nextPoint_ == finalPoint_) {
		finalPosition_ = AvoidSearch::selectPoint(world_, position_, posits, &finalPoint_);
	}
	score_.clear();
	nextPosition_ = AvoidSearch::Search(world_, position_, posits, finalPosition_, basePoint_, &nextPoint_, &score_);
}

bool Enemy_Rival::is_First()
{
	if (scoreManager_->getFirst().playerNumber_ == playerNumber_) return true;
	if (scoreManager_->getFirst().score_ < scoreManager_->getScoreData(playerNumber_)->score_ && scoreManager_->getScoreData(playerNumber_)->score_ != 0) {
		return true;
	}
	return false;
}

BaseEnemy::AttackType Enemy_Rival::is_Attack()
{
	AttackType result = AttackType::None;
	count_ = 0;
	std::list<ScoreData*> datas;
	scoreManager_->getScoreDataList(datas);
	//datasから自身を削除
	datas.remove_if([&](ScoreData* data)->bool { return data->playerNumber_ == getPlayerNumber(); });

	for (auto& d : datas) {
		if (Vector3::Distance(d->target_.lock()->position(), position_) <= Spin_Range) {
			result = AttackType::Spin;
			break;
		}
		else if (Vector3::Distance(d->target_.lock()->position(), position_) <= Half_Range) {
			count_++;
			if (count_ == 1) {
				result = AttackType::Half;
			}
			else {
				result = AttackType::None;
			}
		}
	}
	return result;
}

void Enemy_Rival::FirstMove(float deltaTime)
{
	if (world_->getCanChangedTempoManager().getBeatCount() % 3 == 2) {
		speedEaseTimer_ = 0.0f;
		return;
	}
	//2拍分の時間
	float maxEaseTime = world_->getCanChangedTempoManager().getOneBeatTime()*2.0f;
	//0.5拍を取得、ここを勢いの頂点とする
	float quarter = maxEaseTime*0.25f;

	speedEaseTimer_ += deltaTime;
	float maxp = 2.f;
	float answer = mathSpeedUnderPower(speedEaseTimer_, maxp, maxEaseTime, quarter);

	Vector3 vel = (nextPosition_ - centerPosition_).Normalize();
	vel.y = 0.0f;
	velocity_ += vel.Normalize()*movePower*answer*0.5f;

	if (Vector2::Distance(Vector2{ centerPosition_.x,centerPosition_.z }, Vector2{ nextPosition_.x,nextPosition_.z }) <= 5.0f) {
		if (lightState_ == LightState::CenterLighting) {
			nextPosition_ = lightPosition_;
		}
		else {
			nextPosition_ = scoreManager_->getFirst().target_.lock()->position();
		}
	}
}

void Enemy_Rival::AvoidMove(float deltaTime)
{
	if (world_->getCanChangedTempoManager().getBeatCount() % 3 == 2) {
		return;
	}
	Vector3 pos = (nextPosition_ - position_).Normalize()*0.07f;
	avoidDirection_ += pos;
	centerPosition_ += avoidDirection_;
	avoidDirection_ *= 0.9f;
	if (Vector2::Distance(Vector2{ centerPosition_.x,centerPosition_.z }, Vector2{ nextPosition_.x,nextPosition_.z }) <= 5.0f) {
		setNextPosition();
	}
}

void Enemy_Rival::ExtinctionUpdate(float deltaTime) {
	float t = 0;
	Vector2 myPos;
	Vector2 pointPos;
	float dis;

	switch (rivalState_)
	{
		//攻撃モード
	case Enemy_Rival::RivalState::AttackMode:

		attackType_ = is_Attack();

		if (attackType_ == AttackType::Spin) {
			change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Spin);
		}
		else if (attackType_ == AttackType::Half) {
			change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Half);
		}

		if (is_First() == true) {
			nextPoint_ = Point(-1, -1);
			finalPoint_ = Point(-1, -1);
			moveState_ = MoveState::Avoid;
			setNextPosition();
		}
		else {
			moveState_ = MoveState::First_Aim;
			nextPosition_ = scoreManager_->getFirst().target_.lock()->position();
			finalPosition_ = nextPosition_;
		}
		prevRivalState_ = rivalState_;
		stopTimer_ = 0.0f;
		rivalState_ = RivalState::MoveMode;
		break;

		//移動モード
	case Enemy_Rival::RivalState::MoveMode:

		myPos = Vector2(centerPosition_.x, centerPosition_.z);
		pointPos = Vector2(finalPosition_.x, finalPosition_.z);
		dis = Vector2::Distance(myPos, pointPos);

		//ポイントに到達したら
		if (dis <= 15.0f) {
			stopTimer_ += deltaTime;
			if (stopTimer_ <= 1.0f) return;
			moveTimer_ = 0.0f;
			prevRivalState_ = rivalState_;
			moveCount_++;
			rivalState_ = RivalState::StepMode;
		}

		m_MoveUpdate[moveState_](deltaTime);
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
		}
		break;
	}
}

void Enemy_Rival::CenterLightingUpdate(float deltaTime) {
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
		attackType_ = is_Attack();

		numbers = scoreManager_->getPlayerNumberList();
		numbers.remove_if([&](int number)->bool {return number == getPlayerNumber(); });
		if (numbers.size() > 0) {
			attackTarget_ = scoreManager_->getScoreData(numbers.front())->target_;
		}
		else {
			attackTarget_ = getNearestActor();
		}

		if (attackType_ == AttackType::Spin && Vector3::Distance(centerPosition_, lightPosition_) <= 20.0f) {
			change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Spin);
		}
		else if (attackType_ == AttackType::Half && numbers.size() >= 1) {
			change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Half);
		}
		//else {
		//	moveState_ = MoveState::Avoid;
		//	prevRivalState_ = rivalState_;
		//	rivalState_ = RivalState::MoveMode;
		//	return;
		//}

		moveState_ = MoveState::First_Aim;
		nextPosition_ = lightPosition_ + Vector3::Up * 6;
		prevRivalState_ = rivalState_;
		rivalState_ = RivalState::MoveMode;
		break;

		//移動モード
	case Enemy_Rival::RivalState::MoveMode:

		myPos = Vector2(centerPosition_.x, centerPosition_.z);
		pointPos = Vector2(finalPosition_.x, finalPosition_.z);

		//if (timer_ >= 5.0f && moveState_ == MoveState::Avoid) {
		//	nextPosition_ = lightPosition_;
		//	moveState_ = MoveState::First_Aim;
		//}

		//ポイントに到達したら
		dis = Vector2::Distance(myPos, pointPos);
		if (dis <= 10.0f) {
			stopTimer_ += deltaTime;
			if (stopTimer_ <= 1.0f) return;
			if (moveState_ == MoveState::Avoid) {
				nextPosition_ = lightPosition_;
				moveState_ = MoveState::First_Aim;
				return;
			}
			moveTimer_ = 0.0f;
			prevRivalState_ = rivalState_;
			moveCount_++;
			rivalState_ = RivalState::AttackMode;
			return;
		}
		m_MoveUpdate[moveState_](deltaTime);
		if (moveState_ == MoveState::Avoid) {
			timer_ += deltaTime;
		}
		break;

		//ステップモード
	case Enemy_Rival::RivalState::StepMode:
		break;
	}

	ScoreData* data_ = scoreManager_->getScoreData(playerNumber_);
	if (data_->notice_ == true) {
		moveState_ = MoveState::Avoid;
		////world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_QUARTER);
		////change_State_and_Anim(Enemy_State::Fever, Enemy_Animation::Quarter, false);
		lightState_ = LightState::SpotLighting;
	}
	else if (playerNumber_ != scoreManager_->getNoticePlayer()->playerNumber_ && scoreManager_->getNoticePlayer()->notice_ == true) {
		moveState_ = MoveState::Avoid;
		rivalState_ = RivalState::MoveMode;
		lightState_ = LightState::Extinction;
	}
}

void Enemy_Rival::SpotLighting(float deltaTime)
{
	Vector2 myPos = Vector2(centerPosition_.x, centerPosition_.z);
	Vector2 pointPos = Vector2(finalPosition_.x, finalPosition_.z);

	if (Vector2::Distance(myPos, pointPos) <= 5.5f || timer_ <= 2.0f) {
		stopTimer_ += deltaTime;
		//if (stopTimer_ <= 1.0f) return;
		//timer_ = 0.0f;
	}

	if (stopTimer_ >= 1.0f && stepCount_ >= 1) {
		stepCount_ = 0;
		change_State_and_Anim(Enemy_State::Step, Enemy_Animation::Turn);
	}
	else if (stopTimer_ >= 1.0f) {
		stepCount_++;
		change_State_and_Anim(Enemy_State::Step, Enemy_Animation::Quarter);
	}
	if (stopTimer_ <= 2.0f) {
		m_MoveUpdate[moveState_](deltaTime);
	}
	//timer_ += deltaTime;
}
