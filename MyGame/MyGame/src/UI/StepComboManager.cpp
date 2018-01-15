#include "StepComboManager.h"
#include "../Input/Keyboard.h"


static const Vector2 defaultPos_{ 100.0f,600.0f };
static const Vector2 PatternPos_{ 150.0f,600.0f };

StepComboManager::StepComboManager(IWorld * world)
	:UI{ "StepComboManager", position_ }, world_(world)
{
	initialize();
}

void StepComboManager::initialize()
{
	stepcombo_.clear();
	stepNum_ = 0;
	step_ = 0;
	alpha_ = 0.5f;
	alpha2_ = 1.0f;
	cursorPos_ = Vector2(100.0f, 600.0f);
	target_ = std::static_pointer_cast<Player>(world_->findActor("Player"));
	position_ = defaultPos_;
	patternPos_ = PatternPos_;
	
}

void StepComboManager::update(float deltaTime)
{
	for (auto &i : stepcombo_)
	{
		i->update(deltaTime);

		if ((stepcombo_.size() == 1 && (i->GetId() != SPRITE_ID::QUATER_SPRITE || i->GetId() != SPRITE_ID::TURN_SPRITE))) {
			alpha_ = 0.0f;
		}
		if ((stepcombo_.size() == 2 && (i->GetId() != SPRITE_ID::QUATER_SPRITE))) {
			alpha_ = 0.0f;
		}
	}
	
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::R)) {
		step_ = 1;
		Notify(Notification::Call_ComboStep, (void*)&step_);
	}
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::T)) {
		step_ = 2;
		Notify(Notification::Call_ComboStep, (void*)&step_);
	}
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Y)) {
		step_ = 3;
		Notify(Notification::Call_ComboStep, (void*)&step_);
	}
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::U)) {
		step_ = 4;
		Notify(Notification::Call_ComboStep, (void*)&step_);
	}

	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::V)) {
		IsPCheck = true;
	}
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::B)) {
		IsBCheck = true;
	}

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::G)) {
		ClearData(std::vector<Player_Animation>{Player_Animation::Quarter});
	}
	if (stepcombo_.size() >= 4) ClearData(std::vector<Player_Animation>{}), alpha_ = 0.5f;
	
}

void StepComboManager::draw() const
{
	//if (stepcombo_.empty())return;

	for (auto b : stepcombo_) {
		b->draw();
		if (stepcombo_.front()->GetId() == SPRITE_ID::QUATER_SPRITE) {
			Sprite::GetInstance().Draw(SPRITE_ID::QUATER_SPRITE, patternPos_ + Vector2(150.0f, 0.0f), alpha_);
			Sprite::GetInstance().Draw(SPRITE_ID::TURN_SPRITE, patternPos_ + Vector2(350.0f, 0.0f), alpha_);
		}
		if (stepcombo_.front()->GetId() == SPRITE_ID::TURN_SPRITE) {
			Sprite::GetInstance().Draw(SPRITE_ID::QUATER_SPRITE, patternPos_ + Vector2(150.0f, 0.0f), alpha_);
			Sprite::GetInstance().Draw(SPRITE_ID::TURN_SPRITE, patternPos_ + Vector2(350.0f, 0.0f), alpha_);
		}

		for (auto a : stepcombo_) {
			a->IsStart();
		}
	}

	if (IsBCheck == true) {
		Sprite::GetInstance().Draw(SPRITE_ID::BURST_SPRITE, position_, 1.0f);
		Sprite::GetInstance().Draw(SPRITE_ID::TURN_SPRITE, position_, 1.0f);
		Sprite::GetInstance().Draw(SPRITE_ID::QUATER_SPRITE, position_ + Vector2(200.0f,0.0f), 1.0f);
		Sprite::GetInstance().Draw(SPRITE_ID::TURN_SPRITE, position_ + Vector2(400.0f,0.0f), 1.0f);
	}
	if (IsPCheck == true) {
		Sprite::GetInstance().Draw(SPRITE_ID::POINTUP_SPRITE, position_, alpha2_);
		Sprite::GetInstance().Draw(SPRITE_ID::QUATER_SPRITE, position_, alpha2_);
		Sprite::GetInstance().Draw(SPRITE_ID::QUATER_SPRITE, position_ + Vector2(200.0f, 0.0f), alpha2_);
		Sprite::GetInstance().Draw(SPRITE_ID::TURN_SPRITE, position_ + Vector2(400.0f, 0.0f), alpha2_);
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
		position_ += Vector2(200.0f, 0.0f);
	}

	if (type == Notification::Call_Success_Combo_Burst) {
		IsBCheck = true;
	}
	if (type == Notification::Call_Success_Combo_PointUp) {
		IsPCheck = true;
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
	position_ = defaultPos_;
	stepcombo_.clear();
	for (auto &q : stepcombo_) {
		q->IsEnd();
	}
	for (auto p : playeranm) {
		switch (p)
		{
		case Player_Animation::Quarter:
			stepcombo_.push_back(std::make_shared<StepComboUI>(SPRITE_ID::QUATER_SPRITE, position_));
			position_ += Vector2(200.0f, 0.0f);
			break;
		case Player_Animation::Turn:
			stepcombo_.push_back(std::make_shared<StepComboUI>(SPRITE_ID::TURN_SPRITE, position_));
			position_ += Vector2(200.0f, 0.0f);
			break;
		default:
			break;
		}
	}

}
