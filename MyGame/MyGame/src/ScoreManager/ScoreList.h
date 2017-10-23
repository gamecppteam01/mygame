#pragma once
#include<map>
#include"../Actor/Player/Step_Type.h"

//ステップ毎の加点リスト
static const std::map<Step_Type, int> step_score_list{
	{ Step_Type::Chasse,100 },
	{ Step_Type::Whisk,200 },
	{ Step_Type::Turn,300 }
};
