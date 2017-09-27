#pragma once
#include"UI.h"

class UITemplate:public UI {
public:
	//コンストラクタ
	UITemplate(const Vector2& position);

	//初期化
	virtual void initialize()override;
	//更新
	virtual void update(float deltaTime)override;
	//描画
	virtual void draw() const override;

};