#include "StepComboManager.h"
#include "../Input/Keyboard.h"

StepComboManager::StepComboManager(IWorld * world)
	:UI{ "StepComboManager", position_ }, world_(world)
{
	initialize();
}

void StepComboManager::initialize()
{
	stepcombo_.clear();
	stepNum_ = 0;
	cursorPos_ = Vector2(100.0f, 650.0f);
	target_ = std::static_pointer_cast<Player>(world_->findActor("Player"));
	position_ = Vector2(120.0f, 650.0f);
}

void StepComboManager::update(float deltaTime)
{
	int count = 0;
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::R)) {
		int step_ = 1;
		Notify(Notification::Call_ComboStep, (void*)&step_);
	}
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::T)) {
		int step_ = 2;
		Notify(Notification::Call_ComboStep, (void*)&step_);
	}
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Y)) {
		int step_ = 3;
		Notify(Notification::Call_ComboStep, (void*)&step_);
	}
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::U)) {
		int step_ = 4;
		Notify(Notification::Call_ComboStep, (void*)&step_);
	}

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::G)) {
		ClearData(std::vector<Player_Animation>{Player_Animation::Quarter});
	}

}

void StepComboManager::draw() const
{
	for (auto b : stepcombo_) {
		b->draw();
	}
}

void StepComboManager::Notify(Notification type, void * param)
{
	if (type == Notification::Call_ComboStep) {
		//プレイヤーが行ったステップが送られてくる
		stepNum_ = *(int*)param;
		switch (stepNum_)
		{
		case 1: {
			stepcombo_.push_back(std::make_shared<StepComboUI>(SPRITE_ID::QUATER_SPRITE, position_));
			break;
		}
		case 2: {
			stepcombo_.push_back(std::make_shared<StepComboUI>(SPRITE_ID::HALF_SPRITE, position_));
			break;
		}
		case 3: {
			stepcombo_.push_back(std::make_shared<StepComboUI>(SPRITE_ID::TURN_SPRITE, position_));
			break;
		}
		case 4: {
			stepcombo_.push_back(std::make_shared<StepComboUI>(SPRITE_ID::SPIN_SPRITE, position_));
			break;
		}

		default:
			break;
		}
		position_ += Vector2(120.0f, 0.0f);
	}
}

void StepComboManager::pause()
{
	IsPause = true;
}

void StepComboManager::restart()
{
	IsPause = false;
}

void StepComboManager::ClearData(std::vector<Player_Animation> playeranm)
{
	stepcombo_.clear();
	for (auto p : playeranm) {
		switch (p)
		{
		case Player_Animation::Quarter:
			stepcombo_.push_back(std::make_shared<StepComboUI>(SPRITE_ID::QUATER_SPRITE, position_));
			break;
		case Player_Animation::Turn:
			stepcombo_.push_back(std::make_shared<StepComboUI>(SPRITE_ID::TURN_SPRITE, position_));
			break;
		default:
			break;
		}
	}
	
}
