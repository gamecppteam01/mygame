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
};