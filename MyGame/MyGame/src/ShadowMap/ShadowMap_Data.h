#pragma once

#include"../Game/ID.h"
#include"../Math/Math.h"

struct ShadowMap_Data
{
	ShadowMap_Data() = default;
	ShadowMap_Data(const SHADOW_MAP_ID& id, const Point& size, Vector3& direction, Vector3& minpos, Vector3& maxpos, int slot)
		:Id(id), Size(size), Direction(direction), MinPos(minpos), MaxPos(maxpos), Slot(slot) {
	}
	//シャドウマップのID
	SHADOW_MAP_ID Id;
	//解像度
	Point Size;
	//ライトの方向
	Vector3 Direction;
	//効果範囲の最小値
	Vector3 MinPos;
	//効果範囲の最大値
	Vector3 MaxPos;
	//使用するスロット
	int Slot;
};