#include "SpecifiedStepManager.h"
#include "SpecifiedDraw.h"

SpecifiedStepManager::SpecifiedStepManager(IWorld * world)
	: UI{ "SpecifiedStepManager", position_ }, world_(world)
{
	initialize();
}

void SpecifiedStepManager::initialize()
{
	reciveList_.clear();
	stepMap.clear();
	step_ = stepState::NONE;
	cursorPos_ = Vector2(110.0f, 720.0f);
	target_ = std::static_pointer_cast<Player>(world_->findActor("Player"));
	position_ = Vector2(100.0f, 750.0f);
		
	
}

void SpecifiedStepManager::update(float deltaTime)
{
	//stepMathingと一致したら消す
	if (stepMatching() == 1) ;
	if (stepMatching() == 2) ;
	if (stepMatching() == 3) ;
	if (stepMatching() == 4) ;

}

void SpecifiedStepManager::draw() const
{
	for (auto a : stepdraw_) {
		a->draw();
	}
}

void SpecifiedStepManager::Notify(Notification type, void * param)
{
	//イベントメッセージで飛んできた値を格納する
	if (type == Notification::Call_ReciveStep) {
		reciveStep_ = *(int*)param;
		
		switch (reciveStep_)
		{
		case 1: {
			stepdraw_.push_back(std::make_shared<SpecifiedDraw>(SPRITE_ID::QUATER_SPRITE, position_));
			break;
		}
		case 2: {
			stepdraw_.push_back(std::make_shared<SpecifiedDraw>(SPRITE_ID::HALF_SPRITE, position_));
			break;
		}
		case 3: {
			stepdraw_.push_back(std::make_shared<SpecifiedDraw>(SPRITE_ID::TURN_SPRITE, position_));
			break;
		}
		case 4: {
			stepdraw_.push_back(std::make_shared<SpecifiedDraw>(SPRITE_ID::SPIN_SPRITE, position_));
			break;
		}

		default:
			break;
		}
		position_ += Vector2(50.0f, 0.0f);
	}
	
}

void SpecifiedStepManager::pause()
{
	IsPause = true;
}

void SpecifiedStepManager::restart()
{
	IsPause = false;
}

int SpecifiedStepManager::stepMatching()
{
	//ステップ １クオーター、２ハーフ、３ターン、４スピン
	if (target_->getStep() == 1 && target_->getState() == Player::Player_State::Step_Success) {
		return 1;
	}
	if (target_->getStep() == 2 && target_->getState() == Player::Player_State::Attack) {
		return 2;
	}
	if (target_->getStep() == 3 && target_->getState() == Player::Player_State::Step_Success) {
		return 3;
	}
	//ここが謎
	if (target_->getStep() == 4 && target_->getState() == Player::Player_State::Shoot) {
		return 4;
	}
	if (target_->getStep() == 0)return 0;
	
}

void SpecifiedStepManager::stepRecive()
{
	//if(reciveStep_ == 1) step
}

