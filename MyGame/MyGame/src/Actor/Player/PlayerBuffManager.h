#pragma once
#include<memory>

class Player;
class PlayerBuffManager {
public:
	PlayerBuffManager();
	void setPlayer(Player* player);
	void update(float deltaTime);//更新

	void shield(int guardCount = 2);//シールド生成
	bool hit(int damage = 1);//被弾時のダメージ処理
private:
	int shield_count_{ 0 };//攻撃無効化回数
	bool isCreateEffect_{ false };
	float timeCount_{ 0.0f };//エフェクト生成タイマー

	Player* player_;//親
};