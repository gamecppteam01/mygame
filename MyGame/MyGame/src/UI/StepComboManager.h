#pragma once
#include "../World/IWorld.h"
#include "../Math/Math.h"
#include "../UI/UI.h"
#include "../Graphic/Sprite.h"
#include "../Actor/Player/Player.h"
#include "ComboStepUIPtr.h"
#include"StepComboUI.h"
#include "../Actor/Player/Player_Animation.h"
#include <vector>
#include <map>


class StepComboManager : public UI {
public:
	StepComboManager() = default;
	StepComboManager(IWorld * world);
	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw() const override;
	virtual void Notify(Notification type, void* param = nullptr);
	virtual void pause() override;
	virtual void restart() override;

	void ClearData(std::vector<Player_Animation> playeranm);

private:
	IWorld * world_;
	std::vector<StepComboUIPtr> stepcombo_;
	std::shared_ptr<Player> target_;
	int stepNum_;
	Vector2 cursorPos_;
	bool IsPause{ false };

};