#include "PlayerEffectDraw.h"
#include "../Graphic/EffekseerManager.h"
#include "../Graphic/Sprite.h"
#include"../Graphic/DebugDraw.h"
#include"../Define.h"
#include"../Sound/Sound.h"


static const float defTime = 0.2f;

PlayerEffectDraw::PlayerEffectDraw(Player * player):player_(player),key_(-1){
}

PlayerEffectDraw::~PlayerEffectDraw(){
}

void PlayerEffectDraw::Initialize(){
	playState_ = 0;
	time_ = 0.0f;
	sincount = 0.0f;
	endtime = 0.0f;
	seVolume_ = 0.0f;
	PointLight_alpha = 0.0f;
	PointRight_alpha = 1.0f;
	PointLeft_alpha = 1.0f;
	PointLeft_position = Vector2(0, SCREEN_SIZE.y) + Vector2(-150, 150);
	PointRight_position = Vector2(SCREEN_SIZE) + Vector2(150, 150);
}

void PlayerEffectDraw::setPlayerEffectDraw(Player * player){
	player_ = player;
}

void PlayerEffectDraw::finalize(){
	player_ = nullptr;
	if(EffekseerManager::GetInstance().isPlayEffect3D(beginKey_))EffekseerManager::GetInstance().StopEffect3D(beginKey_);
	if (EffekseerManager::GetInstance().isPlayEffect3D(loopKey_))EffekseerManager::GetInstance().StopEffect3D(loopKey_);
	if (EffekseerManager::GetInstance().isPlayEffect3D(endKey_))EffekseerManager::GetInstance().StopEffect3D(endKey_);
	if (EffekseerManager::GetInstance().isPlayEffect3D(key_))EffekseerManager::GetInstance().StopEffect3D(key_);

}

