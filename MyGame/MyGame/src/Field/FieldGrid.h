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
	Vector3 position;//�}�X�̈ʒu
	float score;//�}�X���̂̎��X�R�A
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

	//�ʒu����L�[�ԍ���Ԃ�
	Point getGridNum(const Vector3& position);

	//�L�[�ԍ�����FieldChip��Ԃ�(�͈͓��̃f�[�^���������̃`�F�b�N���Ԃ�)
	FieldChip getGridChip(int x, int y,bool* isIn=nullptr);
	//�L�[�ԍ�����FieldChip��Ԃ�(�͈͓��̃f�[�^���������̃`�F�b�N���Ԃ�)
	FieldChip getGridChip(Point point, bool* isIn = nullptr);

	Point getXYSize()const;
	Vector2 getFieldSize()const;

	void addCost(Point point);//�R�X�g����
	void resetCost();//�R�X�g���Z�b�g
private:
	IWorld* world_;
	TwoDimensionalArray<FieldChip> fieldGrid_;

	std::list<Point> addList_;//�R�X�g���Z���X�g
	Vector2 fieldXZ_{ Vector2::Zero };
};