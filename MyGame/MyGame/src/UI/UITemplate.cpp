#include "UITemplate.h"
#include"../Graphic/Sprite.h"

UITemplate::UITemplate(const Vector2 & position):
	UI("UIName",position)//UI�̖��O�͂��ꂼ���UI���ɂ���(������������ꍇ��A���g�Ŗ��O��t�������ꍇ�͈�����string���󂯂Ƃ�Ή\)
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
