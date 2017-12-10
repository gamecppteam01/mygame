#include "ScoreMap.h"
#include"../World/IWorld.h"
#include"../Actor/Judge/JudgeBase.h"
#include"../Judge/JudgeFunction.h"
#include"../Math/Random.h"
#include"ScoreManager.h"
#include<list>

ScoreMap::ScoreMap(IWorld * world):world_(world)
{
	//とりあえずスコアポイントの周回分を入れておく
	roundPoints_.push_back(points_.getElement(0, 0).position_);
	roundPoints_.push_back(points_.getElement(1, 0).position_);
	roundPoints_.push_back(Vector3{ 0.0f,10.0f,0.0f });
	roundPoints_.push_back(points_.getElement(2, 0).position_);
	roundPoints_.push_back(points_.getElement(3, 0).position_);
	roundPoints_.push_back(points_.getElement(3, 1).position_);
	roundPoints_.push_back(points_.getElement(3, 2).position_);
	roundPoints_.push_back(points_.getElement(3, 3).position_);
	roundPoints_.push_back(points_.getElement(2, 3).position_);
	roundPoints_.push_back(points_.getElement(1, 3).position_);
	roundPoints_.push_back(points_.getElement(0, 3).position_);
	roundPoints_.push_back(points_.getElement(0, 2).position_);
	roundPoints_.push_back(points_.getElement(0, 1).position_);
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
	resetList_.clear();
}

void ScoreMap::update(float deltaTime)
{
	//getNextPoint内で毎フレーム1回だけmathScoreRateを呼び出せるようにする
	//mathScoreRateTimer_.Initialize();
	//mathScoreRateTimer_.Add([this] {mathScoreRate(); });

	for (auto i : resetList_) {
		points_.getElement(i.first, i.second).alreadyChecked_ = false;
	}
}

void ScoreMap::mathScoreRate()
{
	return;
	points_.loopElement([this](ScorePoint& s) {
		float nextRate = 1.0f;
		for (auto& j : judges_) {
			if (j.lock()->Judgement(s.position_)) {
				nextRate += 0.2f;
			}
		}
		s.rate_ = nextRate;
	}
	);
}

float ScoreMap::mathScoreRate(ScorePoint & point)
{
	//今回のフレームで計算が終了していたら戻る
	if (point.alreadyChecked_)return point.rate_;
	
	point.rate_ = world_->getScoreManager().mathScoreRata_All(point.position_);
	point.alreadyChecked_ = true;

	return point.rate_;
}

