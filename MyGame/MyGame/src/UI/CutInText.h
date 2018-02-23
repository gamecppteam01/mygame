#pragma once
#include"../Math/Vector2.h"
#include"../Graphic/Sprite.h"
#include"../Graphic/FontManager.h"

class CutInText {
public:


	static void Draw(const Vector2& position, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One);
	static void DrawMin(const Vector2& position);

	static void DrawRank(const Vector2 & position);//ƒ‰ƒ“ƒN•\Ž¦—p

private:
	static const std::vector<FONT_ID> fontIDs;
	static const std::vector<FONT_ID> rankIDs;

	static const int maxNameSize{ 10 };
};