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

};