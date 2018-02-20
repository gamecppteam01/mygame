#include "PlayerBuffManager.h"
#include"../../Graphic/EffekseerManager.h"
#include"Player.h"

static const float createEffectTime = 0.3f;//エフェクトの生成周期

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
	if (shield_count_ < guardCount)shield_count_ = guardCount;//シールド値を高い方に合わせる
	isCreateEffect_ = true;

	int effectID = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::SPIN_SHIELD_EFFECT, player_->position());
	EffekseerManager::GetInstance().SetPositionTrackTarget(EFFECT_ID::SPIN_SHIELD_EFFECT, effectID, &player_->position());

}
bool PlayerBuffManager::hit(int damage) {
	bool result = shield_count_ > 0;//体力が0より多いか
	shield_count_ = max(shield_count_ - damage, 0);//シールド値にダメージを与える(最低値は0)

	//シールドがなくなったらエフェクトの停止
	if (shield_count_ <= 0) {
		isCreateEffect_ = false;
	}
	return result;
}
