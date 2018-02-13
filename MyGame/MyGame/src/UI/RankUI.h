#pragma once
#include"../ScoreManager/ScoreManager.h"
#include"../ScoreManager/NumberManager.h"
#include"../Math/Math.h"
#include "../UI/UI.h"
#include "../Camera/RoundCamera.h"
#include<list>
class RankUI : public UI{
public:
	//コンストラクタ
	RankUI(ScoreManager* score,RoundCamera* roundCamera ,const Vector2& position);
	void initialize() override;
	void update(float delta_time) override;
	void draw() const override;
	void Score(const Vector2& position) const;
	void Rank_SpriteID(const int num, const Vector2& position, const float size)const;
	bool IsStart()const;
private:
	int stage_{ 1 };
	ScoreManager* score_;
	RoundCamera* roundCamera_;
	float alpha_;
	bool start_;
};