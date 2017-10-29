#pragma once
#include "../Math/Math.h"

struct  WarningParamter
{
	WarningParamter(const Vector2& warningPos=Vector2::Zero,const Vector2& scale=Vector2::One,float angle=0.0f,const Vector2& origin=Vector2::Zero) : 
		warningPos_(warningPos),
		scale_(scale), angle_(angle), origin_(origin) {

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