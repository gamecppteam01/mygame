#pragma once
#include <DxLib.h>
#include "../Math/Math.h"
#include<list>

class ScoreManager {
public:
	//コンストラクタ
	ScoreManager();
	//初期化
	void initialize();
	//更新
	void update(float deltaTime);

};
