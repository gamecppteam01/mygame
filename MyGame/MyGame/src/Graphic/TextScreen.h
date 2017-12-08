#pragma once
#include <vector>
#include"../Scene/Scene.h"
#include"../Math/Vector2.h"
#include <iostream>
#include<fstream>
#include<array>

class World;
class TextScreen
{
public:
	// コンストラクタ
	TextScreen();

	void Init(const std::string& filename,int windowTextSize);

	void Update();


	void Check();

	// 描画
	void Draw() const;
	void End();

private:
	int CheckInsertPoinst(const std::string& checkText,int& point1, int& point2,int& point3);

	int currentText()const;

private:
	const int textLine{ 3 };//行数
	int timeCount_;
	std::vector<std::string> textList_;

	int textCount_{ 0 };
	int textSize_;

	int targetText_;//表示画面数

	std::array<int,4> insertPoints_;//insertする数,地点1,地点2
};