#pragma once
#include"../../../Math/Vector2.h"
#include"../../../DataManager/DataManager.h"

class KeyCursor {
public:
	KeyCursor(const Vector2& position);
	void initialize(const Vector2 & position);
	void update(float deltaTime);
	void draw(const Vector2& position)const;
	void drawWide(const Vector2& position)const;
	void setPosition(const Vector2& position);
	float getPosition();

private:
	Vector2 targetPosition_;
	Vector2 basePosition_;
	float moveTime_{ 0.0f };
	float animationTime_{ 0.0f };
};