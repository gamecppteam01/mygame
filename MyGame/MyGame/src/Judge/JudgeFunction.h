#pragma once
#include"../Math/Math.h"

class JudgeFunction {
public:

	static bool isInView(const Vector3& myPosition,const Vector3& targetPosition, const Matrix& myRotation,float viewAngle) {

		//ターゲット方向のベクトル
		Vector3 toTarget = targetPosition - myPosition;
		//角度を求める
		float forwardAngle = MathHelper::ACos(Vector3::Dot(myRotation.Forward().Normalize(), toTarget.Normalize()));
		float leftAngle = MathHelper::ACos(Vector3::Dot(myRotation.Left().Normalize(), toTarget.Normalize()));

		//範囲内かどうか
		return forwardAngle <= viewAngle;
	}
};