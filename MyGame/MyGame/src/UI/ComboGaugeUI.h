#pragma once
#include "../Math/Vector2.h"
#include <list>
#include "ButtonUIPtr.h"
#include "../Actor/Player/Step_Type.h"

enum class State {
	input,
	output,
};

class ComboGaugeUI {
public:
	//コンストラクタ
	ComboGaugeUI(const Vector2& gaugePos);
	//開始
	void start();
	//更新
	void update(float deltaTime);
	//描画
	void draw() const;

private:
	//ボタン生成
	void createButton(const Step_Type& type);
	//
	void stateUpdete(float deltaTime);
	//
	void inputUpdate(float deltaTime);
	//
	void outputUpdate(float deltaTime);

private:
	//ゲージ
	Vector2 gaugePos_;
	//ゲージの横幅
	RECT gaugeRect_;
	//ゲージの横幅
	float gaugeWidth_;
	//現在の時間
	float nowTime_;
	//最大時間
	float maxTime_;
	//ボタン入力
	int ButtonCount_;
	//
	int t;
	//
	State state_;
	//ボタンポインター
	std::list<ButtonUIPtr> buttonList_;
};