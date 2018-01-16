#pragma once
#include"ComboDrawer.h"
#include<functional>

class TutorialComboDrawer :public ComboDrawer {
public:
	enum class DrawComboType {
		Burst,
		PointUp
	};
public:
	TutorialComboDrawer();

	void init(DrawComboType type);
	virtual void draw() const;

private:

	std::function<void(const std::vector<StepParts>& stepUIs_)> drawFunc_;
};