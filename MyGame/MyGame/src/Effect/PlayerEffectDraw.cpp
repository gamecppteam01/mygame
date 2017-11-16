#include "PlayerEffectDraw.h"
#include "../Graphic/EffekseerManager.h"

PlayerEffectDraw::PlayerEffectDraw(Player * player):player_(player),key_(-1){
}

PlayerEffectDraw::~PlayerEffectDraw(){
	finalize();
}

void PlayerEffectDraw::Initialize(){
}

void PlayerEffectDraw::setPlayerEffectDraw(Player * player){
	player_ = player;
}

void PlayerEffectDraw::finalize(){
	player_ = nullptr;
}

void PlayerEffectDraw::Update(float deltatime){
	if (player_->getPlayerScoreRate() > 1.0f) {
		if (EffekseerManager::GetInstance().isPlayEffect3D(key_))return;
			//EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::POINT_UP_EFFECT, player_->position());
		key_ = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::SAMPLE_EFFECT, player_->position(), Vector3::Zero, Vector3::One);
		//EffekseerManager::GetInstance().SetPositionTrackTarget(EFFECT_ID::POINT_UP_EFFECT, key, &player_->position());
		DrawFormatString(100, 400, GetColor(255, 255, 255), "エフェクト出てる！スコア高くなってる！");
	}
	else {
		if (!EffekseerManager::GetInstance().isPlayEffect3D(key_))return;
		EffekseerManager::GetInstance().StopEffect3D(key_);
	}

}

void PlayerEffectDraw::Draw()const{
}
