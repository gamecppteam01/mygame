#include "MathHelperSupport.h"

float MathHelperSupport::MathDistance_Segment_Point(const Vector3 & seg_start, const Vector3 & seg_end, const Vector3 & point)
{
	//線分と線分始点から点へのベクトルを作成
	Vector3 Seg, SegS_Point;
	Seg = seg_end - seg_start;
	SegS_Point = point - seg_start;
	
	//外積の長さを測る=面積
	float area = Vector3::Cross(Seg, SegS_Point).Length();
	//線分の長さを測る
	float seg_length = Vector3::Distance(seg_start, seg_end);

	return area / seg_length;

}
