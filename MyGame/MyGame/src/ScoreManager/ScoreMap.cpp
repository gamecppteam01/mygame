#include "ScoreMap.h"
#include"../World/IWorld.h"
#include"../Actor/Judge/JudgeBase.h"
#include"../Judge/JudgeFunction.h"
#include"../Math/Random.h"
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
		judges_.push_back(std::static_pointer_cast<JudgeBase>(j));
	}
}

void ScoreMap::update(float deltaTime)
{
	//getNextPoint内で毎フレーム1回だけmathScoreRateを呼び出せるようにする
	//mathScoreRateTimer_.Initialize();
	//mathScoreRateTimer_.Add([this] {mathScoreRate(); });

	points_.loopElement([](ScorePoint& s) {
		s.alreadyChecked_ = false;
	}
	);
}

void ScoreMap::mathScoreRate()
{
	points_.loopElement([this](ScorePoint& s) {
		float nextRate = 1.0f;
		for (auto& j : judges_) {
			if (j->Judgement(s.position_)) {
				nextRate += 0.2f;
			}
		}
		s.rate_ = nextRate;
	}
	);
}

void ScoreMap::mathScoreRate(ScorePoint & point)
{
	//今回のフレームで計算が終了していたら戻る
	if (point.alreadyChecked_)return;

	float nextRate = 1.0f;
	for (auto& j : judges_) {
		if (j->Judgement(point.position_)) {
			nextRate += 0.2f;
		}
	}
	point.rate_ = nextRate;
	point.alreadyChecked_ = true;

}

Vector3 ScoreMap::getNextPoint(const Vector3 & point, float* resultRate)
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
	for (auto& p : points) {
		mathScoreRate(p);
	}

	float rate = 0.0f;
	std::vector<Vector3> nextList{ next };

	for (auto& i : points) {
		if (i.rate_ > rate) {
			nextList.clear();
			rate = i.rate_;
			nextList.push_back(i.position_);
		}
		else if (i.rate_ == rate) {
			nextList.push_back(i.position_);
		}
	}
	*resultRate = rate;
	next = nextList[Random::GetInstance().Range(0, nextList.size() - 1)];

	//points_.loopElement([this, &next,point](ScorePoint& s) {
	//	//対象ポイントが現在の次の行き先より近かったらそっちを適用
	//	if (Vector3::Distance(point, s.position_) < Vector3::Distance(point, next.position_)) {
	//		next = s;
	//	}
	//}
	//);

	return next;
}

std::vector<Vector3> ScoreMap::getRoundPoint()
{
	std::vector<Vector3> result;
	for (int i = 0; i < points_.getXSize(); i++) {
		//上の縦列
		result.push_back(points_.getElement(i, 0).position_);
	}
	for (int i = 1; i < points_.getYSize()-1; i++) {
		//右の横列
		result.push_back(points_.getElement(points_.getXSize() - 1, i).position_);
	}
	for (int i = points_.getXSize()-1; i >=0; i--) {
		//下の縦列
		result.push_back(points_.getElement(i,points_.getYSize()-1).position_);
	}
	for (int i = points_.getYSize() - 2; i >0 ; i--) {
		//左の横列
		result.push_back(points_.getElement(0, i).position_);
	}

	return result;
}
