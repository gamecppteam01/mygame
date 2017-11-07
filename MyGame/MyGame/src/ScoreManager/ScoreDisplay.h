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
	//�X�R�A�\��(���W�A�ő包��)
	void Score(const Vector2& position,int digit) const;
	static void Score(const std::list<ScoreData>& score,const Vector2& position,int digit);
private:
	ScoreManager* scoreManager_;

};