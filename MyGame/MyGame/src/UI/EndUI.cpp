#include "EndUI.h"

EndUI::EndUI(TempoManager* tempoManager,const Vector2 & position)
	:UI{ "EndUI",position },tempoManager_(tempoManager),position_(position){
}

void EndUI::initialize()
{
	time_ = 0;
}

void EndUI::update(float deltaTime)
{
	if (tempoManager_->isEnd()) {
		position_.x += 2;
		time_ += deltaTime;
	}
}

void EndUI::draw() const
{
	if (tempoManager_->isEnd()) {
		DrawFormatString(position_.x, position_.y, (255, 255, 255), "I—¹");
	}
}

bool EndUI::end() const
{
	if (time_ >= 5) return true;

	return false;
}
