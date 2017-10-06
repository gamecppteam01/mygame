#include "ButtonUI.h"

ButtonUI::ButtonUI(const SPRITE_ID& id, const Vector2& position)
	:UI{ "ButtonUI",position }, m_ID(id), m_Position(position) {
}

void ButtonUI::start()
{
}

void ButtonUI::draw() const
{
	Sprite::GetInstance().Draw(m_ID, m_Position);
}
