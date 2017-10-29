#pragma once
#include "../Math/Math.h"

struct  WarningParamter
{
	WarningParamter(const Vector2& warningPos=Vector2::Zero,const Vector2& scale=Vector2::One,float angle=0.0f,const Vector2& origin=Vector2::Zero) : 
		warningPos_(warningPos),
		scale_(scale), angle_(angle), origin_(origin) {

	}
	//Œx‚ÌêŠ
	Vector2 warningPos_;
	//‘å‚«‚³
	Vector2 scale_;
	//Šp“x
	float angle_;
	//Œ´“_
	Vector2 origin_;
};