#pragma once
#include "UI.h"
#include "../Graphic/Sprite.h"
#include"../Math/Math.h"


class StepComboUI : public UI {
public:
	StepComboUI() = default;
	StepComboUI(const SPRITE_ID& id,const Vector2& position);
	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw() const override;
	bool IsCount();

	void alpha(const float& alpha);
	void position(const Vector2& pos);
	SPRITE_ID GetId() const;

private:
	SPRITE_ID id_;
	Vector2 position_;
	float alpha_;
	float timer_;
	bool IsCount_{ false };
	
};