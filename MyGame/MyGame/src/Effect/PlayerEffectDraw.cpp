#include "PlayerEffectDraw.h"
#include "../Graphic/EffekseerManager.h"
#include"../Graphic/DebugDraw.h"


static const float defTime = 0.2f;

PlayerEffectDraw::PlayerEffectDraw(Player * player):player_(player),key_(-1){
}

PlayerEffectDraw::~PlayerEffectDraw(){
	finalize();
}

void PlayerEffectDraw::Initialize(){
	playState_ = 0;
	time_ = 0.0f;
}

void PlayerEffectDraw::setPlayerEffectDraw(Player * player){
	player_ = player;
}

void PlayerEffectDraw::finalize(){
	player_ = nullptr;
}

void PlayerEffectDraw::Update(float deltatime){

	//”{—¦ã‚ª‚Á‚Ä‚½‚ç
	if (player_->getPlayerScoreRate() > 1.0f) {
		switch (playState_)
		{
		case 0: {
			if (EffekseerManager::GetInstance().isPlayEffect3D(endKey_))return;
			playState_++;
			beginKey_ = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::POINT_UP_BEGIN_EFFECT, Vector3::Zero, Vector3::Zero, Vector3::One);
			EffekseerManager::GetInstance().SetPosPlayEffect3D(beginKey_, Vector3{ 0.0f,10.0f,0.0f });
			break;
		}
		case 1: {
			time_ += deltatime;
			if (time_ < defTime)return;
			//if (EffekseerManager::GetInstance().isPlayEffect3D(beginKey_))return;
			playState_++;
			if (!EffekseerManager::GetInstance().isPlayEffect3D(loopKey_))loopKey_ = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::POINT_UP_LOOP_EFFECT, Vector3::Zero, Vector3::Zero, Vector3::One);
			EffekseerManager::GetInstance().SetPosPlayEffect3D(loopKey_, Vector3{ 0.0f,10.0f,0.0f });
			break;
		}
		case 2: {
			if (EffekseerManager::GetInstance().isPlayEffect3D(key_))return;
			key_ = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::POINT_UP_EFFECT, Vector3::Zero, Vector3::Zero, Vector3::One);
			EffekseerManager::GetInstance().SetPosPlayEffect3D(key_, Vector3{ 0.0f,10.0f,0.0f });
			break;
		}
		case 3: {
			if (!EffekseerManager::GetInstance().isPlayEffect3D(endKey_)) {
				time_ = 0.0f;
				playState_ = 0;
			}
		}

		default:
			break;
		}
	}
	//”{—¦ã‚ª‚Á‚Ä–³‚©‚Á‚½‚ç
	else {
		if (playState_ != 0) {
			switch (playState_) {
			case 1:
				EffekseerManager::GetInstance().StopEffect3D(beginKey_);
			case 2: {
				if (EffekseerManager::GetInstance().isPlayEffect3D(endKey_))return;
				playState_++;
				endKey_ = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::POINT_UP_END_EFFECT, Vector3::Zero, Vector3::Zero, Vector3::One);
				EffekseerManager::GetInstance().SetPosPlayEffect3D(endKey_, Vector3{ 0.0f,10.0f,0.0f });
				break;
			}
			case 3: {
				if (!EffekseerManager::GetInstance().isPlayEffect3D(endKey_)) {
					time_ = 0.0f;
					playState_ = 0;
				}
			}
			default:
				break;
			}

		}
		if (EffekseerManager::GetInstance().isPlayEffect3D(loopKey_)) {
			EffekseerManager::GetInstance().StopEffect3D(loopKey_);
		}
		
	}

	//if (player_->getPlayerScoreRate() > 1.0f) {
	//	if (EffekseerManager::GetInstance().isPlayEffect3D(key_))return;
	//		//EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::POINT_UP_EFFECT, player_->position());
	//	key_ = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::POINT_UP_EFFECT, Vector3::Zero, Vector3::Zero, Vector3::One);
	//	EffekseerManager::GetInstance().SetPosPlayEffect3D(key_, Vector3{ 0.0f,10.0f,0.0f });
	//	//EffekseerManager::GetInstance().SetPositionTrackTarget(EFFECT_ID::POINT_UP_EFFECT, key, &player_->position());
	//}
	//else {
	//	if (!EffekseerManager::GetInstance().isPlayEffect3D(key_))return;
	//	EffekseerManager::GetInstance().StopEffect3D(key_);
	//}

}

void PlayerEffectDraw::Draw()const{

	DebugDraw::DebugDrawFormatString(700, 100, GetColor(255, 255, 255), "%d", playState_);
}
