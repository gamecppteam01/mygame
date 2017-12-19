#include "MusicScoreManager.h"
#include"TempoManager.h"
#include"../Graphic/Sprite.h"
#include"../Graphic/DxlibGraphic.h"
#include"../Math/Color.h"
#include"../Sound/TempoManager.h"
#include"../Math/Easing.h"
#include"../Graphic/EffekseerManager.h"

MusicScoreManager::MusicScoreManager(IWorld* world):
	world_(world), currentBeat_(0.0f), currentMeasure_(0.0f), isNotice_(false)
{
}

MusicScoreManager::~MusicScoreManager()
{
}

void MusicScoreManager::SetWorld(IWorld * world)
{
	world_ = world;
}

void MusicScoreManager::SetSize(const Vector2 & size){
	scoreSize_ = size;
}

void MusicScoreManager::SetMeasure(const float size)
{
	measureSize_ = size;
}

void MusicScoreManager::Initialize()
{
	isNotice_ = false;
}

void MusicScoreManager::Update(float deltaTime)
{
	currentMeasure_ = std::fmodf(world_->getCanChangedTempoManager().getMeasureCount(), world_->getCanChangedTempoManager().getMusicCount())*world_->getCanChangedTempoManager().getBeat();//何小節目か
	currentMeasure_ += std::fmodf(world_->getCanChangedTempoManager().getBeatCount(), world_->getCanChangedTempoManager().getBeat());//拍数
	currentMeasure_ += world_->getCanChangedTempoManager().getTempoCount();//1拍内での今の位置

	//currentBeatには何拍目のどのあたりにいるかが入る
	//currentMeasure_ = world_->getCanChangedTempoManager().getBeatCount();//何拍目か
	//currentBeat_ = currentMeasure_;
	currentBeat_ = world_->getCanChangedTempoManager().getTempoCount();//1拍内での今の位置
	

	if (!isNotice_) {
		scaleTimer_ -= deltaTime;
		scaleTimer_ = max(scaleTimer_, 0.0f);
		return;
	}
	scaleTimer_ += deltaTime;
	scaleTimer_ = std::fmodf(scaleTimer_, 1.0f);

}

void MusicScoreManager::Draw(const Vector2& position) const
{
	DrawCircleGauge(position.x, position.y, std::fmodf(currentMeasure_, world_->getCanChangedTempoManager().getMusicCount()) / world_->getCanChangedTempoManager().getMusicCount()*100.f, Sprite::GetInstance().GetHandle(SPRITE_ID::CIRCLE_EFFECT));
	//DrawGraph(position.x, position.y, Sprite::GetInstance().GetHandle(SPRITE_ID::BUTTON_A), TRUE);
	/*
	float right = position.x + scoreSize_.x;//右端
	float left = position.x - scoreSize_.x;//左端
	float measureSize = (right - left) / measureSize_;//1小節毎の幅

	//表示小節数分表示
	for (int i = 0; i < std::floorf(measureSize_); i++) {
		float measureleft = left + (measureSize*i);
		//1小節ごとの割合
		float notes = std::fmodf(currentMeasure_, 3);
		//ノーツの左端
		float notesLeft = MathHelper::Lerp(measureleft+measureSize, measureleft, notes / 3);

		float notesRight = notesLeft + (measureSize / 3)*2.f;
		notesRight = min(notesRight, right);

		if (i == 0&&notes > 1.f)SetDrawBright(255, 0, 0);
		
		DrawBox(notesLeft, position.y - scoreSize_.y, notesRight, position.y + scoreSize_.y, GetColor(255, 255, 255), TRUE);
		SetDrawBright(255, 255, 255);
	}
	DrawLine(position.x - scoreSize_.x, position.y - scoreSize_.y, position.x + scoreSize_.x, position.y - scoreSize_.y, GetColor(255, 0, 0),5);
	DrawLine(position.x - scoreSize_.x, position.y + scoreSize_.y, position.x + scoreSize_.x, position.y + scoreSize_.y, GetColor(255, 0, 0),5);
	//判定ライン位置
	float lineLeft = left + measureSize / 3.f*2.0f;
	DrawLine(lineLeft, position.y - scoreSize_.y*1.5f, lineLeft, position.y + scoreSize_.y*1.5f, GetColor(0, 0, 0),3);
	*/
}

