#include "LightTimeDrawUI.h"
#include"../Graphic/Sprite.h"
#include"../Graphic/DxlibGraphic.h"
#include"../Math/Color.h"
#include<DxLib.h>

LightTimeDrawUI::LightTimeDrawUI():state_(State::None), alpha_(0.0f),rate_(0.0f), isIn_(false)
{
}

void LightTimeDrawUI::init()
{
	state_ = State::None;
	alpha_ = 0.0f;
	rate_ = 0.0f;
	isIn_ = false;
}

void LightTimeDrawUI::update(float deltaTime)
{
	switch (state_)
	{
	case LightTimeDrawUI::State::In:in(deltaTime); break;
	case LightTimeDrawUI::State::Keep:keep(deltaTime); break;
	case LightTimeDrawUI::State::Out:out(deltaTime); break;
	case LightTimeDrawUI::State::None:none(deltaTime); break;
	default:
		break;
	}
}

void LightTimeDrawUI::draw_enemy(const Vector2& position) const
{
	if (!isDraw())return;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_ * 255);
	DrawCircleGauge(position.x, position.y, rate_*100.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::JUST_GAUGE), 0.0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void LightTimeDrawUI::draw_player(const Vector3& position, const Vector3& upVector,float rate) const
{
	if (!isDraw())return;
	float size = 20.0f*2.0f;
	size *= rate;
	Color c{ 255,255,255,255 };//ƒQ[ƒWF

	DrawCircleGauge3D(position, upVector, c.r, c.g, c.b, c.a, size, 40.0f+rate_*42.5f, Sprite::GetInstance().GetHandle(SPRITE_ID::LIGHT_GAUGE_SPRITE),0.0f);//LIGHT_GAUGE_SPRITE
	
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_ * 255);
	//DrawCircleGauge(position.x, position.y, rate_*100.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::JUST_GAUGE), 0.0);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void LightTimeDrawUI::start()
{
	//alpha_ = 0.0f;

}

void LightTimeDrawUI::end()
{
	state_ = State::Out;
}

void LightTimeDrawUI::isIn(bool isIn)
{
	isIn_ = isIn;
	if (isIn_) {
		state_ = State::In;
	}
	else {
		state_ = State::Out;
	}
}

void LightTimeDrawUI::rate(float rate)
{
	rate_ = rate;
}

void LightTimeDrawUI::in(float deltaTime)
{
	alpha_ += deltaTime;

	if (alpha_ >= 1.0f) {
		alpha_ = 1.0f;
		state_ = State::Keep;
	}
}

void LightTimeDrawUI::keep(float deltaTime)
{
}

void LightTimeDrawUI::out(float deltaTime)
{
	alpha_ -= deltaTime;

	if (alpha_ <= 0.0f) {
		alpha_ = 0.0f;
		state_ = State::None;
	}

}

void LightTimeDrawUI::none(float deltaTime)
{
}

bool LightTimeDrawUI::isDraw() const
{
	return state_ != State::None;
}
