#pragma once

#include"Vector2.h"
#include"Vector3.h"
#include"MathHelper.h"

class MathHelperSupport {
public:
	//線分と点から作られる平行四辺形の面積を求める
	static float MathDistance_Segment_Point(const Vector3& seg_start, const Vector3& seg_end, const Vector3& point);

};