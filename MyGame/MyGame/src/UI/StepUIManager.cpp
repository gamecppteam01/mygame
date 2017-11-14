#include "StepUIManager.h"

StepUIManager::StepUIManager(IWorld* world):UI{ "warningmanager" , position_ },world_(world){
}

void StepUIManager::initialize(){
	ActorPtr p = world_->findActor("Player");
	player_ = std::static_pointer_cast<Player>(p);
}

void StepUIManager::update(float deltaTime){
}

void StepUIManager::draw() const{

}

bool StepUIManager::is_StepSuccess(){
	if (player_.lock()->getState() == Player::Player_State::Step_Success) true;
	return true;
}

void StepUIManager::step_Decision(){
	if (player_.lock()->getStep() == 1) {
		FontManager::GetInstance().DrawTextApplyFont(100, 100, GetColor(255, 255, 255), FONT_ID::DEFAULT_FONT, "1");
	}
	else if (player_.lock()->getStep() == 2) {
		FontManager::GetInstance().DrawTextApplyFont(100, 100, GetColor(255, 255, 255), FONT_ID::DEFAULT_FONT, "2");
	}
	else if (player_.lock()->getStep() == 3) {
		FontManager::GetInstance().DrawTextApplyFont(100, 100, GetColor(255, 255, 255), FONT_ID::DEFAULT_FONT, "3");
	}
	else if (player_.lock()->getStep() == 4) {
		FontManager::GetInstance().DrawTextApplyFont(100, 100, GetColor(255, 255, 255), FONT_ID::DEFAULT_FONT, "4");
	}
}
