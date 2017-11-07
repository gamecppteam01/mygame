#include "NumberManager.h"
#include"../Math/MyFuncionList.h"
#include"../Math/MathHelper.h"
#include <sstream>
#include <iomanip>

void NumberManager::DrawNumber(Vector2 & position, int score, int digit, int space){
	int maxscore = MathHelper::Pow(10, digit) - 1;
	score = min(score, maxscore);
	draw(position, score, space, digit);
}

void NumberManager::DrawNumber(Vector2 & position, int score){
	draw(position, score);
}

void NumberManager::draw(Vector2 & position, int score, int digit, char fill)
{
	std::stringstream ss;
	ss << std::setw(digit) << std::setfill(fill) << score;
	draw(position, ss.str());
}

void NumberManager::draw(Vector2 & position, int score,char fill){
	std::stringstream ss;
	ss << std::setw(std::to_string(score).size()) << std::setfill(fill) << score;
	draw(position, ss.str());
}

void NumberManager::draw(const Vector2 & position, int score){
	draw(position, std::to_string(score));
}

void NumberManager::draw(const Vector2 & position, const std::string & score){
	for (int i = 0; i < (int)score.size(); ++i) {
		if (score[i] == ' ')continue;
		const int n = score[i] - '0';
		unsigned int C = GetColor(255, 255, 255);
		FontManager::GetInstance().DrawTextApplyFont(position.x + i * 25, position.y, C, FONT_ID::DEFAULT_FONT, "%d", n);
	}
}

void NumberManager::drawT(const Vector2 & position, int score, int digit){
	int maxscore = MathHelper::Pow(10, digit) - 1;
	score = min(score, maxscore);
	std::vector<int> drawscore = SligeDigit(score);
	auto position_ = position;
	position_.x = position.x + 30 * digit;
	for (int i = 0; i < (int)drawscore.size(); i++) {
		FontManager::GetInstance().DrawTextApplyFont(position_.x - 22.5 * i, position_.y, GetColor(255, 255, 255), FONT_ID::DEFAULT_FONT, "%d", drawscore.at(i));
	}
}