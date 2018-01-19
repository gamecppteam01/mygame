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
Enemy_Rival::Enemy_Rival():
	BaseEnemy("Enemy")
{
}
Enemy_Rival::Enemy_Rival(IWorld * world, const std::string & name, const Vector3 & position, int playerNumber, const IBodyPtr & body) :
	BaseEnemy(world, name, position, playerNumber, body, MODEL_ID::RIVALENEMY_MODEL, MODEL_ID::RIVALENEMY_BULLET_MODEL) {

	roundPoint_ = world_->getCanChangedScoreMap().getRoundPoint();
	targetPos_ = world_->getCanChangedScoreMap().getNearestBonusPoint(centerPosition_);

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

}

std::shared_ptr<BaseEnemy> Enemy_Rival::Create(IWorld * world, const Vector3 & position, int playerNumber)
{
	return std::make_shared<Enemy_Rival>(world, "Enemy", position, playerNumber);
}

void Enemy_Rival::onDraw() const
{
	BaseEnemy::onDraw();
	//world_->setLateDraw([this] {
	//	switch (chooseAttackTargetMode_)
	//	{
	//	case Enemy_Rival::chooseAttackTargetMode::NotAttack:
	//		DebugDraw::DebugDrawFormatString(400, 300, GetColor(255, 255, 255), "NotAttack");
	//		break;
	//	case Enemy_Rival::chooseAttackTargetMode::AttackMove:
	//		DebugDraw::DebugDrawFormatString(400, 300, GetColor(255, 255, 255), "AttackMove");
	//		break;
	//	case Enemy_Rival::chooseAttackTargetMode::Attack:
	//		DebugDraw::DebugDrawFormatString(400, 300, GetColor(255, 255, 255), "Attack");
	//		break;
	//	case Enemy_Rival::chooseAttackTargetMode::Return:
	//		DebugDraw::DebugDrawFormatString(400, 300, GetColor(255, 255, 255), "Return");
	//		break;
	//	case Enemy_Rival::chooseAttackTargetMode::Step:
	//		DebugDraw::DebugDrawFormatString(400, 300, GetColor(255, 255, 255), "Step");
	//		break;
	//	case Enemy_Rival::chooseAttackTargetMode::StepMove:
	//		DebugDraw::DebugDrawFormatString(400, 300, GetColor(255, 255, 255), "StepMove");
	//		break;
	//	default:
	//		break;
	//	}
	//	DebugDraw::DebugDrawFormatString(350, 300, GetColor(255, 255, 255), "%d", rhythmTimeCount_);
	//	
	//	DebugDraw::DebugDrawFormatString(600, 400, GetColor(255, 255, 255), "%f:%f:%f", centerPosition_.x, centerPosition_.y, centerPosition_.z);
	//});
}

void Enemy_Rival::onShadowDraw() const
{
	//判定の中心に描画位置を合わせる
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	animation_.Draw(Matrix(Matrix::Identity)*Matrix(rotation_).Translation(drawPosition));
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

void Enemy_Rival::to_Normal()
{
	targetPos_ = world_->getCanChangedScoreMap().getNearestBonusPoint(centerPosition_);
	//setNextPosition();
	speedEaseTimer_ = 0.0f;
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