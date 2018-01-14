#pragma once
#include"../Math/Vector2.h"
#include"../Game/ID.h"


class StepParts {
public:
	enum class DrawStepType {
		Quarter,
		Half,
		Turn,
		Spin
	};
	enum class State {
		Start,
		Normal,
		Slide
	};
public:
	StepParts(DrawStepType type,const Vector2& position);

	void update(float deltaTime);

	void draw()const;

	void dead();

	bool isDead()const;
	bool isStartDead()const;
	void start(float deltaTime);
	void normal(float deltaTime);
	void dead(float deltaTime);
	void slide(float deltaTime);

	void startSlide(const Vector2& slidePos);

	void setID(DrawStepType type);

	void changeState(State state);
private:
	State state_{ State::Start };

	Vector2 position_;
	Vector2 firstPos_;
	Vector2 targetPos_;
	float alpha_{ 0.0f };
	bool isDead_{ false };
	DrawStepType type_{ DrawStepType::Quarter };

	bool startDead_{ false };
	float countTimer_{ 0.0f };
	SPRITE_ID id_{ SPRITE_ID::QUATER_SPRITE };
};