#pragma once
#include "../Math/Vector2.h"
#include <list>
#include "ButtonUIPtr.h"
#include "../Actor/Player/Step_Type.h"
#include "UI.h"

enum class State {
	input,
	output,
};

class ComboGaugeUI : public UI{
public:
	//コンストラクタ
	explicit ComboGaugeUI(const Vector2& gaugePos);
	//初期化
	virtual void initialize() override;
	//更新
	virtual void update(float deltaTime) override;
	//描画
	virtual void draw() const override;

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