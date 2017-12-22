#include "PlayerEffectDraw.h"
#include "../Graphic/Sprite.h"
#include"../Graphic/DebugDraw.h"
#include"../Define.h"
#include"../Sound/Sound.h"


static const float defTime = 0.2f;
static const float sizeRate = 0.7f;
static const float posy = 0.0f;
PlayerEffectDraw::PlayerEffectDraw(Player * player):player_(player){
}

PlayerEffectDraw::~PlayerEffectDraw(){
}

void PlayerEffectDraw::Initialize(){
	state_ = State::None;
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
	//if(EffekseerManager::GetInstance().isPlayEffect3D(beginKey_))EffekseerManager::GetInstance().StopEffect3D(beginKey_);
	//if (EffekseerManager::GetInstance().isPlayEffect3D(loopKey_))EffekseerManager::GetInstance().StopEffect3D(loopKey_);
	//if (EffekseerManager::GetInstance().isPlayEffect3D(endKey_))EffekseerManager::GetInstance().StopEffect3D(endKey_);
	//if (EffekseerManager::GetInstance().isPlayEffect3D(key_))EffekseerManager::GetInstance().StopEffect3D(key_);

}

void PlayerEffectDraw::Update(float deltatime){
	seVolume_ = MathHelper::Clamp(seVolume_, 0.0f, 0.4f);

	//”{—¦ã‚ª‚Á‚Ä‚½‚ç
	if (player_->getPlayerScoreRate() > 1.0f) {
		//‰¹º‚ÌÄ¶
		if (!Sound::GetInstance().IsPlaySE(SE_ID::CHEER_SE)) {
			Sound::GetInstance().SetSEVolume(SE_ID::CHEER_SE, seVolume_);
			Sound::GetInstance().PlaySE(SE_ID::CHEER_SE);
		}
		else {
			seVolume_ += deltatime;
			Sound::GetInstance().SetSEVolume(SE_ID::CHEER_SE, seVolume_);

		}
	}
	switch (state_)
	{
	case PlayerEffectDraw::State::In:
		in(deltatime);
		break;
	case PlayerEffectDraw::State::Stay:
		stay(deltatime);
		break;
	case PlayerEffectDraw::State::End:
		out(deltatime);
		break;
	case PlayerEffectDraw::State::None:
		none(deltatime);
		break;
	default:
		break;
	}
	
}

void PlayerEffectDraw::Draw()const {
	if (state_ == State::None)return;

	Sprite::GetInstance().Draw(SPRITE_ID::POINTUP_AUDIENCE_LEFT, PointLeft_position, Sprite::GetInstance().GetSize(SPRITE_ID::POINTUP_AUDIENCE_LEFT) / 2, PointLeft_alpha, Vector2::One*0.5f);
	Sprite::GetInstance().Draw(SPRITE_ID::POINTUP_AUDIENCE_RIGHT, PointRight_position, Sprite::GetInstance().GetSize(SPRITE_ID::POINTUP_AUDIENCE_RIGHT) / 2, PointRight_alpha, Vector2::One*0.5f);
	Sprite::GetInstance().Draw(SPRITE_ID::POINTUP_LIGHT, SCREEN_SIZE - Sprite::GetInstance().GetSize(SPRITE_ID::POINTUP_LIGHT) / 2, Sprite::GetInstance().GetSize(SPRITE_ID::POINTUP_LIGHT) / 2, PointLight_alpha, Vector2::One);
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

void PlayerEffectDraw::in(float deltaTime)
{
	time_ += deltaTime*5.0f;
	PointLeft_position = Vector2::Lerp(Vector2(0, SCREEN_SIZE.y) + Vector2(-150, 150), Vector2(0, SCREEN_SIZE.y), time_);
	PointRight_position = Vector2::Lerp(Vector2(SCREEN_SIZE) + Vector2(150, 150), Vector2(SCREEN_SIZE), time_);
	PointRight_alpha = time_;
	PointLeft_alpha = time_;
	PointLight_alpha = time_;
	if (time_ >= 1.0f) {
		changeState(State::Stay);
	}
}

void PlayerEffectDraw::stay(float deltaTime)
{
	sincount += 4;
	sincount = std::fmodf(sincount, 360);
	PointLeft_position = Vector2::Lerp(Vector2(0, SCREEN_SIZE.y), Vector2(0, SCREEN_SIZE.y) + Vector2(150, -150), std::abs(MathHelper::Sin(sincount)));
	PointRight_position = Vector2::Lerp(Vector2(SCREEN_SIZE), Vector2(SCREEN_SIZE) - Vector2(150, 150), std::abs(MathHelper::Sin(sincount)));

	if (player_->getPlayerScoreRate() <= 1.1f) {
		changeState(State::End);
	}
}
void PlayerEffectDraw::out(float deltaTime)
{
	endtime += deltaTime*5.0f;
	PointLight_alpha = 1.0f - endtime;
	PointRight_alpha = 1.0f - endtime;
	PointLeft_alpha = 1.0f - endtime;
	sincount += 4;
	sincount = std::fmodf(sincount, 360);
	PointLeft_position = Vector2::Lerp(Vector2(0, SCREEN_SIZE.y), Vector2(0, SCREEN_SIZE.y) + Vector2(150, -150), std::abs(MathHelper::Sin(sincount)));
	PointRight_position = Vector2::Lerp(Vector2(SCREEN_SIZE), Vector2(SCREEN_SIZE) - Vector2(150, 150), std::abs(MathHelper::Sin(sincount)));

	if (endtime >= 1.0f) {
		changeState(State::None);
	}
}

void PlayerEffectDraw::none(float deltaTime)
{
	if (player_->getPlayerScoreRate() > 1.0f) {
		changeState(State::In);
	}
}

void PlayerEffectDraw::changeState(State s)
{
	state_ = s;

	switch (state_)
	{
	case PlayerEffectDraw::State::In:
		sincount = 0.0f;
		time_ = 0.0f;
		endtime = 0.0f;
		PointLight_alpha = 0.0f;
		PointRight_alpha = 1.0f;
		PointLeft_alpha = 1.0f;
		PointLeft_position = Vector2(0, SCREEN_SIZE.y) + Vector2(-150, 150);
		PointRight_position = Vector2(SCREEN_SIZE) + Vector2(150, 150);
		break;
	case PlayerEffectDraw::State::Stay:
		break;
	case PlayerEffectDraw::State::End:
		break;
	case PlayerEffectDraw::State::None:
		break;
	default:
		break;
	}
}
