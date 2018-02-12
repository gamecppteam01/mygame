#pragma once
#include"../Math/Vector2.h"
#include"../Graphic/Sprite.h"
#include"../Graphic/FontManager.h"

class CutInText {
public:


	static void Draw(const Vector2& position, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One);
	static void DrawMin(const Vector2& position);


private:
	static const std::vector<FONT_ID> fontIDs;

	static const int maxNameSize{ 10 };
};