#include "ComboGaugeUI.h"
#include "../Graphic/Sprite.h"
#include "../Input/GamePad.h"
#include "ButtonUI.h"

ComboGaugeUI::ComboGaugeUI(const Vector2& gaugePos)
	:gaugePos_{ gaugePos }
{
}

void ComboGaugeUI::start()
{
	buttonList_.clear();
	//初期化
	gaugeRect_.top = 0.0f;
	gaugeRect_.right = 0.0f;
	gaugeRect_.left = 0.0f;
	gaugeRect_.bottom = 50.0f;
	//時間指定
	nowTime_ = 0.0f;
	maxTime_ = 600.0f;
	//画像のサイズに合わせる
	gaugeWidth_ = 200.0f;
	ButtonCount_ = 0;
	t = 0;
	state_ = State::input;
}

void ComboGaugeUI::update(float deltaTime)
{
	stateUpdete(deltaTime);
}

void ComboGaugeUI::draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::GAUGE_UI,
		gaugePos_,
		gaugeRect_,
		Vector2::Zero, 1.0f,
		Vector2(1.0f, 1.0f),
		0.0f,
		true,
		false);
	for (auto b : buttonList_) {
		b->draw();
	}
}

void ComboGaugeUI::createButton(const Step_Type& type)
{
	switch (type)
	{
	case Step_Type::Chasse:
		buttonList_.push_back(std::make_shared<ButtonUI>(SPRITE_ID::BUTTON_A, Vector2(100.0f, 100.0f) + Vector2(50.0f, 0.0f) * buttonList_.size()));
		break;
	case Step_Type::Turn:
		buttonList_.push_back(std::make_shared<ButtonUI>(SPRITE_ID::BUTTON_B, Vector2(100.0f, 100.0f) + Vector2(50.0f, 0.0f) * buttonList_.size()));
		break;
	case Step_Type::Whisk:
		buttonList_.push_back(std::make_shared<ButtonUI>(SPRITE_ID::BUTTON_C, Vector2(100.0f, 100.0f) + Vector2(50.0f, 0.0f) * buttonList_.size()));
		break;
	case Step_Type::SplitCubanBreak:
		buttonList_.push_back(std::make_shared<ButtonUI>(SPRITE_ID::BUTTON_D, Vector2(100.0f, 100.0f) + Vector2(50.0f, 0.0f) * buttonList_.size()));
		break;
	}
}

void ComboGaugeUI::stateUpdete(float deltaTime)
{
	switch (state_)
	{
	case State::input:
		inputUpdate(deltaTime);
		break;
	case State::output:
		outputUpdate(deltaTime);
		break;
	}
}

void ComboGaugeUI::inputUpdate(float deltaTime)
{
	if (buttonList_.size() >= 3 && nowTime_ <= 0.0f) {
		nowTime_ = 600.0f;
		t = 1;
		state_ = State::output;
	}
	
}

void ComboGaugeUI::outputUpdate(float deltaTime)
{
	float result = 0.0f;

	result = nowTime_ / maxTime_ * gaugeWidth_;
	gaugeRect_.right = result;

	if (nowTime_ <= 0.0f)
	{
		nowTime_ = 0.0f;
		t = 0;
		buttonList_.clear();
		state_ = State::input;
	}

	//減少する
	nowTime_ -= 1.0f * t;
}
