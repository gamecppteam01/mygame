#pragma once
#include "../Math/Math.h"

struct  WarningParamter
{
	WarningParamter(const Vector2& warningPos=Vector2::Zero,const Vector2& scale=Vector2::One,float angle=0.0f,const Vector2& origin=Vector2::Zero) : 
		warningPos_(warningPos),
		scale_(scale), angle_(angle), origin_(origin) {

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