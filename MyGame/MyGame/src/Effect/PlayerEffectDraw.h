#pragma once
#include"../Actor/Player/Player.h"

class PlayerEffectDraw {
private:
	enum class State {
		In,
		Stay,
		End,
		None
	};
public:
	PlayerEffectDraw(Player* player);
	~PlayerEffectDraw();
	void Initialize();
	void setPlayerEffectDraw(Player* player);
	void finalize();
	void Update(float deltatime);
	void Draw()const;

	void pauseSound();
	void restartSound();

	void in(float deltaTime);
	void stay(float deltaTime);
	void out(float deltaTime);
	void none(float deltaTime);
	void changeState(State s);
private:
	Player* player_;

	float seVolume_{ 0.1f };//SE‰¹—Ê

	float time_{ 0.0f };

	State state_{ State::None };

	float sincount{ 0.0f };
	float endtime{ 0.0f };

	Vector2 PointLight_position;
	Vector2 PointLeft_position;
	Vector2 PointRight_position;
	
	float PointLeft_alpha{ 1.0f };
	float PointRight_alpha{ 1.0f };
	float PointLight_alpha{ 0.0f };
};