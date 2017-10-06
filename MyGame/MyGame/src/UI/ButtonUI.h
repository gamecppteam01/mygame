#pragma once
#include "../Math/Math.h"
#include "../Graphic/Sprite.h"
#include "../UI/UI.h"

class ButtonUI : public UI {
public:
	//コンストラクタ
	ButtonUI( const SPRITE_ID& id, const Vector2& position);
	//開始
	void start();
	//描画
	void draw() const;

private:
	//ボタンの座標
	Vector2 m_Position;
	//ボタンのID
	SPRITE_ID m_ID;
};