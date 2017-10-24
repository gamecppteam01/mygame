#pragma once
#include"../Math/Math.h"

class JudgeFunction {
public:

	static bool isInView(const Vector3& myPosition,const Vector3& targetPosition, const Matrix& myRotation,float viewAngle) {

		//�^�[�Q�b�g�����̃x�N�g��
		Vector3 toTarget = targetPosition - myPosition;
		//�p�x�����߂�
		float forwardAngle = MathHelper::ACos(Vector3::Dot(myRotation.Forward().Normalize(), toTarget.Normalize()));
		float leftAngle = MathHelper::ACos(Vector3::Dot(myRotation.Left().Normalize(), toTarget.Normalize()));

		//�͈͓����ǂ���
		return forwardAngle <= viewAngle;
	}
};