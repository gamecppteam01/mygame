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
	// �R���X�g���N�^
	TextScreen();

	void Init(const std::string& filename,int windowTextSize);

	void Update();


	void Check();

	// �`��
	void Draw() const;
	void End();

private:
	int CheckInsertPoinst(const std::string& checkText,int& point1, int& point2,int& point3);

	int currentText()const;

private:
	const int textLine{ 3 };//�s��
	int timeCount_;
	std::vector<std::string> textList_;

	int textCount_{ 0 };
	int textSize_;

	int targetText_;//�\����ʐ�

	std::array<int,4> insertPoints_;//insert���鐔,�n�_1,�n�_2
};