#pragma once
#include"Field.h"
#include"../Math/TwoDimensionalArray.h"
#include"../Math/Vector3.h"
#include"../Math/Vector2.h"
#include"../Math/Point.h"
#include<list>

struct FieldChip {
	FieldChip(const Vector3& position = Vector3::Zero, float score = 0.0f, Point point = Point(-1, -1), bool isIn = false) :position(position), score(score), isIn(isIn), point(point) {
	}
	Vector3 position;//マスの位置
	float score;//マス自体の持つスコア
	bool isIn;
	Point point;
};

class FieldChipSort {
public:
	bool operator ()(const FieldChip& c1, const FieldChip& c2) {
		return c1.score < c2.score;
	}
};
class IWorld;
class FieldGrid {
public:
	FieldGrid(IWorld* world);

	void initialize();

	//位置からキー番号を返す
	Point getGridNum(const Vector3& position);

	//キー番号からFieldChipを返す(範囲内のデータだったかのチェックも返す)
	FieldChip getGridChip(int x, int y,bool* isIn=nullptr);
	//キー番号からFieldChipを返す(範囲内のデータだったかのチェックも返す)
	FieldChip getGridChip(Point point, bool* isIn = nullptr);

	Point getXYSize()const;
	Vector2 getFieldSize()const;

	void addCost(Point point);//コスト増加
	void resetCost();//コストリセット
private:
	IWorld* world_;
	TwoDimensionalArray<FieldChip> fieldGrid_;

	std::list<Point> addList_;//コスト加算リスト
	Vector2 fieldXZ_{ Vector2::Zero };
};