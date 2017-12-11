#include "StepUI.h"
#include"../Math/Math.h"
#include"../Math/Easing.h"
#include"../Graphic/Sprite.h"

StepUI::StepUI(IWorld* world)
	:UI{ "StepUI",position_ }, world_(world){
}

void StepUI::initialize() {
	auto p = world_->findActor("Player");
	player_ = std::static_pointer_cast<Player>(p);

	position_ = Vector2::Zero;
	scale_ = Vector2::One;
	alpha_ = 1.0f;

	another_position_ = Vector2::Zero;
	another_scale_ = Vector2::One;
	another_alpha_ = 1.0f;

	start_position_ = Vector2::Zero;
	end_position_ = Vector2::Zero;

	count = 0.0f;
	another_count = 0.0f;
	max_count = 1.0f;

	timer_ = 0.0f;

	state_ = UI_State::Initialize;
	ui_Play_ = false;

	pause_ = false;
}

void StepUI::pause(){
	pause_ = true;
}

void StepUI::restart(){
	pause_ = false;
}

void StepUI::update(float deltaTime) {
	if (!pause_) {
		switch (state_) {
		case UI_State::Initialize: {
			position_ = Vector2::Zero;
			scale_ = Vector2::One;
			alpha_ = 0.0f;

			another_position_ = Vector2::Zero;
			another_scale_ = Vector2::One;
			another_alpha_ = 0.0f;

			timer_ = 0.0f;

			count = 0.0f;
			another_count = 0.0f;

			ui_Play_ = false;
			if (is_StepSuccess()) {
				state_ = UI_State::Start;
			}
			break;
		}
		case UI_State::Start: {
			ui_Play_ = true;

			//
			alpha_ = MathHelper::Lerp(0.0f, 1.0f, count);

			position_ = Vector2::Lerp(Vector2(SCREEN_SIZE.x + 640, SCREEN_SIZE.y * 3 / 4), Vector2(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 3 / 4), count);
			another_position_ = Vector2::Lerp(Vector2(-640, SCREEN_SIZE.y * 3 / 4), Vector2(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 3 / 4), count);
			//

			//
					//another_scale_ = Vector2::Lerp(Vector2(1.0f, 0.0f), Vector2(1.0f, 1.0f), count);

					//if (count >= 1.0f) {
					//	position_ = Vector2::Lerp(Vector2(-640, SCREEN_SIZE.y * 3 / 4), Vector2(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 3 / 4), count);
					//}
			//

			if (alpha_ >= 1.0f) {
				count = 0;
				state_ = UI_State::Before_End;
			}

			count = count + deltaTime * 3.0;
			count = min(count, 1);
			//if (count >= 1.0f) {
			//	another_count = another_count + deltaTime * 1.0;
			//	another_count = min(another_count, 1.0f);
			//}
			break;
		}
		case UI_State::Staging: {
			//
					//position_ = Vector2::Lerp(Vector2(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 3 / 4), Vector2(SCREEN_SIZE.x * 3 / 4, SCREEN_SIZE.y * 3 / 4), count);
			if (another_count >= 10.0f) {
				state_ = UI_State::Before_End;
			}
			//

					//count = count + deltaTime * 1.0;
					//count = min(count, 1.0f);
		}
		case UI_State::Before_End: {
			//
			alpha_ = MathHelper::Lerp(1.0f, 0.0f, count);

			position_ = Vector2::Lerp(Vector2(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 3 / 4), Vector2(-640, SCREEN_SIZE.y * 3 / 4), count);
			another_position_ = Vector2::Lerp(Vector2(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 3 / 4), Vector2(SCREEN_SIZE.x + 640, SCREEN_SIZE.y * 3 / 4), count);
			//
					//position_ = Vector2::Lerp(Vector2(SCREEN_SIZE.x * 3 / 4, SCREEN_SIZE.y * 3 / 4), Vector2(SCREEN_SIZE.x + 640, SCREEN_SIZE.y * 3 / 4), count);
					//if (count >= 1.0f) {
					//	another_scale_ = Vector2::Lerp(Vector2(1.0f, 1.0f), Vector2(1.0f, 0.0f), count);
					//}
			//
			if (alpha_ <= 0.0f && !is_StepSuccess()) {
				state_ = UI_State::End;
			}

			timer_ += deltaTime;
			if (timer_ >= 1.0f)
				count = count + deltaTime * 3.0;
			if (count >= 1.0f) {
				count = 1.0f;
			}
			//if (count >= 1.0f) {
			//	another_count = another_count + deltaTime * 3.0;
			//	another_count = min(another_count, 1.0f);
			//}
			break;
		}
		case UI_State::End: {
			state_ = UI_State::Initialize;
			ui_Play_ = false;
			break;
		}
		}
	}
}

void StepUI::draw() const {
	if (ui_Play_) {
		switch (player_.lock()->getStep())
		{
		case 1:
			//Sprite::GetInstance().Draw(SPRITE_ID::BACK_UI, Vector2(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 3 / 4), Sprite::GetInstance().GetSize(SPRITE_ID::BACK_UI) / 2, alpha_, another_scale_);
			Sprite::GetInstance().Draw(SPRITE_ID::STEP_QUARTER, position_, Sprite::GetInstance().GetSize(SPRITE_ID::STEP_QUARTER) / 2, alpha_, scale_);
			Sprite::GetInstance().Draw(SPRITE_ID::STEP_QUARTER, another_position_, Sprite::GetInstance().GetSize(SPRITE_ID::STEP_QUARTER) / 2, alpha_, scale_);
			break;
		case 2:
			Sprite::GetInstance().Draw(SPRITE_ID::STEP_HALF, position_, Sprite::GetInstance().GetSize(SPRITE_ID::STEP_HALF) / 2, alpha_, scale_);
			Sprite::GetInstance().Draw(SPRITE_ID::STEP_HALF, another_position_, Sprite::GetInstance().GetSize(SPRITE_ID::STEP_HALF) / 2, alpha_, scale_);
			break;
		case 3:
			Sprite::GetInstance().Draw(SPRITE_ID::STEP_TURN, position_, Sprite::GetInstance().GetSize(SPRITE_ID::STEP_TURN) / 2, alpha_, scale_); 
			Sprite::GetInstance().Draw(SPRITE_ID::STEP_TURN, another_position_, Sprite::GetInstance().GetSize(SPRITE_ID::STEP_TURN) / 2, alpha_, scale_);
			break;
		case 4:
			Sprite::GetInstance().Draw(SPRITE_ID::STEP_SPIN, position_, Sprite::GetInstance().GetSize(SPRITE_ID::STEP_SPIN) / 2, alpha_, scale_); 
			Sprite::GetInstance().Draw(SPRITE_ID::STEP_SPIN, another_position_, Sprite::GetInstance().GetSize(SPRITE_ID::STEP_SPIN) / 2, alpha_, scale_);
			break;
		}
	}
}


bool StepUI::is_StepSuccess() const {
	if (player_.lock()->getState() == Player::Player_State::Step_Success ||
		player_.lock()->getState() == Player::Player_State::Attack ||
		player_.lock()->getState() == Player::Player_State::Shoot) return true;
	return false;
}