Vector3 ScoreMap::getNextPoint(const Vector3 & point, float* resultRate)
{
	//スコアレートの計算
	//mathScoreRateTimer_.Action();

	float nearest = Vector3::Distance(point, points_.getElement(0, 0).position_)+1.f;
	std::list<std::pair<int, int>> pointList;
	if (point.x > 0.0f) {
		//右上
		if (point.z > 0.0f) {
			pointList.push_back(std::make_pair(2, 2));
			pointList.push_back(std::make_pair(2, 3));
			pointList.push_back(std::make_pair(3, 2));
			pointList.push_back(std::make_pair(3, 3));
		}
		//右下
		else {
			pointList.push_back(std::make_pair(0, 2));
			pointList.push_back(std::make_pair(0, 3));
			pointList.push_back(std::make_pair(1, 2));
			pointList.push_back(std::make_pair(1, 3));
		}
	}
	else {
		//左上
		if (point.z > 0.0f) {
			pointList.push_back(std::make_pair(2, 0));
			pointList.push_back(std::make_pair(2, 1));
			pointList.push_back(std::make_pair(3, 0));
			pointList.push_back(std::make_pair(3, 1));
		}
		//左下
		else {
			pointList.push_back(std::make_pair(0, 1));
			pointList.push_back(std::make_pair(0, 2));
			pointList.push_back(std::make_pair(1, 1));
			pointList.push_back(std::make_pair(1, 2));
		}
	}
	//自身の位置に一番近いポイントを検索
	std::pair<int, int> targetKey{ 0,0 };
	for (auto& pl : pointList) {
		float dist = Vector3::Distance(point, points_.getElement(pl.first,pl.second).position_);
		if (nearest > dist) {
			nearest = dist;
			targetKey = pl;
		}

	}
	//自身の位置に一番近いポイントを検索
//	auto targetKey = points_.getTargetKey([this, point,&nearest](ScorePoint& s1, ScorePoint& s2) {
//		float dist = Vector3::Distance(point, s2.position_);
//		if (nearest > dist) {
//			nearest = dist;
//			return true;
//		}
//		else return false;
//		}); 
//ポイントの周囲のスコアをまとめて
std::vector<ScorePoint> points{
	points_.getElement(targetKey.first,targetKey.second),//中心
	points_.getElement(targetKey.first,max(targetKey.second - 1,0)),//上
	points_.getElement(max(targetKey.first - 1,0),targetKey.second),//左
	points_.getElement(min(targetKey.first + 1,points_.getXSize() - 1),targetKey.second),//右
	points_.getElement(targetKey.first,min(targetKey.second + 1,points_.getYSize() - 1)),//下
};

float maxrate = 0.0f;
Vector3 next = points.front().position_;

//スコアを検索
for (auto& p : points) {
	float rate = mathScoreRate(p);
	if (rate > maxrate) {
		maxrate = rate;
		next = p.position_;
	}
	else if (rate == maxrate) {
		if (Random::GetInstance().Range(0, 1) == 0)continue;

		maxrate = rate;
		next = p.position_;

	}
}
resetList_.push_back(targetKey);
resetList_.push_back(std::make_pair(targetKey.first, max(targetKey.second - 1, 0)));
resetList_.push_back(std::make_pair(max(targetKey.first - 1, 0), targetKey.second));
resetList_.push_back(std::make_pair(min(targetKey.first + 1, points_.getXSize() - 1), targetKey.second));
resetList_.push_back(std::make_pair(targetKey.first, min(targetKey.second + 1, points_.getYSize() - 1)));

//float rate = 0.0f;
//std::vector<Vector3> nextList{ next };

////スコアが高いところを探して
//for (auto& i : points) {
//	if (i.rate_ > rate) {
//		nextList.clear();
//		rate = i.rate_;
//		nextList.push_back(i.position_);
//	}
//	else if (i.rate_ == rate) {
//		nextList.push_back(i.position_);
//	}
//}

//スコア倍率と次のポイントを返す
*resultRate = maxrate;

//points_.loopElement([this, &next,point](ScorePoint& s) {
//	//対象ポイントが現在の次の行き先より近かったらそっちを適用
//	if (Vector3::Distance(point, s.position_) < Vector3::Distance(point, next.position_)) {
//		next = s;
//	}
//}
//);

return next;
}

Vector3 ScoreMap::getNearestBonusPoint(const Vector3 & point)
{
	std::list<std::pair<int, int>> pointList;
	if (point.x > 0.0f) {
		//右上
		if (point.z > 0.0f) {
			pointList.push_back(std::make_pair(2, 2));
			pointList.push_back(std::make_pair(2, 3));
			pointList.push_back(std::make_pair(3, 2));
			pointList.push_back(std::make_pair(3, 3));
		}
		//右下
		else {
			pointList.push_back(std::make_pair(0, 2));
			pointList.push_back(std::make_pair(0, 3));
			pointList.push_back(std::make_pair(1, 2));
			pointList.push_back(std::make_pair(1, 3));
		}
	}
	else {
		//左上
		if (point.z > 0.0f) {
			pointList.push_back(std::make_pair(2, 0));
			pointList.push_back(std::make_pair(2, 1));
			pointList.push_back(std::make_pair(3, 0));
			pointList.push_back(std::make_pair(3, 1));
		}
		//左下
		else {
			pointList.push_back(std::make_pair(0, 1));
			pointList.push_back(std::make_pair(0, 2));
			pointList.push_back(std::make_pair(1, 1));
			pointList.push_back(std::make_pair(1, 2));
		}
	}
	float rate = 0.0f;
	Vector3 next = points_.getElement(pointList.front().first, pointList.front().second).position_;
	for (auto& p : pointList) {
		if (points_.getElement(p.first, p.second).rate_ > rate) {
			rate = points_.getElement(p.first, p.second).rate_;
			next = points_.getElement(p.first, p.second).position_;
		}
	}
	return next;
	//float rate = 0.f;
	//std::vector<std::pair<int, int>> points;
	//int x = points_.getXSize();
	//int i = 0;
	//for (auto& dp : points_.getAllDataPtr()) {
	//	if (dp->rate_ > rate) {
	//		rate = dp->rate_;
	//		points.clear();
	//		points.push_back({ i%x,i / x });
	//	}
	//	else if(dp->rate_==rate){
	//		points.push_back({ i%x,i / x });
	//	}
	//	i++;
	//}
	//int key = Random::GetInstance().Range(0, points.size() - 1);


	//return points_.getElement(points[key].first, points[key].second).position_;
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

std::vector<Vector3> ScoreMap::getEnemy_Round_CrawlPoint()
{
	return roundPoints_;
}
