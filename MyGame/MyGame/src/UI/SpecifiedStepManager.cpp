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
	cursorPos_ = Vector2(100.0f, 650.0f);
	target_ = std::static_pointer_cast<Player>(world_->findActor("Player"));
	position_ = Vector2(120.0f, 650.0f);
		
	
}

void SpecifiedStepManager::update(float deltaTime)
{
	if (stepdraw_.empty()) return;
	//stepMathingと一致したら消す
	stepMatching();
	for (auto &a : stepdraw_) {
		a->update(deltaTime);
	}
	if (stepdraw_.front()->getIsDead() == true) {
		auto itr = std::remove_if(stepdraw_.begin(), stepdraw_.end(), [](auto &a) {return a->getIsDead(); });
		stepdraw_.erase(itr, stepdraw_.end());
		for (auto &a : stepdraw_) {
			a->addPosition(Vector2(-120.0f, 0.0f));
		}
	}
}

void SpecifiedStepManager::draw() const
{
	for (auto a : stepdraw_) {
		a->draw();
	}
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_CURSOR, cursorPos_);
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
		position_ += Vector2(120.0f, 0.0f);
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
	if (stepdraw_.empty())return 0;
	if (stepdraw_.front()->getIsStart()) return 0;
	//ステップ １クオーター、２ハーフ、３ターン、４スピン
	if (target_->getStep() == 1 && target_->getState() == Player::Player_State::Step_Success) {
		if (stepdraw_.front()->getid() == SPRITE_ID::QUATER_SPRITE) stepdraw_.front()->IsStart();
		
	}
	if (target_->getStep() == 2 && target_->getState() == Player::Player_State::Attack) {
		if (stepdraw_.front()->getid() == SPRITE_ID::HALF_SPRITE) stepdraw_.front()->IsStart();
	}
	if (target_->getStep() == 3 && target_->getState() == Player::Player_State::Step_Success) {
		if (stepdraw_.front()->getid() == SPRITE_ID::TURN_SPRITE) stepdraw_.front()->IsStart();
	}
	if (target_->getStep() == 4 && target_->getState() == Player::Player_State::Shoot) {
		if (stepdraw_.front()->getid() == SPRITE_ID::SPIN_SPRITE) stepdraw_.front()->IsStart();
	}
	if (target_->getStep() == 0)return 0;
	
}

