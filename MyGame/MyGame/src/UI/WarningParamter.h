#pragma once
#include "../Math/Math.h"

struct  WarningParamter
{
	WarningParamter() : warningPos_(Vector2::Zero),
		scale_(Vector2::Zero), angle_(0), origin_(Vector2::Zero) {

	}
	//警告の場所
	Vector2 warningPos_;
	//大きさ
	Vector2 scale_;
	//角度
	float angle_;
	//原点
	Vector2 origin_;
};