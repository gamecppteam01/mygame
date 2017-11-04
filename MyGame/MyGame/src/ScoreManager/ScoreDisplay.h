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
	//�i�I��ԍ��A�X�R�A�j�\��
	void Score() const;
private:
	ScoreManager* scoreManager_;

};