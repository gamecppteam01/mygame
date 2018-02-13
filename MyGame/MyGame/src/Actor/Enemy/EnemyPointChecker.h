#pragma once
#include<vector>
#include<memory>

class IWorld;
struct Vector3;

class EnemyPointChecker {
public:

	static void setNearestPoint(IWorld* world, int& currentKey,int& nextKey, Vector3& nextPosition, const Vector3& position, const std::vector<Vector3>& points, int myNumber);
	static bool nextPosition_Round(IWorld* world, int& currentKey,int& nextKey, Vector3& nextPosition, const std::vector<Vector3>& points, int myNumber, const Vector3& center);
	static void to_NextPosition_Avoid(IWorld* world, int& currentKey, int& nextKey, Vector3& nextPosition, const std::vector<Vector3>& points, int myNumber);
};