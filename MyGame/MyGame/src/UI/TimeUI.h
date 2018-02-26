#pragma once
#include "../Math/Math.h"
#include "../Graphic/Sprite.h"
#include "../UI/UI.h"
#include"../World/World.h"
#include "../Camera/RoundCamera.h"

class TimeUI : public UI {
public:
	TimeUI(IWorld* world ,RoundCamera* roundCamera ,const Vector2& position);
	void initialize() override;
	void update(float deltaTime) override;
	void draw() const override;
private:
	int number_;
	float sincount;
	Vector2 scale_;
	Vector2 move_;
	IWorld* world_;
	RoundCamera* roundCamera_;
};