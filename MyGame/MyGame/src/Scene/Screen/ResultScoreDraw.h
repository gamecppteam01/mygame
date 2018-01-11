#pragma once
#include<list>
#include"../../ScoreManager/ScoreData.h"
#include"ResultAnimation.h"

class ResultScoreDraw {
enum State {
	Start,
	Move1,
	Animation,
	Move2,
	End,
};
public:
	ResultScoreDraw();
	~ResultScoreDraw();

	void init();
	void update(float deltaTime);
	void draw()const;
	bool end()const;
private:
	std::vector<ScoreData> dataList_;
	State state_;
	int drawCount_;
	float lerpTimer_;

	Vector2 another_position_;

	float count;

	float x;
	float y;

	std::vector<std::pair<ScoreData,Vector2>> PlayerList;

	int curent_key;

	ResultAnimation animation_;
};