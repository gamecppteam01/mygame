#include "ScoreMap.h"
#include"../World/IWorld.h"
#include"../Actor/Judge/Judge_NPC/Judge_NPC.h"
#include"../Judge/JudgeFunction.h"
#include<list>

ScoreMap::ScoreMap(IWorld * world):world_(world)
{
}

ScoreMap::~ScoreMap()
{
	judges_.clear();
}

void ScoreMap::initialize()
{
	points_.loopElement([](ScorePoint& s) {s.rate_ = 1.0f; });

	judges_.clear();
	std::list<ActorPtr> judges;
	world_->findActors("Judge", judges);
	for (auto& j : judges) {
		judges_.push_back(std::static_pointer_cast<Judge_NPC>(j));
	}
}

void ScoreMap::update(float deltaTime)
{
	//getNextPoint内で毎フレーム1回だけmathScoreRateを呼び出せるようにする
	mathScoreRateTimer_.Initialize();
	mathScoreRateTimer_.Add([this] {mathScoreRate(); });
}

void ScoreMap::mathScoreRate()
{
	points_.loopElement([this](ScorePoint& s) {
		float nextRate = 1.0f;
		for (auto& j : judges_) {
			if (JudgeFunction::isInView(j->position(), s.position_, j->rotation(), j->getAngle())) {
				nextRate += 0.2f;
			}
		}
		s.rate_ = nextRate;
	}
	);
}

Vector3 ScoreMap::getNextPoint(const Vector3 & point)
{
	mathScoreRateTimer_.Action();

	Vector3 next = points_.getElement(0, 0).position_;

	auto targetKey=points_.getTargetKey([this,point](ScorePoint& s1, ScorePoint& s2) {
		return Vector3::Distance(point, s1.position_) > Vector3::Distance(point, s2.position_);
	});
	std::vector<ScorePoint> points{
		points_.getElement(targetKey.first,targetKey.second),//中心
		points_.getElement(targetKey.first,max(targetKey.second - 1,0)),//上
		points_.getElement(max(targetKey.first - 1,0),targetKey.second),//左
		points_.getElement(min(targetKey.first + 1,points_.getXSize() - 1),targetKey.second),//右
		points_.getElement(targetKey.first,min(targetKey.second + 1,points_.getYSize() - 1)),//下
	};

	float rate = 0.0f;
	for (auto& i : points) {
		if (i.rate_ > rate) {
			rate = i.rate_;
			next = i.position_;
		}
	}

	//points_.loopElement([this, &next,point](ScorePoint& s) {
	//	//対象ポイントが現在の次の行き先より近かったらそっちを適用
	//	if (Vector3::Distance(point, s.position_) < Vector3::Distance(point, next.position_)) {
	//		next = s;
	//	}
	//}
	//);

	return next;
}
