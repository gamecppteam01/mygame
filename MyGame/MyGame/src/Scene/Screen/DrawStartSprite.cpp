#include "DrawStartSprite.h"
#include"../../Math/Easing.h"
#include"../../Math/Vector2.h"
#include"../../Graphic/Sprite.h"

static const float easeTime = 0.5f;
static const float easeTime_fall = 0.2f;
DrawStartSprite::DrawStartSprite(SPRITE_ID id, DrawStartSprite_FadeType type):
	id_{ id }, type_{ type }, easeTimer_{ 0.0f }{
	switch (type)
	{
	case DrawStartSprite_FadeType::Fade_Scale:
		scale_ = 0.5f;
		alpha_ = 0.0f;
		break;
	case DrawStartSprite_FadeType::Fade_Fall:
		scale_ = 20.0f;
		alpha_ = 1.0f;
		state_ = State::In;
		break;
	default:
		break;
	}
}

void DrawStartSprite::update(float deltaTime)
{
	if (type_ == DrawStartSprite_FadeType::Fade_None)return;

	easeTimer_ += deltaTime;
	switch (type_)
	{
	case DrawStartSprite_FadeType::Fade_Scale: {
		scale_ = Easing::EaseOutCirc(easeTimer_, 0.5f, 0.5f, easeTime);//0.5fからスタートで0.5f追加
		alpha_ = Easing::EaseOutCirc(easeTimer_, 0.0f, 1.0f, easeTime);
		break;
	}
	case DrawStartSprite_FadeType::Fade_Fall:{
		switch (state_)
		{
		case DrawStartSprite::In:in();
			break;
		case DrawStartSprite::Stay:stay();
			break;
		case DrawStartSprite::Out:out();
			break;
		default:
			break;
		}

		break;
	}
	default:
		break;
	}
}

void DrawStartSprite::draw(const Vector2& position) const
{
	if (type_ == DrawStartSprite_FadeType::Fade_None)return;

	Vector2 origin = Sprite::GetInstance().GetSize(id_) / 2;
	Sprite::GetInstance().Draw(id_, position, origin, alpha_, Vector2{ scale_,scale_ });
}

bool DrawStartSprite::isDead() const
{
	return isDead_;
}

void DrawStartSprite::in()
{
	easeTimer_ = min(easeTimer_, easeTime_fall);
	scale_ = Easing::EaseOutCirc(easeTimer_, 20.0f, -19.0f, easeTime_fall);
	if (easeTimer_ >= easeTime_fall) {
		easeTimer_ = 0.0f;
		state_ = State::Stay;
	}
	//alpha_ = Easing::EaseOutCirc(easeTimer_, 0.0f, 1.0f, easeTime_fall);

}

void DrawStartSprite::stay()
{
	if (easeTimer_ >= easeTime_fall) {
		easeTimer_ = 0.0f;
		state_ = State::Out;
	}

}

void DrawStartSprite::out()
{
	scale_ = Easing::EaseInCirc(easeTimer_, 1.0f, -0.5f, 0.2f);
	alpha_ = Easing::EaseInCirc(easeTimer_, 1.0f, -1.0f, 0.2f);


	//全時間が終わったら死ぬ
	if (easeTimer_ >= 0.2f) {
		isDead_ = true;
	}
	return;

}
