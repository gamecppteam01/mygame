#pragma once
#include "../Math/Math.h"

struct  WarningParamter
{
	WarningParamter() : warningPos_(Vector2::Zero),
		scale_(Vector2::Zero), angle_(0), origin_(Vector2::Zero) {

	}
	//�x���̏ꏊ
	Vector2 warningPos_;
	//�傫��
	Vector2 scale_;
	//�p�x
	float angle_;
	//���_
	Vector2 origin_;
};