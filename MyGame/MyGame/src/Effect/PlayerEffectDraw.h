#pragma once
#include"../Actor/Player/Player.h"

class PlayerEffectDraw {
public:
	PlayerEffectDraw(Player* player);
	~PlayerEffectDraw();
	void Initialize();
	void setPlayerEffectDraw(Player* player);
	void finalize();
	void Update(float deltatime);
	void Draw()const;
private:
	Player* player_;
	int key_;

	float time_{ 0.0f };

	int beginKey_{ -1 };
	int loopKey_{ -1 };
	int endKey_{ -1 };

	int playState_{ 0 };

	float sincount{ 0.0f };

	Vector2 PointLight_position;
	Vector2 PointLeft_position;
	Vector2 PointRight_position;
	
	float PointLeft_alpha{ 1.0f };
	float PointRight_alpha{ 1.0f };
	float PointLight_alpha{ 0.0f };
};