void MusicScoreManager::Draw(const Vector3& position, const Vector3& upVector) const
{
	float size = 20.0f;

	Vector3 pos = ConvWorldPosToScreenPos(position);

	float percent = currentMeasure_/(world_->getCanChangedTempoManager().getMusicCount()*world_->getCanChangedTempoManager().getBeat())*100.f;
	Color c{ 0,130,200,255 };//ゲージ色
	Color fc{ 0,0,0,255 };//枠色

	if (percent >= 75.0f)c=Color(200, 130, 0,255);//4小節毎に判定

	//ライトに入ってる時限定の処理
	if (isNotice_) {
		c = { 0,180,180,255 };
		fc = { 200,130,0,255 };
		percent = 100.0f;
		float sinPos = 0.25f + MathHelper::Smoothstep(0.0f,1.0f,currentBeat_)*0.5f;//最大サイズからスタートするために0.25fズラす

		size *= 1.0f + 0.3f-std::abs(MathHelper::Sin(sinPos*360.0f)*0.3f);
		SetDrawBlendMode(DX_BLENDMODE_SUB, 255);
	}
	DrawCircleGauge3D(position, upVector, c.r, c.g, c.b, c.a, size*2.0f, percent, Sprite::GetInstance().GetHandle(SPRITE_ID::JUST_GAUGE),-90.0f);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawSprite3D(position, size, Sprite::GetInstance().GetHandle(SPRITE_ID::JUST_GAUGE_FRAME), fc.r, fc.g, fc.b, fc.a, -90.0f);

	//Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::JUST_GAUGE_FRAME)/2;
	//DrawRotaGraph2(pos.x, pos.y, origin.x, origin.y, 1.0, 0.0, Sprite::GetInstance().GetHandle(SPRITE_ID::JUST_GAUGE_FRAME), TRUE);

	//int handle = Sprite::GetInstance().GetHandle(SPRITE_ID::CIRCLE_EFFECT);

	//Vector2 size = Sprite::GetInstance().GetSize(SPRITE_ID::CIRCLE_EFFECT);

	//float notes = std::fmodf(currentMeasure_, 3);
	//float timer = notes / 3.f;

	//float angle = MathHelper::Lerp(0.0f, 360.0f, timer);
	//
	//float x1, y1, x2, y2, x3, y3, x4, y4;
	//x1 = size.x / 2;
	//y1 = 0.0f;
	//y2 = 0.0f;

	//if (angle <= 45.0f) {
	//	x2 = MathHelper::Lerp(size.x / 2, size.x, angle / 45.0f);
	//	x3 = size.x / 2;
	//	y3 = size.y / 2;
	//	x4 = size.x / 2;
	//	y4 = size.y / 2;
	//}
	//else if (angle <= 135.0f) {
	//	x2 = size.x;
	//	x3 = size.x;
	//	y3 = MathHelper::Lerp(0.0f, size.y, (angle - 45.0f) / 90.0f);
	//	x4 = size.x / 2;
	//	y4 = size.y / 2;
	//}
	////else if (angle <= 180.0f) {
	//else{
	//	x2 = size.x;
	//	x3 = size.x;
	//	y3 = size.y;
	//	x4 = size.x / 2;
	//	y4 = size.y / 2;

	//


	//}
	////DrawModiBillboard3D(position, x1, y1, x2, y2, x3, y3, x4, y4, handle, TRUE);
	//DrawModiBillboard3D(position, x1, y1, x2, y2, x3, y3, x4, y4, handle, TRUE);
}

bool MusicScoreManager::getNotice() const
{
	return isNotice_;
}

void MusicScoreManager::setNotice(bool notice)
{
	if (notice && !isNotice_) {
		handle_ = EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::FIRE_EFFECT);
		EffekseerManager::GetInstance().SetPositionTrackTarget(EFFECT_ID::FIRE_EFFECT, handle_, &world_->findActor("Player")->position());
	}
	if (!notice&&isNotice_) {
		EffekseerManager::GetInstance().StopEffect3D(handle_);
	}
	isNotice_ = notice;
}
