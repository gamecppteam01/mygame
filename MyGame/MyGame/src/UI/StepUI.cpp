#include "StepUI.h"
#include"../Math/Math.h"
#include"../Math/Easing.h"
#include"../Graphic/Sprite.h"

StepUI::StepUI(IWorld* world)
	:UI{ "StepUI",position_ },world_(world){
}

void StepUI::initialize(){
	auto p = world_->findActor("Player");
	player_ = std::static_pointer_cast<Player>(p);
	position_ = Vector2::Zero;
	alpha_ = 1.0f;
	scale_ = Vector2::One;

	time_ = 0.0f;

	start_position_ = Vector2::Zero;
	end_position_ = Vector2::Zero;

	count = 0.0f;
	another_count = 0.0f;

	ui_State_ = 0;
	ui_Play_ = false;
}

void StepUI::update(float deltaTime){
	switch (ui_State_){
		case 0: {
			//position_ = Vector2(SCREEN_SIZE.x, SCREEN_SIZE.y / 2) + Vector2(256, 128);
			position_ = Vector2(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2);
			scale_ = Vector2::One;
			alpha_ = 1.0f;
			time_ = 0.0f;
			count = 0.0f;
			another_count = 0.0f;
			ui_Play_ = false;
			if (is_StepSuccess()) {
				ui_State_++;
			}
			break;
		}
		case 1: {
			ui_Play_ = true;
			count += 1.0f * deltaTime;
			start_position_ = Vector2(SCREEN_SIZE.x, SCREEN_SIZE.y / 2) + Vector2(256, 0);
			end_position_ = Vector2(SCREEN_SIZE.x / 2 , SCREEN_SIZE.y / 2);
			position_ = Vector2::Lerp(start_position_, end_position_,count);
			if (position_.x <= end_position_.x) {
				ui_State_++;
				count = 0;
			}
			break;
		}
		case 2: {
			another_count += deltaTime;
			if (another_count >= 1.0f) count += 1.0f * deltaTime;
			start_position_ = Vector2(SCREEN_SIZE.x / 2 , SCREEN_SIZE.y / 2);
			end_position_ = Vector2( -128 , SCREEN_SIZE.y / 2);
			position_ = Vector2::Lerp(start_position_, end_position_, count);
			if (position_.x <= end_position_.x) {
				ui_State_++; 
			}
			break;
		}
		case 3: {
				ui_State_ = 0;
				ui_Play_ = false; 
			break;
		}
	}
}

void StepUI::draw() const{
	if (ui_Play_) {
		switch (player_.lock()->getStep())
		{
		case 1:
			Sprite::GetInstance().Draw(SPRITE_ID::STEP_QUARTER, position_, Sprite::GetInstance().GetSize(SPRITE_ID::STEP_QUARTER) / 2, alpha_, scale_); break;
		case 2:
			Sprite::GetInstance().Draw(SPRITE_ID::STEP_HALF, position_, Sprite::GetInstance().GetSize(SPRITE_ID::STEP_HALF) / 2, alpha_, scale_); break;
		case 3:
			Sprite::GetInstance().Draw(SPRITE_ID::STEP_TURN, position_, Sprite::GetInstance().GetSize(SPRITE_ID::STEP_TURN) / 2, alpha_, scale_); break;
		case 4:
			Sprite::GetInstance().Draw(SPRITE_ID::STEP_SPIN, position_, Sprite::GetInstance().GetSize(SPRITE_ID::STEP_SPIN) / 2, alpha_, scale_); break;
		}
	}
}

bool StepUI::End_time(float deltaTime){
	time_ += deltaTime;
	if (time_ > 3) {
		return true;
	}
	return false;
}

bool StepUI::is_StepSuccess() const{
	if (player_.lock()->getState() == Player::Player_State::Step_Success ||
		player_.lock()->getState() == Player::Player_State::Attack ||
		player_.lock()->getState() == Player::Player_State::Shoot) return true;
	return false;
}
