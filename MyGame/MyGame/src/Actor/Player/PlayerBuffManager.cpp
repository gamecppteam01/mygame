#include "PlayerBuffManager.h"
#include"../../Graphic/EffekseerManager.h"
#include"Player.h"

static const float createEffectTime = 0.3f;//�G�t�F�N�g�̐�������

PlayerBuffManager::PlayerBuffManager() {

}

void PlayerBuffManager::setPlayer(Player* player){
	player_ = player;
}

void PlayerBuffManager::update(float deltaTime)
{
	if (!isCreateEffect_)return;


	timeCount_ += deltaTime;
	if(timeCount_>= createEffectTime){
		timeCount_ = 0.0f;
		int effectID = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::SPIN_SHIELD_EFFECT, player_->position());
		EffekseerManager::GetInstance().SetPositionTrackTarget(EFFECT_ID::SPIN_SHIELD_EFFECT, effectID, &player_->position());
	}
}

void PlayerBuffManager::shield(int guardCount) {
	if (shield_count_ < guardCount)shield_count_ = guardCount;//�V�[���h�l���������ɍ��킹��
	isCreateEffect_ = true;

	int effectID = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::SPIN_SHIELD_EFFECT, player_->position());
	EffekseerManager::GetInstance().SetPositionTrackTarget(EFFECT_ID::SPIN_SHIELD_EFFECT, effectID, &player_->position());

}
bool PlayerBuffManager::hit(int damage) {
	bool result = shield_count_ > 0;//�̗͂�0��葽����
	shield_count_ = max(shield_count_ - damage, 0);//�V�[���h�l�Ƀ_���[�W��^����(�Œ�l��0)

	//�V�[���h���Ȃ��Ȃ�����G�t�F�N�g�̒�~
	if (shield_count_ <= 0) {
		isCreateEffect_ = false;
	}
	return result;
}
