#include "FieldGrid.h"
#include"../World/IWorld.h"
#include"../Math/MathHelper.h"

static const float gridSize{ 20.0f };

FieldGrid::FieldGrid(IWorld * world):world_(world)
{
}
//�|�C���g����
void FieldGrid::initialize()
{
	if (world_->getField() == nullptr)return;

	auto xSize = world_->getField()->getXWidth()*2.f;
	auto zSize = world_->getField()->getZWidth()*2.f;

	if ((int)xSize <= 0 && (int)zSize <= 0)return;

	addList_.clear();

	//�]����o���Ĕ����ɂ��鎖�ŁA�㉺�A���E�̒[�ɃY�����l
	auto  xsurplus = std::fmodf(xSize, gridSize)*0.5f;
	auto  zsurplus = std::fmodf(zSize, gridSize)*0.5f;
	
	fieldXZ_ = Vector2{ xSize - xsurplus,zSize - zsurplus };//�ꏊ���炵�T�C�Y�����

	//���o��x,z�̂��ꂼ��̃}�X�����o��
	int xCount = (int)std::roundf(xSize) / (int)std::roundf(gridSize);
	int zCount = (int)std::roundf(zSize) / (int)std::roundf(gridSize);
	
	//�����l�����
	float xCenter = xCount *0.5f;
	float zCenter = zCount *0.5f;

	//����(z�͉��ɉ����p)
	Vector3 centerPos{ xSize*0.5f,0.0f,-zSize*0.5f };

	//�[���܂߂邽�߃J�E���g����1�ǉ�(�f��ق̐Ȑ��ƃW���[�X�z���_�[���̊֌W�Ɠ����C���[�W)
	xCount++;
	zCount++;

	fieldGrid_.setSize(xCount, zCount);

	for (int x = 0; x < xCount; x++) {
		for (int z = 0; z < zCount; z++) {
			int subx = x - xCenter;
			int subz = z - zCenter;

			//z�͎�O�Ɏ����Ă���p
			Vector3 position{ x*gridSize,10.0f,-z*gridSize };
			position -= centerPos;
			position += Vector3{ xsurplus,0.0f,-zsurplus };

			//�X�R�A�͋���
			//float score = Vector2{ (float)subx,(float)subz }.Length();
			float score = 1.0f;//�X�R�A�ꗥ��

			fieldGrid_.getElement(x, z) = FieldChip(position, score, Point(x, z), true);
		}
	}
}

Point FieldGrid::getGridNum(const Vector3 & position)
{
	//�����l�����
	auto center = fieldXZ_ *0.5f;

	auto pos = Vector2{ position.x,position.z } +center;
	pos = Vector2::Clamp(pos, Vector2::Zero, fieldXZ_);
	auto divx = fieldXZ_.x / fieldGrid_.getXSize();
	auto divz = fieldXZ_.y / fieldGrid_.getYSize();

	int x = std::floorf(pos.x / divx);
	int z = std::floorf(pos.y / divz);
	x = MathHelper::Clamp(x, 0, fieldGrid_.getXSize() - 1);
	z = MathHelper::Clamp(fieldGrid_.getYSize() - 1 - z, 0, fieldGrid_.getYSize() - 1);

	return Point(x, z);
}

FieldChip FieldGrid::getGridChip(int x, int y,bool* isIn)
{
	if (x >= fieldGrid_.getXSize() || y >= fieldGrid_.getYSize()||x<0||y<0) {
		if (isIn != nullptr)*isIn = false;//�͈͊O
		return FieldChip();
	}
	if (isIn != nullptr)*isIn = true;//�͈͓�

	return fieldGrid_.getElement(x, y);
}

FieldChip FieldGrid::getGridChip(Point point, bool* isIn)
{
	if (point.x >= fieldGrid_.getXSize() || point.y >= fieldGrid_.getYSize() || point.x<0 || point.y < 0) {
		if (isIn != nullptr)*isIn = false;//�͈͊O
		return FieldChip();
	}
	if (isIn != nullptr)*isIn = true;//�͈͓�
	return getGridChip(point.x, point.y);
}

Point FieldGrid::getXYSize() const
{
	return Point(fieldGrid_.getXSize(), fieldGrid_.getYSize());
}

Vector2 FieldGrid::getFieldSize() const
{
	return fieldXZ_;
}

void FieldGrid::addCost(Point point)
{
	addList_.push_back(point);
	fieldGrid_.getElement(point.x, point.y).score += 1.0f;
}

void FieldGrid::resetCost()
{
	for (auto& p : addList_) {
		//fieldGrid_.getElement(p.x, p.y).score = 1.0f;
	}
}
