#pragma once

#include"Vector2.h"
#include"Vector3.h"
#include"MathHelper.h"

class MathHelperSupport {
public:
	//�����Ɠ_�������镽�s�l�ӌ`�̖ʐς����߂�
	static float MathDistance_Segment_Point(const Vector3& seg_start, const Vector3& seg_end, const Vector3& point);

};