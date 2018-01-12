#include "TimeUI.h"
#include "../ScoreManager/NumberManager.h"
#include"../Graphic/Sprite.h"
#include"../Define.h"

TimeUI::TimeUI(IWorld * world, const Vector2& position) 
	: UI { "TimeUI", position },world_(world),position_(position){
}

void TimeUI::initialize(){
}

void TimeUI::update(float deltaTime){

}

void TimeUI::draw() const{
	const Vector2 position1{ position_.x + 64,position_.y + 64 };
	Sprite::GetInstance().Draw(SPRITE_ID::TIME_UI, position1,Sprite::GetInstance().GetSize(SPRITE_ID::TIME_UI),Vector2::One);

	if (world_->getTempoManager().getRemainTime() > 30) {
		NumberManager::GetInstance().DrawNumberTexture(SPRITE_ID::NUMBER ,position_, (int)world_->getTempoManager().getRemainTime(), Vector2(64, 64), Vector2(0.5f, 0.5f));
	}
	else {
		NumberManager::GetInstance().DrawNumberTexture2(SPRITE_ID::REDNUMBER, position_, (int)world_->getTempoManager().getRemainTime(), Vector2(64, 64), Vector2(0.5f, 0.5f));
	}
}
