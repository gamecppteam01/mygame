#include "EndUI.h"

EndUI::EndUI(TempoManager* tempoManager,const Vector2 & position)
	:UI{ "EndUI",position },tempoManager_(tempoManager),position_(position){
}

void EndUI::initialize(){
	time_ = 0;
	scale_ = Vector2(20.0, 20.0);
}

void EndUI::update(float deltaTime){
	if (tempoManager_->isEnd()) {
		scale_.x -= 1.25;
		scale_.y -= 1.25;
		time_ += deltaTime;
		if (scale_.x < 1.0f || scale_.y < 1.0f) {
			scale_ = Vector2(1.0f, 1.0f);
		}
	}
}

void EndUI::draw() const{
	if (tempoManager_->isEnd()) {
		Sprite::GetInstance().Draw(SPRITE_ID::FINISH, Vector2(position_.x, position_.y), Sprite::GetInstance().GetSize(SPRITE_ID::FINISH) / 2 , scale_);
	}
}

bool EndUI::end() const{
	if (time_ >= 2)return true;
	return false;
}
