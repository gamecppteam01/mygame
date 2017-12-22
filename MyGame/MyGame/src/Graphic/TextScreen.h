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

	void Init(const std::string& filename,int lineTextSize);
	void Reset();
	void Update();


	void Check();

	// 描画
	void Draw(const Vector2& position) const;
	void End();

	bool isEnd()const;
private:

	//int currentText()const;

private:
	const int textLine{ 3 };//行数
	int timeCount_;
	std::vector<std::string> textList_;

	int textCount_{ 0 };
	int textSize_;

	int targetText_;//表示画面数

	bool isEnd_;
};