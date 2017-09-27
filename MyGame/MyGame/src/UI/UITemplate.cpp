#include "UITemplate.h"
#include"../Graphic/Sprite.h"

UITemplate::UITemplate(const Vector2 & position):
	UI("UIName",position)//UIの名前はそれぞれのUI毎につける(複数生成する場合や、自身で名前を付けたい場合は引数でstringを受けとれば可能)
{
}

void UITemplate::initialize()
{
}

void UITemplate::update(float deltaTime)
{
}

void UITemplate::draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::START_SPRITE, position_);
}
