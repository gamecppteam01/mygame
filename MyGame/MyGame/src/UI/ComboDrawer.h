#pragma once
#include"UI.h"
#include"StepParts.h"
#include"../Actor/Player/Player_Animation.h"

#include<vector>

class ComboDrawer:public UI{
public:
	ComboDrawer();

	virtual void initialize();
	//çXêV
	virtual void update(float deltaTime);
	//ï`âÊ
	virtual void draw() const;

	virtual void Notify(Notification type, void* param = nullptr);

	void uiDead();
	void addStep(Player_Animation type);

	StepParts::DrawStepType chooseID(Player_Animation type);
private:
	std::vector<StepParts> stepUIs_;

	bool isCombo_{ false };
};