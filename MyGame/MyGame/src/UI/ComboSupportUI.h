#pragma once
#include<vector>

struct Vector2;
class StepParts;
class ComboSupportUI {
public:

	static void drawCombo(const std::vector<StepParts>& stepUIs_);
	static void drawComboPointUp(const std::vector<StepParts>& stepUIs_);
	static void drawComboBurst(const std::vector<StepParts>& stepUIs_);

};