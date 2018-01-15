#include "SpecifiedStepManager.h"
#include "SpecifiedDraw.h"
#include "../Input/Keyboard.h"

static const std::map<int, SPRITE_ID> changeSprList{
	{ 1,SPRITE_ID::QUATER_SPRITE },
	{ 2,SPRITE_ID::HALF_SPRITE },
	{ 3,SPRITE_ID::TURN_SPRITE },
	{ 4,SPRITE_ID::SPIN_SPRITE }
};

SpecifiedStepManager::SpecifiedStepManager(IWorld * world)
	: UI{ "SpecifiedStepManager", position_ }, world_(world)
{
	initialize();
}

void SpecifiedStepManager::initialize()
{
	cursorPos_ = Vector2(50.0f, 600.0f);
	target_ = std::static_pointer_cast<Player>(world_->findActor("Player"));
	position_ = Vector2(100.0f, 620.0f);
	alpha_ = 1.0f;
	Xpos = 0.0f;
	timer_ = 0.0f;
}

void SpecifiedStepManager::update(float deltaTime)
{
	if (stepdraw_.empty()) return;
	for (auto &a : stepdraw_) {
		a->update(deltaTime);
		timer_++;
	}

	if (stepdraw_.front()->getPos() >= 100.0f) IsPad_ = true;

	if (stepdraw_.front()->getIsDead() == true) {
		auto itr = std::remove_if(stepdraw_.begin(), stepdraw_.end(), [](auto &a) {return a->getIsDead(); });
		stepdraw_.erase(itr, stepdraw_.end());
		if (IsPad_ = true) {
			for (auto &a : stepdraw_) {

				a->addPosition(Vector2(-200.0f, 0.0f));

			}
		}
		 
	}
	if (target_->getState() == Player::Player_State::Step_Success) {
		if (stepdraw_.front()->getIsDead() == true) { 
			alpha_ -= 0.1f;
		}
	} else { 
		alpha_ = 1.0f; 
	}
	
	
}

void SpecifiedStepManager::draw() const
{
	
	for (auto a : stepdraw_) {
		a->draw();
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	if (!stepdraw_.empty()) {
		if ((stepdraw_.front()->getid() == SPRITE_ID::QUATER_SPRITE && target_->getState() == Player::Player_State::Step_Success)) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			Sprite::GetInstance().Draw(SPRITE_ID::FLASH_SPRITE, stepdraw_.front()->getPosition());
		}
		if ((stepdraw_.front()->getid() == SPRITE_ID::TURN_SPRITE && target_->getState() == Player::Player_State::Step_Success)) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			Sprite::GetInstance().Draw(SPRITE_ID::FLASH_SPRITE, stepdraw_.front()->getPosition());
		}
		if ((stepdraw_.front()->getid() == SPRITE_ID::HALF_SPRITE && target_->getState() == Player::Player_State::Attack)) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			Sprite::GetInstance().Draw(SPRITE_ID::FLASH_SPRITE, stepdraw_.front()->getPosition());
		}
		if ((stepdraw_.front()->getid() == SPRITE_ID::SPIN_SPRITE && target_->getState() == Player::Player_State::Shoot)) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			Sprite::GetInstance().Draw(SPRITE_ID::FLASH_SPRITE, stepdraw_.front()->getPosition());
		}
		Sprite::GetInstance().Draw(SPRITE_ID::TITLE_CURSOR, cursorPos_);
	}
	if (!stepdraw_.empty() && stepdraw_.front()->getid() == SPRITE_ID::QUATER_SPRITE && target_->getState() == Player::Player_State::Step_Success) {
		Sprite::GetInstance().Draw(SPRITE_ID::NICE_SPRITE, cursorPos_ + Vector2(25.0f, -65.0f), alpha_);
	}
	if (!stepdraw_.empty() && stepdraw_.front()->getid() == SPRITE_ID::TURN_SPRITE && target_->getState() == Player::Player_State::Step_Success) {
		Sprite::GetInstance().Draw(SPRITE_ID::NICE_SPRITE, cursorPos_ + Vector2(25.0f, -65.0f), alpha_);
	}
	if (!stepdraw_.empty() && stepdraw_.front()->getid() == SPRITE_ID::HALF_SPRITE && target_->getState() == Player::Player_State::Attack) {
		Sprite::GetInstance().Draw(SPRITE_ID::NICE_SPRITE, cursorPos_ + Vector2(25.0f, -65.0f), alpha_);
	}
	if (!stepdraw_.empty() && stepdraw_.front()->getid() == SPRITE_ID::SPIN_SPRITE && target_->getState() == Player::Player_State::Shoot) {
		Sprite::GetInstance().Draw(SPRITE_ID::NICE_SPRITE, cursorPos_ + Vector2(25.0f, -65.0f), alpha_);
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
		position_ += Vector2(200.0f, 0.0f);
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

int SpecifiedStepManager::stepMatching(int stepType)
{
	if (stepdraw_.empty())return 0;
	if (stepdraw_.front()->getid() == changeSprList.at(stepType)) {
		stepdraw_.front()->IsStart();
	}

	return 1;


	//if (stepdraw_.front()->getIsStart()) return 0;
	////ステップ １クオーター、２ハーフ、３ターン、４スピン
	//if (target_->getStep() == 1 && target_->getState() == Player::Player_State::Step_Success) {
	//	if (stepdraw_.front()->getid() == SPRITE_ID::QUATER_SPRITE) stepdraw_.front()->IsStart();
	//	
	//}
	//if (target_->getStep() == 2 && target_->getState() == Player::Player_State::Attack) {
	//	if (stepdraw_.front()->getid() == SPRITE_ID::HALF_SPRITE) stepdraw_.front()->IsStart();
	//}
	//if (target_->getStep() == 3 && target_->getState() == Player::Player_State::Step_Success) {
	//	if (stepdraw_.front()->getid() == SPRITE_ID::TURN_SPRITE) stepdraw_.front()->IsStart();
	//}
	//if (target_->getStep() == 4 && target_->getState() == Player::Player_State::Shoot) {
	//	if (stepdraw_.front()->getid() == SPRITE_ID::SPIN_SPRITE) stepdraw_.front()->IsStart();
	//}
	//if (target_->getStep() == 0)return 0;
	
}

