#include "Enemy_Round.h"
#include"../../../World/IWorld.h"
#include"../../../ScoreManager/ScoreMap.h"
#include"../../../ScoreManager/ScoreManager.h"
#include"../../../Sound/TempoManager.h"
#include"../../../Math/Random.h"

Enemy_Round::Enemy_Round():
	BaseEnemy("Enemy")
{
}

Enemy_Round::Enemy_Round(IWorld * world, const std::string & name, const Vector3 & position, int playerNumber):
	BaseEnemy(world,name,position,playerNumber, std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f),
		MODEL_ID::BALANCEENEMY_MODEL, MODEL_ID::BALANCEENEMY_BULLET_MODEL)
{
	points_.clear();
	points_=world_->getCanChangedScoreMap().getEnemy_Round_CrawlPoint();
	setNearestPoint();
	timer_ = 0.0f;
	nextStep = 0;
}

std::shared_ptr<BaseEnemy> Enemy_Round::Create(IWorld * world, const Vector3 & position, int playerNumber)
{
	return std::make_shared<Enemy_Round>(world, "Enemy", position, playerNumber);
}

void Enemy_Round::to_Normal()
{
	//setNearestPoint();
}

void Enemy_Round::JustStep()
{
}

void Enemy_Round::updateNormal(float deltaTime)
{
	timer_ += deltaTime;

	data_ = world_->getCanChangedScoreManager().getScoreData(playerNumber_);
	firstdata = world_->getCanChangedScoreManager().getFirst();

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

	Vector3 vel = (nextPosition_ - centerPosition_);
	vel.y = 0.0f;
	centerPosition_ += vel.Normalize()*movePower*answer;

	//Vector3 pos = (nextPosition_ - position_).Normalize()*movePower;
	//centerPosition_ += pos;
	if (Vector2::Distance(Vector2{ centerPosition_.x,centerPosition_.z },
		Vector2{ nextPosition_.x,nextPosition_.z }) <= 10.0f) nextPosition();

	Step();
	//Around_Enemy(50.0f);
}

void Enemy_Round::onShadowDraw() const
{
	//判定の中心に描画位置を合わせる
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	animation_.Draw(Matrix(Matrix::Identity)*Matrix(rotation_).Translation(drawPosition));
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
	//nextKey_ = (nextKey_ - 1 + points_.size()) % points_.size();
	//if (Around_Enemy(50.0f) >= 1) {
		nextKey_ = (nextKey_ - Random::GetInstance().Range(1, 12) + points_.size()) % points_.size();
	//}
	nextPosition_ = points_[nextKey_];
	
}

void Enemy_Round::Step(){
	if (timer_ >= 5.0f && Distance_First()) {
		nextStep = 1;
		change_State_and_Anim(Enemy_State::Attack, stepAnim[nextStep].first, false);
		timer_ = 0.0f;
	}
	else if (timer_ >= 7.0f) {
		nextStep = 0;
		change_State_and_Anim(Enemy_State::Step, stepAnim[nextStep].first, false);
		world_->getCanChangedScoreManager().addScore(playerNumber_, stepAnim[nextStep].second);
		timer_ = 0.0f;
	}
	else if (timer_ >= 9.0f) {
		nextStep = 2;
		change_State_and_Anim(Enemy_State::Step, stepAnim[nextStep].first, false);
		world_->getCanChangedScoreManager().addScore(playerNumber_, stepAnim[nextStep].second);
		timer_ = 0.0f;
	}
}

bool Enemy_Round::Distance_First()
{
	if(!RankedFirst() && is_In_Distans(ActorPtr(firstdata.target_), centerPosition_, 50.0f)){
		return true;
	}
	return false;
}

bool Enemy_Round::RankedFirst()
{
	if (firstdata.playerNumber_ == playerNumber_) {
		return true;
	}
	return false;
}

int Enemy_Round::Around_Enemy(float distance)
{
	int enemy_count = 0;
	int num = world_->getCanChangedScoreManager().GetCharacterCount();
	ScoreData* data[7];
	for (int i = 0; i <= num; i++) {
		data[i] = world_->getCanChangedScoreManager().getScoreData(min(i+1,num));
		if (is_In_Distans(ActorPtr(data[i]->target_), centerPosition_, distance)){
			enemy_count++;
		}
	}
	return enemy_count;
}
