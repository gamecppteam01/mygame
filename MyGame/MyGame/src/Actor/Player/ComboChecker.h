#pragma once
#include"Player_Animation.h"
#include<vector>

class ComboChecker {
public:
	enum class ComboType {
		Combo_PointUp,
		Combo_Burst,
		Combo_None
	};
	static ComboType checkCombo(std::vector<Player_Animation>& comboList);

private:
	static const std::vector<Player_Animation> pointUp;
	static const std::vector<Player_Animation> burst;
};