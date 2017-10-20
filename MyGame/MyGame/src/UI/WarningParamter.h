#pragma once
#include "../Math/Math.h"

struct  WarningParamter
{
	WarningParamter() : warningPos_(Vector2::Zero),
		scale_(Vector2::Zero), angle_(0), origin_(Vector2::Zero) {

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