#include "TimeUI.h"
#include "../ScoreManager/NumberManager.h"
#include"../Define.h"

TimeUI::TimeUI(IWorld * world, const Vector2& position) 
	: UI { "TimeUI", position },world_(world),position_(position){
}

void TimeUI::initialize(){
	sincount = 0.0f;
	scale_ = Vector2(0.0f,0.0f);
	move_ = Vector2(0.0f, 0.0f);
}

void TimeUI::update(float deltaTime){
	if (world_->getTempoManager().getRemainTime() <= 30) {
		sincount += 4;
		sincount = std::fmodf(sincount, 360);
		scale_ = Vector2::Lerp(Vector2(0.5, 0.5), Vector2(0.7, 0.7), std::abs(MathHelper::Sin(sincount)));
		move_ = Vector2::Lerp(Vector2(0, 0), Vector2(-5, -5), std::abs(MathHelper::Sin(sincount)));
	}
}

void TimeUI::draw() const{
	if (world_->getTempoManager().getRemainTime() > 30) {
		NumberManager::GetInstance().DrawNumberTexture(SPRITE_ID::NUMBER ,position_, (int)world_->getTempoManager().getRemainTime(), Vector2(128, 128), Vector2(0.5f, 0.5f));
	}
	else {
		if (world_->getTempoManager().getRemainTime() > 9) {
			NumberManager::GetInstance().DrawNumberTexture2(SPRITE_ID::REDNUMBER, position_ + move_, (int)world_->getTempoManager().getRemainTime(), Vector2(128, 128), scale_);
		}
		else {
			NumberManager::GetInstance().DrawNumberTexture2(SPRITE_ID::REDNUMBER, position_, (int)world_->getTempoManager().getRemainTime(), Vector2(128, 128), scale_);
		}
	}
}
