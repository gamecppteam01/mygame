#pragma once
#include"UI.h"
#include"StepParts.h"
#include"../Actor/Player/Player_Animation.h"
#include"../Game/ID.h"

#include<vector>

class ComboDrawer:public UI{
	enum class SuccessComboType {
		None,
		PointUp,
		Burst
	};
public:
	ComboDrawer();
	virtual ~ComboDrawer(){}

	virtual void initialize();
	//çXêV
	virtual void update(float deltaTime);
	//ï`âÊ
	virtual void draw() const;

	virtual void Notify(Notification type, void* param = nullptr);

	void uiDead();
	void addStep(Player_Animation type);

	StepParts::DrawStepType chooseID(Player_Animation type);

protected:
	std::vector<StepParts> stepUIs_;

	SuccessComboType comboType_{ SuccessComboType::None };

	SPRITE_ID id_{ SPRITE_ID::COMBO_POINTUP_SPRITE };
	float alpha_{ 0.0f };
	bool isCombo_{ false };
};