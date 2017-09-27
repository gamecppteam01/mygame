#pragma once
#include"Effect.h"

class CircleEffect :public Effect {
public:
	CircleEffect(float maxSize,float effectTime);
	virtual void Update(float deltaTime) override;
	virtual void Draw(const Vector3& position)const override;

private:
	float maxSize_;
	float effectTime_;
	float effectMaxTime_;
};