void PlayerEffectDraw::Update(float deltatime){
	seVolume_ = MathHelper::Clamp(seVolume_, 0.0f, 0.4f);

	//”{—¦ã‚ª‚Á‚Ä‚½‚ç
	if (player_->getPlayerScoreRate() > 1.0f) {
		if (!Sound::GetInstance().IsPlaySE(SE_ID::CHEER_SE)) {
			Sound::GetInstance().SetSEVolume(SE_ID::CHEER_SE, seVolume_);
			Sound::GetInstance().PlaySE(SE_ID::CHEER_SE);
		}
		else {
			seVolume_ += deltatime;
			Sound::GetInstance().SetSEVolume(SE_ID::CHEER_SE,seVolume_);

		}
		switch (playState_)
		{
		case 0: {
			if (EffekseerManager::GetInstance().isPlayEffect3D(endKey_))return;
			sincount = 0.0f;
			PointLight_alpha = 0.0f;
			PointRight_alpha = 1.0f;
			PointLeft_alpha = 1.0f;
			PointLeft_position = Vector2(0, SCREEN_SIZE.y) + Vector2(-150, 150);
			PointRight_position = Vector2(SCREEN_SIZE) + Vector2(150, 150);

			playState_++;
			beginKey_ = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::POINT_UP_BEGIN_EFFECT, Vector3::Zero, Vector3::Zero, Vector3::One);
			EffekseerManager::GetInstance().SetPosPlayEffect3D(beginKey_, Vector3{ 0.0f,10.0f,0.0f });
			break;
		}
		case 1: {
			time_ += deltatime;
			PointLeft_position = Vector2::Lerp(Vector2(0, SCREEN_SIZE.y) + Vector2(-150, 150), Vector2(0, SCREEN_SIZE.y), time_ * 5);
			PointRight_position = Vector2::Lerp(Vector2(SCREEN_SIZE) + Vector2(150, 150), Vector2(SCREEN_SIZE), time_ * 5);
			PointLight_alpha = time_ * 5;

			if (time_ < defTime)return;
			//if (EffekseerManager::GetInstance().isPlayEffect3D(beginKey_))return;
			playState_++;
			if (!EffekseerManager::GetInstance().isPlayEffect3D(loopKey_))loopKey_ = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::POINT_UP_LOOP_EFFECT, Vector3::Zero, Vector3::Zero, Vector3::One);
			EffekseerManager::GetInstance().SetPosPlayEffect3D(loopKey_, Vector3{ 0.0f,10.0f,0.0f });
			break;
		}
		case 2: {
			sincount += 4;
			sincount = std::fmodf(sincount, 360);
			PointLeft_position = Vector2::Lerp(Vector2(0, SCREEN_SIZE.y), Vector2(0, SCREEN_SIZE.y) + Vector2(150, -150), std::abs(MathHelper::Sin(sincount)));
			PointRight_position = Vector2::Lerp(Vector2(SCREEN_SIZE), Vector2(SCREEN_SIZE) - Vector2(150, 150), std::abs(MathHelper::Sin(sincount)));
			
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
		if (Sound::GetInstance().IsPlaySE(SE_ID::CHEER_SE)) {
			seVolume_ -= deltatime;
			Sound::GetInstance().SetSEVolume(SE_ID::CHEER_SE, seVolume_);

			if(Sound::GetInstance().IsSEVolume(SE_ID::CHEER_SE)<=0.01f)Sound::GetInstance().StopSE(SE_ID::CHEER_SE);
		}
		if (playState_ != 0) {
			switch (playState_) {
			case 1:
				EffekseerManager::GetInstance().StopEffect3D(beginKey_);
			case 2: {
				if (EffekseerManager::GetInstance().isPlayEffect3D(endKey_))return;
				endtime = 0.0f;
				playState_++;
				endKey_ = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::POINT_UP_END_EFFECT, Vector3::Zero, Vector3::Zero, Vector3::One);
				EffekseerManager::GetInstance().SetPosPlayEffect3D(endKey_, Vector3{ 0.0f,10.0f,0.0f });
				break;
			}
			case 3: {
				endtime += deltatime;
				endtime = min(endtime, 0.2f);
				PointLight_alpha = 1 - endtime * 5;
				PointRight_alpha = 1 - endtime * 5;
				PointLeft_alpha = 1 - endtime * 5;
				sincount += 4;
				sincount = std::fmodf(sincount, 360);
				PointLeft_position = Vector2::Lerp(Vector2(0, SCREEN_SIZE.y), Vector2(0, SCREEN_SIZE.y) + Vector2(150, -150), std::abs(MathHelper::Sin(sincount)));
				PointRight_position = Vector2::Lerp(Vector2(SCREEN_SIZE), Vector2(SCREEN_SIZE) - Vector2(150, 150), std::abs(MathHelper::Sin(sincount)));
				//PointLeft_position = Vector2::Lerp(Vector2(0, SCREEN_SIZE.y), Vector2(0, SCREEN_SIZE.y) + Vector2(-150, 150), endtime * 5);
				//PointRight_position = Vector2::Lerp(Vector2(SCREEN_SIZE), Vector2(SCREEN_SIZE) + Vector2(150, 150), endtime * 5);
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
	if (player_->getPlayerScoreRate() > 1.0f || endtime <= 0.199f) {
		Sprite::GetInstance().Draw(SPRITE_ID::POINTUP_AUDIENCE_LEFT, PointLeft_position, Sprite::GetInstance().GetSize(SPRITE_ID::POINTUP_AUDIENCE_LEFT) / 2 ,PointLeft_alpha ,Vector2::One*0.5f);
		Sprite::GetInstance().Draw(SPRITE_ID::POINTUP_AUDIENCE_RIGHT, PointRight_position, Sprite::GetInstance().GetSize(SPRITE_ID::POINTUP_AUDIENCE_RIGHT) / 2, PointRight_alpha,Vector2::One*0.5f);
		Sprite::GetInstance().Draw(SPRITE_ID::POINTUP_LIGHT, SCREEN_SIZE - Sprite::GetInstance().GetSize(SPRITE_ID::POINTUP_LIGHT) / 2, Sprite::GetInstance().GetSize(SPRITE_ID::POINTUP_LIGHT) / 2, PointLight_alpha,Vector2::One);
	}
}

void PlayerEffectDraw::pauseSound()
{
	Sound::GetInstance().StopSE(SE_ID::CHEER_SE);
}

void PlayerEffectDraw::restartSound()
{
	if (player_->getPlayerScoreRate() <= 1.0f)return;

	Sound::GetInstance().SetSEVolume(SE_ID::CHEER_SE, seVolume_);
	Sound::GetInstance().PlaySE(SE_ID::CHEER_SE, DX_PLAYTYPE_BACK, FALSE);

}
