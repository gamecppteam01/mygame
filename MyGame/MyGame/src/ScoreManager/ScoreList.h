#pragma once
#include<map>
#include"../Actor/Player/Step_Type.h"

//�X�e�b�v���̉��_���X�g
static const std::map<Step_Type, int> step_score_list{
	{ Step_Type::Chasse,100 },
	{ Step_Type::Whisk,200 },
	{ Step_Type::Turn,300 }
};
