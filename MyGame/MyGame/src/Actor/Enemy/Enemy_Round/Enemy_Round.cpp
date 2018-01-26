#include "Enemy_Round.h"
#include"../../../World/IWorld.h"
#include"../../../ScoreManager/ScoreMap.h"
#include"../../../ScoreManager/ScoreManager.h"
#include"../../../Sound/TempoManager.h"
#include"../../../Math/Random.h"

Enemy_Round::Enemy_Round() :
	BaseEnemy("Enemy")
{
}

Enemy_Round::Enemy_Round(IWorld * world, const std::string & name, const Vector3 & position, int playerNumber) :
	BaseEnemy(world, name, position, playerNumber, std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f),
		MODEL_ID::BALANCEENEMY_MODEL, MODEL_ID::BALANCEENEMY_BULLET_MODEL)
{
	points_.clear();
	points_ = world_->getCanChangedScoreMap().getEnemy_Round_CrawlPoint();
	setNearestPoint();
}

std::shared_ptr<BaseEnemy> Enemy_Round::Create(IWorld * world, const Vector3 & position, int playerNumber)
{
	return std::make_shared<Enemy_Round>(world, "Enemy", position, playerNumber);
}

void Enemy_Round::JustStep()
{
	////ターゲット指定のリセットはとりあえずやる
	//nonTargetResetTimer_.Action();

	//if (Random::GetInstance().Range(1, 10) > 3) {
	//	rhythmTimeCount_++;
	//}
	//if (rhythmTimeCount_ < 2) return;

	//rhythmTimeCount_ = 0;
	//nextPosition();

	////ステップ出来るときだけステップする
	//if (!isCanStep())return;

	//int nextStep = Random::GetInstance().Randomize(std::vector<int>{ 0,2 });
	//change_State_and_Anim(Enemy_State::Step, stepAnim[nextStep].first,false);
	//world_->getCanChangedScoreManager().addScore(playerNumber_, stepAnim[nextStep].second);


}

void Enemy_Round::to_Normal()
{
	//setNearestPoint();
	selectPoint();
	avoidDirection_ = Vector3::Zero;
}

void Enemy_Round::onDraw() const
{
	//判定の中心に描画位置を合わせる
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	animation_.Draw(Matrix(Matrix::Identity)*Matrix(rotation_).Translation(drawPosition));
	
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

void Enemy_Round::updateNormal(float deltaTime)
{
	Vector3 pos = (nextPosition_ - position_).Normalize()*0.05f;
	avoidDirection_ += pos;
	centerPosition_ += avoidDirection_;
	avoidDirection_ *= 0.9f;

	if (Vector2::Distance(Vector2{ centerPosition_.x,centerPosition_.z }, Vector2{ nextPosition_.x,nextPosition_.z }) <= 10.0f) {
		nextPosition();
	}

	//if (world_->getCanChangedTempoManager().getBeatCount() % 3 == 2) {
	//	speedEaseTimer_ = 0.0f;
	//	return;
	//}

	////2拍分の時間
	//float maxEaseTime = world_->getCanChangedTempoManager().getOneBeatTime()*2.0f;
	////0.5拍を取得、ここを勢いの頂点とする
	//float quarter = maxEaseTime*0.25f;

	//speedEaseTimer_ += deltaTime;
	//float maxp = 2.f;
	//float answer = mathSpeedUnderPower(speedEaseTimer_, maxp, maxEaseTime, quarter);

	//Vector3 vel = (nextPosition_ - centerPosition_);
	//vel.y = 0.0f;
	//centerPosition_ += vel.Normalize()*movePower*answer;


	////Vector3 pos = (nextPosition_ - position_).Normalize()*movePower;
	////centerPosition_ += pos;
	//if (Vector2::Distance(Vector2{ centerPosition_.x,centerPosition_.z }, Vector2{ nextPosition_.x,nextPosition_.z }) <= 10.0f) nextPosition();
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


	//nextKey_ = (nextKey_ - 1+ points_.size()) % points_.size();
	//nextPosition_ = points_[nextKey_];
}

void Enemy_Round::selectPoint()
{
	std::list<ActorPtr> actors;
	world_->findActors("Enemy", actors);
	actors.remove_if([&](auto& a) {return a->getCharacterNumber() == characterNumber_; });
	actors.push_back(world_->findActor("Player"));
	std::list<Vector3> posits;
	for (auto& a : actors) {
		posits.push_back(a->position());
	}
	finalPosition_ = AvoidSearch::selectPoint(world_, position_, posits, &finalPoint_);
	score_.clear();
	nextPosition_ = AvoidSearch::Search(world_, position_, posits, finalPosition_,basePoint_, &nextPoint_, &score_);

}

void Enemy_Round::setCountDown(int downCount)
{
	if (state_ == Enemy_State::Down)return;
	BaseEnemy::setCountDown(downCount);
	selectPoint();
}
