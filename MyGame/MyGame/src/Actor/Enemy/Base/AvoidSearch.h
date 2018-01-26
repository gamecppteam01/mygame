#pragma once
#include"../../../Math/Vector3.h"
#include"../../../Math/Vector2.h"
#include"../../../Math/Point.h"
#include<list>

class IWorld;

struct TestDP {
	TestDP(Vector2 pos, float score) :pos(pos), score(score) {

	}
	Vector2 pos;
	float score;
};
class AvoidSearch {
public:	
	static Vector3 Search(IWorld* world, Vector3 position, const std::list<Vector3>& target,Vector3 finalPosition, Point& prevPoint, Point* pointptr = nullptr, std::list<TestDP>* dp=nullptr);

	static Vector3 selectPoint(IWorld* world, Vector3 position, const std::list<Vector3>& target, Point* pointptr = nullptr);
private:
	static int SearchAngleNum(float angle);//角度をキー番号に変換する(上が0右が2)
};