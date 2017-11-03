#pragma once
#include"ScoreManager.h"
#include"NumberManager.h"
#include"../Graphic/FontManager.h"
#include"../Math/Math.h"
#include"../Graphic/TextDraw.h"
#include<list>

class ScoreDisplay {
public:
	ScoreDisplay(std::list<ScoreData>& list);
	~ScoreDisplay();
	void initialize();
	//（選手番号、スコア）表示
	void Score();
private:
	ScoreManager* scoreManager_;
	std::list<ScoreData> ScoreData_;
};