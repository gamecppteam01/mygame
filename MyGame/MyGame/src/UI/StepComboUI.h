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
	
	void IsStart();
	void IsEnd();
	bool getIsDead() const;
	bool getIsStart() const;
	SPRITE_ID GetId() const;
	int getPos();

private:
	SPRITE_ID id_;
	Vector2 position_;
	float pos;
	float alpha_;
	float timer_;
	bool IsStart_{ false };
	bool IsDead_{ false };
	bool IsEnd_{ false };
	
};