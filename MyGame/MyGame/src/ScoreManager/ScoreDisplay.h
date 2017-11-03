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
	//�i�I��ԍ��A�X�R�A�j�\��
	void Score();
private:
	ScoreManager* scoreManager_;
	std::list<ScoreData> ScoreData_;
};