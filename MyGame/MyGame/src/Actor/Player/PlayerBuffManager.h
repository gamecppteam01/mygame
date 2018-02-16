#pragma once
#include<memory>

class Player;
class PlayerBuffManager {
public:
	PlayerBuffManager();
	void setPlayer(Player* player);
	void update(float deltaTime);//�X�V

	void shield(int guardCount = 2);//�V�[���h����
	bool hit(int damage = 1);//��e���̃_���[�W����
private:
	int shield_count_{ 0 };//�U����������
	bool isCreateEffect_{ false };
	float timeCount_{ 0.0f };//�G�t�F�N�g�����^�C�}�[

	Player* player_;//�e
};