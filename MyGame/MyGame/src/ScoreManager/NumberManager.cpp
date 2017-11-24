#include "NumberManager.h"
#include"../Math/MyFuncionList.h"
#include"../Math/MathHelper.h"
#include"../Graphic/FontManager.h"
#include"../Graphic/Sprite.h"
#include <sstream>
#include <iomanip>

void NumberManager::DrawNumber(const Vector2 & position,const int number){
	std::string string_numebr = std::to_string(number);
	for (int i = 0; i < (int)string_numebr.size(); ++i) {
		if (string_numebr[i] == ' ')continue;
		const int n = string_numebr[i] - '0';
		unsigned int C = GetColor(255, 255, 255);
		FontManager::GetInstance().DrawTextApplyFont(position.x + i * 25, position.y, C, FONT_ID::DEFAULT_FONT, "%d", n);
	}
}

void NumberManager::DrawNumber(const Vector2 & position, const int number, const int colornumebr){
	std::string string_numebr = std::to_string(number);
	switch (colornumebr) {
	case 1: C = GetColor(255, 255, 255); break;
	case 2: C = GetColor(255, 0, 0); break;
	case 3: C = GetColor(0, 255, 0); break;
	case 4: C = GetColor(0, 0, 255); break;
	}

	for (int i = 0; i < (int)string_numebr.size(); ++i) {
		if (string_numebr[i] == ' ')continue;
		const int n = string_numebr[i] - '0';
		FontManager::GetInstance().DrawTextApplyFont(position.x + i * 25, position.y, C, FONT_ID::DEFAULT_FONT, "%d", n);
	}
}

void NumberManager::DrawNumberTexture(const Vector2 & position, int number, const Vector2& size, const Vector2& scale){
	std::string string_numebr = std::to_string(number);
	for (int i = 0; i < (int)string_numebr.size(); ++i) {
		if (string_numebr[i] == ' ')continue;
		const int n = string_numebr[i] - '0';
		const RECT rect{ (float)n * size.x ,0.0f,(float)(n * size.x) + size.x,(float)size.y };
		const Vector2  pos{ position.x + i * size.x * scale.x,position.y };
		Sprite::GetInstance().Draw(SPRITE_ID::NUMBER, pos, rect, Vector2(0.0f, 0.0f), 1.0f, scale, 0.0f, true, false);
	}
}

void NumberManager::DrawNumberTexture2(const Vector2 & position, int number, const Vector2 & size, const Vector2 & scale){
	std::string string_numebr = std::to_string(number);
	for (int i = 0; i < (int)string_numebr.size(); ++i) {
		if (string_numebr[i] == ' ')continue;
		const int n = string_numebr[i] - '0';
		const RECT rect{ (float)n * size.x ,0.0f,(float)(n * size.x) + size.x,(float)size.y };
		const Vector2  pos{ position.x + i * size.x * scale.x ,position.y };
		Sprite::GetInstance().Draw(SPRITE_ID::REDNUMBER, pos, rect, Vector2(0.0f, 0.0f), 1.0f, scale, 0.0f, true, false);
	}
}

void NumberManager::drawT(const Vector2 & position, int number, int digit){
	int maxscore = MathHelper::Pow(10, digit) - 1;
	number = min(number, maxscore);
	std::vector<int> drawscore = SligeDigit(number);
	auto position_ = position;
	position_.x = position.x + 30 * digit;
	for (int i = 0; i < (int)drawscore.size(); i++) {
		FontManager::GetInstance().DrawTextApplyFont(position_.x - 22.5 * i, position_.y, GetColor(255, 255, 255), FONT_ID::DEFAULT_FONT, "%d", drawscore.at(i));
	}
}