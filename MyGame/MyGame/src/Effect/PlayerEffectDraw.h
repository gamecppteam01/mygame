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

	void pauseSound();
	void restartSound();

	int getBeginKey()const { return beginKey_; }
	int getLoopKey()const { return loopKey_; }
	int getEndKey()const { return endKey_; }
private:
	Player* player_;
	int key_;//わっか

	float seVolume_{ 0.1f };//SE音量

	float time_{ 0.0f };

	int beginKey_{ -1 };//ではじめ
	int loopKey_{ -1 };//るーぷ
	int endKey_{ -1 };//おわり

	int playState_{ 0 };

	float sincount{ 0.0f };
	float endtime{ 0.0f };

	Vector2 PointLight_position;
	Vector2 PointLeft_position;
	Vector2 PointRight_position;
	
	float PointLeft_alpha{ 1.0f };
	float PointRight_alpha{ 1.0f };
	float PointLight_alpha{ 0.0f };
};