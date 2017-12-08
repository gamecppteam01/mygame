#pragma once

#include"../Game/ID.h"
#include"../Math/Math.h"

struct ShadowMap_Data
{
	ShadowMap_Data() = default;
	ShadowMap_Data(const SHADOW_MAP_ID& id, const Point& size, Vector3& direction, Vector3& minpos, Vector3& maxpos, int slot)
		:Id(id), Size(size), Direction(direction), MinPos(minpos), MaxPos(maxpos), Slot(slot) {
	}
	//�V���h�E�}�b�v��ID
	SHADOW_MAP_ID Id;
	//�𑜓x
	Point Size;
	//���C�g�̕���
	Vector3 Direction;
	//���ʔ͈͂̍ŏ��l
	Vector3 MinPos;
	//���ʔ͈͂̍ő�l
	Vector3 MaxPos;
	//�g�p����X���b�g
	int Slot;
};