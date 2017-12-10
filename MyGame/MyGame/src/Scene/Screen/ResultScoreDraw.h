#pragma once
#include<list>
#include"../../ScoreManager/ScoreData.h"

class ResultScoreDraw {
public:
	ResultScoreDraw();
	~ResultScoreDraw();

	void init();
	void update(float deltaTime);
	void draw()const;

private:
	std::vector<ScoreData> dataList_;
	int drawCount_;
	float lerpTimer_;
};