#include "UI.h"

//コンストラクタ
UI::UI(const std::string & name, const Vector2 & position)
	: name_{ name }, position_{ position }
{
}

std::string UI::getName() const
{
	return name_;
}

