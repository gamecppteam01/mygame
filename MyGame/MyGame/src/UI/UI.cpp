#include "UI.h"

//コンストラクタ
UI::UI(const std::string & name, const Vector3 & position)
	: _name{ name }, _position{ position }
{
}

//初期化
void UI::onInitialize()
{
}

//更新
void UI::onUpdate(float deltaTime)
{
}

//描画
void UI::onDraw() const
{
}
