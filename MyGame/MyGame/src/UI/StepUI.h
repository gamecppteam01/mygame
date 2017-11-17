#pragma once
#include "../Math/Math.h"
#include "../Graphic/Sprite.h"
#include "../UI/UI.h"

class StepUI : public UI {
public:
	StepUI(const SPRITE_ID& id,const Vector2& position);
	void initialize() override;
	void update(float deltaTime) override;
	void draw() const override;

private:
	//ステップUIの座標
	Vector2 position_;
	//ステップUIの原点
	Vector2 origin_;
	//ステップUIのサイズ
	Vector2 scale_;
	//ステップUIのアルファ値
	float alpha_;
	//ステップUIの画像ID
	SPRITE_ID ID_;
};