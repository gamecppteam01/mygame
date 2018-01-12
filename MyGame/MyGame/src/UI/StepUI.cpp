#include "StepUI.h"
#include"../Math/Math.h"
#include"../Math/Easing.h"
#include"../Graphic/Sprite.h"

StepUI::StepUI(IWorld* world)
	:UI{ "StepUI",position_ }, world_(world){
}

void StepUI::initialize() {
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

	timer_ = 0.0f;

	state_ = UI_State::Initialize;
	state2_ = UI_State::Zero;
	ui_Play_ = false;

	pause_ = false;

	Step_Success = false;
	Step_Failed = false;

	Step = 0;
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
			if (Step_Success) {
				state_ = UI_State::Start;
			}
			else if (Step_Failed){
				state_ = UI_State::Miss_Start;
			}
			break;
		}
		case UI_State::Start: {
			ui_Play_ = true;

			alpha_ = MathHelper::Lerp(0.0f, 1.0f, count);
			position_ = Vector2::Lerp(Vector2(SCREEN_SIZE.x + 640, SCREEN_SIZE.y * 3 / 4), Vector2(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 3 / 4), count);
			another_position_ = Vector2::Lerp(Vector2(-640, SCREEN_SIZE.y * 3 / 4), Vector2(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 3 / 4), count);

			count = count + deltaTime * 3.0;
			count = min(count, 1.0);

			if (count >= 1.0f) {
				state2_ = UI_State::Before_End;
				state_ = UI_State::Zero;
			}
			break;
		}
		case UI_State::Staging: {
			if (another_count >= 1.0f) {
				state_ = UI_State::Before_End;
			}
		}
		case UI_State::Before_End: {
			alpha_ = MathHelper::Lerp(1.0f, 0.0f, count);
			position_ = Vector2::Lerp(Vector2(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 3 / 4), Vector2(-640, SCREEN_SIZE.y * 3 / 4), count);
			another_position_ = Vector2::Lerp(Vector2(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 3 / 4), Vector2(SCREEN_SIZE.x + 640, SCREEN_SIZE.y * 3 / 4), count);
			if (alpha_ <= 0.0f) {
				state2_ = UI_State::End;
				state_ = UI_State::Zero;
			}

			timer_ += deltaTime;
			if (timer_ >= 1.0f)count = count + deltaTime * 3.0;
			count = min(count, 1.0);
			break;
		}
		case UI_State::Miss_Start: {
			ui_Play_ = true;
			alpha_ = MathHelper::Lerp(0.0f, 1.0f, count);
			position_ = Vector2::Lerp(Vector2(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 1 / 4), Vector2(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2 - 75.0f), count);
			if (count >= 1.0f) {
				count = 0;
				state_ = UI_State::Miss_Staging;
			}
			count = count + 0.1;
			count = min(count, 1.0f);
			break;
		}
		case UI_State::Miss_Staging: {
			alpha_ = MathHelper::Lerp(1.0f, 0.0f, count);
			position_ = Vector2::Lerp(Vector2(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2 - 75.0f), Vector2(SCREEN_SIZE.x / 2, SCREEN_SIZE.y), count);
			if (count >= 1.0f) {
				count = 0;
				state_ = UI_State::End;
			}
			timer_ += deltaTime;
			if (timer_ >= 1.0f)count = count + 0.1;
			count = min(count, 1.0f);
			break;
		}
		case UI_State::End: {
			ui_Play_ = false;
			Step_Success = false;
			Step_Failed = false;
			state_ = UI_State::Initialize;
			break;
		}
		case UI_State::Zero:{
			count = 0;
			if (state2_ == UI_State::Before_End) {
				state_ = UI_State::Before_End;
			}
			if (state2_ == UI_State::End) {
				state_ = UI_State::End;
			}
			break;
		}
		}
	}
}

void StepUI::draw() const {
	if (ui_Play_) {
		switch (Step)
		{
		case 0:
			//É~ÉXÇÃîªíË
			Sprite::GetInstance().Draw(SPRITE_ID::STEP_MISS, position_, Sprite::GetInstance().GetSize(SPRITE_ID::STEP_MISS) / 2, alpha_, Vector2(0.5f,0.5f));
			break;
		case 1:
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

void StepUI::Notify(Notification type, void* param){
	switch (type)
	{
	case Notification::Call_StepSuccess: {
		//ê¨å˜éûèàóù
		Step = *(int*)param;
		Step_Success = true;
		break;
	}
	case Notification::Call_StepFailed: {
		//é∏îséûèàóù
		Step = 0;
		Step_Failed = true;
		break;
	}
	default:
		break;
	}
}
