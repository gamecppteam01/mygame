#include "PlayerEffectDraw.h"
#include "../Graphic/EffekseerManager.h"

PlayerEffectDraw::PlayerEffectDraw(Player * player):player_(player){
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
}

void PlayerEffectDraw::Draw()const{
	if (player_->getPlayerScoreRate() > 1.0f) {
		//EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::POINT_UP_EFFECT, player_->position());
		int key = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::POINT_UP_EFFECT, player_->position(), Vector3::Zero, Vector3::One * 2);
		EffekseerManager::GetInstance().SetPositionTrackTarget(EFFECT_ID::POINT_UP_EFFECT, key, &player_->position());
		DrawFormatString(100, 400, GetColor(255, 255, 255), "エフェクト出てる！スコア高くなってる！");
	}
}
