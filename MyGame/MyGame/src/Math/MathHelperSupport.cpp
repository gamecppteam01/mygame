#include "MathHelperSupport.h"

float MathHelperSupport::MathDistance_Segment_Point(const Vector3 & seg_start, const Vector3 & seg_end, const Vector3 & point)
{
	//�����Ɛ����n�_����_�ւ̃x�N�g�����쐬
	Vector3 Seg, SegS_Point;
	Seg = seg_end - seg_start;
	SegS_Point = point - seg_start;
	
	//�O�ς̒����𑪂�=�ʐ�
	float area = Vector3::Cross(Seg, SegS_Point).Length();
	//�����̒����𑪂�
	float seg_length = Vector3::Distance(seg_start, seg_end);

	return area / seg_length;

}
