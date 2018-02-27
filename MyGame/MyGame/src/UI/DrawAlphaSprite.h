#pragma once
#include"../Graphic/Sprite.h"
#include<cmath>
class DrawAlphaSprite {
public:
	DrawAlphaSprite(SPRITE_ID id):id_(id), alpha_(0.0f),isActive_(false){

	}
	void init() {
		alpha_ = 0.0f;
		isActive_ = false;
	}
	void update(float deltaTime) {
		if (isActive_) {
			alpha_ = min(1.0f, alpha_ + deltaTime);
		}
		else {
			alpha_ = max(0.0f, alpha_ - deltaTime);
		}
	}
	void draw(const Vector2& position,const Vector2& size=Vector2::One)const {
		if (alpha_ > 0.0f) {
			Vector2 center = Sprite::GetInstance().GetSize(id_) / 2;
			Sprite::GetInstance().Draw(id_, position, center, alpha_, size);
		}
	}
	void active(bool isActive) {
		isActive_ = isActive;
	}
private:
	SPRITE_ID id_;
	float alpha_;
	bool isActive_;
};