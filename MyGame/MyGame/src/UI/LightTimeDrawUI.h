#pragma once
#include"../Math/Vector2.h"
#include"../Math/Vector3.h"

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
	void draw_enemy(const Vector2& position)const;
	void draw_player(const Vector3& position, const Vector3& upVector, float rate=1.0f)const;

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