#include "KeyCursor.h"
#include"../../../Graphic/Sprite.h"
#include"../../../Math/MathHelper.h"

#include<math.h>

static const float moveSpeed{ 10.f };//ÉJÅ[É\Éãà⁄ìÆéûä‘

KeyCursor::KeyCursor(const Vector2 & position):targetPosition_(position), basePosition_(position)
{
}

void KeyCursor::initialize(const Vector2 & position)
{
	targetPosition_ = position;
	basePosition_ = position;
	moveTime_ = 0.0f;
	animationTime_ = 0.0f;
}

void KeyCursor::update(float deltaTime)
{
	moveTime_ = min((moveTime_ + deltaTime*moveSpeed), 1.0f);
	animationTime_ = fmodf(animationTime_ + deltaTime, 1.0f);

}

void KeyCursor::draw(const Vector2& position) const
{
	
	float sinCount = MathHelper::Abs(MathHelper::Sin(animationTime_*360.0f));
	float addSize = 10.0f;//çLÇ™ÇÈîÕàÕ
	Vector2 addPos{ addSize*sinCount,addSize*sinCount };
	Vector2 drawPos = position + Vector2::Lerp(basePosition_,targetPosition_,moveTime_);
	Sprite::GetInstance().Draw(SPRITE_ID::NAME_CURSOL_L_SPRITE, drawPos + Vector2{ -5.0f, 5.0f }-addPos);
	Vector2 size = Sprite::GetInstance().GetSize(SPRITE_ID::NAME_CURSOL_L_SPRITE);
	size *= 0.5f;
	Sprite::GetInstance().Draw(SPRITE_ID::NAME_CURSOL_R_SPRITE, drawPos + size + Vector2{ 15.0f , 0.0f }+addPos);

	
}

void KeyCursor::drawWide(const Vector2 & position) const
{
	float sinCount = MathHelper::Abs(MathHelper::Sin(animationTime_*360.0f));
	float addSize = 10.0f;//çLÇ™ÇÈîÕàÕ
	Vector2 addPos{ addSize*sinCount,addSize*sinCount };
	Vector2 drawPos = position + Vector2::Lerp(basePosition_, targetPosition_, moveTime_);
	Sprite::GetInstance().Draw(SPRITE_ID::NAME_CURSOL_L_SPRITE, drawPos + Vector2{ -5.0f, 5.0f }-addPos);
	Vector2 size = Sprite::GetInstance().GetSize(SPRITE_ID::NAME_CURSOL_L_SPRITE);
	size *= 0.5f;
	Sprite::GetInstance().Draw(SPRITE_ID::NAME_CURSOL_R_SPRITE, drawPos + size + Vector2{ 50.0f , 0.0f }+addPos);
}

void KeyCursor::setPosition(const Vector2 & position)
{
	basePosition_ = Vector2::Lerp(basePosition_, targetPosition_, moveTime_);
	targetPosition_ = position;
	moveTime_ = 0.0f;
}

float KeyCursor::getPosition()
{
	return 0.0f;
}
