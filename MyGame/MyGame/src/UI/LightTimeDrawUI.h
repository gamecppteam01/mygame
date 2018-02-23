#pragma once
#include"../Math/Vector2.h"

class LightTimeDrawUI {
private:
	enum class State {
		In,
		Keep,
		Out,
		None
	};
public:
	LightTimeDrawUI();

	void init();

	void update(float deltaTime);
	void draw(const Vector2& position)const;

	void start();
	void end();
	void isIn(bool isIn);
	void rate(float rate);

private:
	void in(float deltaTime);
	void keep(float deltaTime);
	void out(float deltaTime);
	void none(float deltaTime);

private:
	bool isDraw()const;
private:
	State state_;
	float alpha_;
	float rate_;
	bool isIn_;
};