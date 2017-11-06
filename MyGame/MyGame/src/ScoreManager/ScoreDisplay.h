#pragma once
#include"ScoreManager.h"
#include"NumberManager.h"
#include"../Graphic/FontManager.h"
#include"../Math/Math.h"
#include"../Graphic/TextDraw.h"
#include<list>

class ScoreDisplay {
public:
	ScoreDisplay(ScoreManager* score);
	~ScoreDisplay();
	void initialize();
	void setScoreManager(ScoreManager* score);
	void finalize();
	//（選手番号、スコア）表示
	void Score() const;
	static void Score(const std::list<ScoreData>& score,const Vector2& position);
private:
	ScoreManager* scoreManager_;

};