#include "StepComboManager.h"
#include "../Input/Keyboard.h"

static const Vector2 defaultPos_{ 120.0f,650.0f };
static const Vector2 PatternPos_{ 240.0f,650.0f };

StepComboManager::StepComboManager(IWorld * world)
	:UI{ "StepComboManager", position_ }, world_(world)
{
	initialize();
}

void StepComboManager::initialize()
{
	stepcombo_.clear();
	combo_ = Combo::first;
	stepNum_ = 0;
	step_ = 0;
	alpha_ = 0.2f;
	cursorPos_ = Vector2(100.0f, 650.0f);
	target_ = std::static_pointer_cast<Player>(world_->findActor("Player"));
	position_ = defaultPos_;
	patternPos_ = PatternPos_;
}

void StepComboManager::update(float deltaTime)
{
	int count = 0;
	
	for (auto &i : stepcombo_)
	{
		i->update(deltaTime);

		
	}
	
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::R)) {
		step_ = 1;
		Notify(Notification::Call_ComboStep, (void*)&step_);
		count++;
		if (count % 3 == 0) {
			count = 0;
			combo_ = Combo::second;
			alpha_ = 0.0f;
		}
	}
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::T)) {
		step_ = 2;
		Notify(Notification::Call_ComboStep, (void*)&step_);
		count++;
		if (count % 3 == 0) {
			count = 0;
		}
	}
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Y)) {
		step_ = 3;
		Notify(Notification::Call_ComboStep, (void*)&step_);
		count++;
		if (count % 3 == 0) {
			count = 0;
			combo_ = Combo::second;
			alpha_ = 0.0f;
		}
	}
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::U)) {
		step_ = 4;
		Notify(Notification::Call_ComboStep, (void*)&step_);
		count++;
		if (count % 3 == 0) {
			count = 0;
		}
	}

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::G)) {
		ClearData(std::vector<Player_Animation>{Player_Animation::Quarter});

	}
	if (stepcombo_.size() >= 4) ClearData(std::vector<Player_Animation>{})/*,combo_ = Combo::first*/;

	
}

void StepComboManager::draw() const
{
	for (auto b : stepcombo_) {
		b->draw();
		
		if (stepcombo_.empty())return;

		for (auto a : stepcombo_) {
			a->IsStart();
		}

		//ポイントアップコンボ
		/*if ((b->GetId() == SPRITE_ID::QUATER_SPRITE || b->GetId() == SPRITE_ID::TURN_SPRITE) && combo_ == Combo::first) {
			Sprite::GetInstance().Draw(SPRITE_ID::QUATER_SPRITE, patternPos_, alpha_);
			Sprite::GetInstance().Draw(SPRITE_ID::TURN_SPRITE, patternPos_ + Vector2(120.0f, 0.0f), alpha_);
		}
		if (b->GetId() == SPRITE_ID::QUATER_SPRITE && combo_ == second) {
			Sprite::GetInstance().Draw(SPRITE_ID::TURN_SPRITE, patternPos_ + Vector2(120.0f, 0.0f), 0.2f);
		}*/
		//バーストコンボ
		/*if (b->GetId() == SPRITE_ID::TURN_SPRITE && combo_ == Combo::first) {
			Sprite::GetInstance().Draw(SPRITE_ID::QUATER_SPRITE, patternPos_, alpha_);
			Sprite::GetInstance().Draw(SPRITE_ID::TURN_SPRITE, patternPos_ + Vector2(120.0f, 0.0f), alpha_);
		}
		if (b->GetId() == SPRITE_ID::QUATER_SPRITE && combo_ == second) {
			Sprite::GetInstance().Draw(SPRITE_ID::TURN_SPRITE, patternPos_ + Vector2(120.0f, 0.0f), 0.2f);
		}*/
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
	position_ = defaultPos_;
	stepcombo_.clear();
	for (auto p : playeranm) {
		switch (p)
		{
		case Player_Animation::Quarter:
			stepcombo_.push_back(std::make_shared<StepComboUI>(SPRITE_ID::QUATER_SPRITE, position_));
			position_ += Vector2(120.0f, 0.0f);
			break;
		case Player_Animation::Turn:
			stepcombo_.push_back(std::make_shared<StepComboUI>(SPRITE_ID::TURN_SPRITE, position_));
			position_ += Vector2(120.0f, 0.0f);
			break;
		default:
			break;
		}
	}

}
