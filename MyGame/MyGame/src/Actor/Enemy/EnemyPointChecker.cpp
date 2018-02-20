#include "EnemyPointChecker.h"
#include"../../World/IWorld.h"
#include"../../Math/Vector3.h"
#include"../Body/BoundingSegment.h"
#include"../Body/Base/HitInfo.h"
#include"BaseEnemy.h"

void EnemyPointChecker::setNearestPoint(IWorld* world,int& currentKey,int & nextKey, Vector3 & nextPosition,const Vector3& position, const std::vector<Vector3>& points, int myNumber)
{
	if (points.empty()||world==nullptr)return;
	std::list<std::weak_ptr<Actor>> enemys;
	world->findActors("Enemy",enemys);

	std::list<int> noneTargetPoints_;
	for (auto& e : enemys) {
		if (std::static_pointer_cast<BaseEnemy>(e.lock())->getPlayerNumber() == myNumber)continue;
		noneTargetPoints_.push_back(std::static_pointer_cast<BaseEnemy>(e.lock())->getNextKey());
		noneTargetPoints_.push_back(std::static_pointer_cast<BaseEnemy>(e.lock())->getCurrentKey());
	}

	nextPosition = points.front();
	currentKey = nextKey;
	nextKey = 0;
	int i = 0;
	for (auto& p : points) {
		if (std::find(noneTargetPoints_.begin(), noneTargetPoints_.end(), i) == noneTargetPoints_.end()) {
			if (Vector3::Distance(nextPosition, position) > Vector3::Distance(p, position)) {
				nextPosition = p;
				nextKey = i;
			}
		}
		i++;
	}
}

bool EnemyPointChecker::nextPosition_Round(IWorld* world, int& currentKey, int & nextKey, Vector3 & nextPosition, const std::vector<Vector3>& points, int myNumber,const Vector3& center)
{
	bool result = false;
	if (points.empty() || world == nullptr)return result;

	std::list<std::weak_ptr<Actor>> enemys;
	world->findActors("Enemy", enemys);
	enemys.push_back(world->findActor("Player"));
	enemys.remove_if([&](auto& e) {return e.lock()->getPlayerNumber() == myNumber; });
	enemys.remove_if([&](auto& e) {return Vector3::Distance(center, e.lock()->position()) >= 100.0f; });

	//“G‚Ì–Ú“I’n‚ðŽæ“¾
	std::list<int> noneTargetPoints_;
	currentKey = nextKey;
	if (Vector3::Distance(center,nextPosition)<=10.0f) {
		nextKey = (nextKey - 1 + points.size()) % points.size();
		nextPosition = points[nextKey];
		result = true;
	}
	goto FIRST;

CHECK_ROUTE:
	if (nextKey == currentKey) {
		if (result) {
			nextKey = (nextKey - 1 + points.size()) % points.size();
			nextPosition = points[nextKey];
		}
		return result;
	}
FIRST:
	for (auto& e : enemys) {
		Vector3 toSeg = (nextPosition - center).Normalize()*100.0f;
		toSeg.y = 0.0f;
		BoundingSegment seg(center, center + toSeg);
		BoundingCapsule cap(e.lock()->position(), Matrix::Identity, 20.0f, 15.0f);
		HitInfo info;

		if (cap.intersects(seg, info)) {
			nextKey = (nextKey - 1 + points.size()) % points.size();
			nextPosition = points[nextKey];
			goto CHECK_ROUTE;
		}
	}
	
	//for (auto& e : enemys) {
	//	if ((e.lock())->getPlayerNumber() == myNumber)continue;
	//	if (Vector3::Distance(center, e.lock()->position()) >= 50.0f)continue;


	//	while (true) {
	//		BoundingSegment seg(center, nextPosition);
	//		HitInfo info;

	//		if (!e.lock()->getBody()->intersects(seg, info))break;
	//		if (currentKey == nextKey) {
	//			nextKey = (nextKey - 1 + points.size()) % points.size();
	//			nextPosition = points[nextKey];
	//			break;
	//		}
	//		nextKey = (nextKey - 1 + points.size()) % points.size();
	//		nextPosition = points[nextKey];

	//	}
	//}

	return result;
}


