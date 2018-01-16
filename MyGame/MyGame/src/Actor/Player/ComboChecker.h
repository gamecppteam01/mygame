#pragma once
#include"Player_Animation.h"
#include<vector>

class IWorld;
class ComboChecker {
public:
	enum class ComboType {
		Combo_PointUp,
		Combo_Burst,
		Combo_None
	};
	static ComboType checkCombo(std::vector<Player_Animation>& comboList, Player_Animation next, IWorld* world);
	static ComboType checkComboTutorial(std::vector<Player_Animation>& comboList, Player_Animation next, IWorld* world, ComboType type);
	static ComboType checkComboBurst(std::vector<Player_Animation>& comboList, Player_Animation next, IWorld* world);
	static ComboType checkComboPointUp(std::vector<Player_Animation>& comboList, Player_Animation next, IWorld* world);
	static ComboType checkCombo(std::vector<Player_Animation>& comboList);

private:
	static const std::vector<Player_Animation> pointUp;
	static const std::vector<Player_Animation> burst;
};