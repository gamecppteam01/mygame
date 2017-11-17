#pragma once
#include"../Math/Math.h"
struct JudgeMapData{
	JudgeMapData(){}
	JudgeMapData(Vector2 position,float rotation){
		position_ = position;
		rotation_ = rotation;
	}
	Vector2 position_;
	float rotation_;
};