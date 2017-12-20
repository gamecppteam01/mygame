#include "ResultScoreDraw.h"
#include"../../DataManager/DataManager.h"
#include"../../Define.h"
#include"../../Graphic/FontManager.h"

static const Vector2 basePos{ WINDOW_WIDTH*0.4f,50.0f };
ResultScoreDraw::ResultScoreDraw()
{
}

ResultScoreDraw::~ResultScoreDraw()
{
}

void ResultScoreDraw::init()
{
	dataList_.clear();
	auto dt = DataManager::GetInstance().getData();
	dt.sort([](ScoreData& s1, ScoreData& s2) {return s1.score_ < s2.score_; });
	dataList_.assign(dt.begin(), dt.end());

	drawCount_ = 0;
	lerpTimer_ = 0.0f;

}

void ResultScoreDraw::update(float deltaTime)
{
	if (drawCount_ >= dataList_.size())return;
	lerpTimer_ += deltaTime;
	if (lerpTimer_ > 1.0f) {
		drawCount_++;
		lerpTimer_ = 0.0f;
	}
}

void ResultScoreDraw::draw() const
{

	for (int i = 0; i < drawCount_; i++) {
		Vector2 Position = basePos + Vector2{ 0.0f,80.0f * (dataList_.size()-1-i) };
		
		std::string space;
		int score = dataList_.at(i).score_;
		if (score >= 100000)score=99999;
		else if (score >= 10000)space = "";
		else if (score >= 1000)space = " ";
		else if (score >= 100)space = "  ";
		else if (score >= 10)space = "   ";
		else space = "    ";
		if (dataList_.at(i).playerNumber_ == 1)SetDrawBright(255, 255, 0);
		FontManager::GetInstance().DrawTextApplyFont(Position.x, Position.y, GetColor(255, 255, 255), FONT_ID::JAPANESE_FONT,
			"No" + std::to_string(dataList_.size() - i) + "    " + std::to_string(dataList_.at(i).playerNumber_) + "”Ô" + "           " + space + std::to_string(score));
		if (dataList_.at(i).playerNumber_ == 1)SetDrawBright(255, 255, 255);
	}
	if (drawCount_ >= dataList_.size())return;
	int pos = drawCount_;

	float x = MathHelper::Lerp(WINDOW_WIDTH, 0.0f, lerpTimer_);
	Vector2 Position = basePos + Vector2{ x,80.0f * (dataList_.size()-1-pos) };
	std::string space;
	
	int score = dataList_.at(pos).score_;
	if (score >= 100000)score = 99999;
	else if (score >= 10000)space = "";
	if (score >= 1000)space = " ";
	else if (score >= 100)space = "  ";
	else if (score >= 10)space = "   ";
	else space = "    ";
	if (dataList_.at(pos).playerNumber_ == 1)SetDrawBright(255, 255, 0);
	FontManager::GetInstance().DrawTextApplyFont(Position.x, Position.y, GetColor(255, 255, 255), FONT_ID::JAPANESE_FONT,
		"No" + std::to_string(dataList_.size() - pos) + "    " + std::to_string(dataList_.at(pos).playerNumber_) + "”Ô" + "           " + space + std::to_string(score));
	if (dataList_.at(pos).playerNumber_ == 1)SetDrawBright(255, 255, 255);

}
