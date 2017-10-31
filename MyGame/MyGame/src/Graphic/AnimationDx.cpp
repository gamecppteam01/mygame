#include "AnimationDx.h"
#include "../math/MathHelper.h"
#include"Model.h"
#include"../Math/Matrix.h"
#include <DxLib.h>
#include <math.h>
#include <algorithm>

void AnimationDx::Update(const float frameTime)
{
	// フラグ初期化
	isAnimEnd_ = false;

	// 前アニメーションをデタッチ
	MV1DetachAnim(modelHandle_, anim_);
	MV1DetachAnim(modelHandle_, prevAnim_);

	// 今アニメーションをアタッチ
	anim_ = MV1AttachAnim(modelHandle_, motion_);
	// 今アニメーションを更新
	maxAnimTime_ = MV1GetAttachAnimTotalTime(modelHandle_, anim_);
	animTimer_	+= frameTime;
	if (animTimer_ >= maxAnimTime_)
	{
		isAnimEnd_ = true;
		animTimer_ = fmodf(animTimer_, maxAnimTime_);
	}

	// 前アニメーションをアタッチ
	prevAnim_ = MV1AttachAnim(modelHandle_, prevMotion_);
	// 前アニメーション更新
	float prevMaxAnimTime = MV1GetAttachAnimTotalTime(modelHandle_, prevAnim_);
	prevAnimTimer_ += frameTime;
	prevAnimTimer_ = fmodf(prevAnimTimer_, prevMaxAnimTime);

	// ブレンド率の更新
	rate_ += RATE_TIME;
	rate_ = MathHelper::Clamp(rate_, 0.0f, 1.0f);
}

void AnimationDx::Draw(const Matrix& rotation) const
{
	// アニメーションのブレンド
	MV1SetAttachAnimBlendRate(modelHandle_, prevAnim_, 1.0f - rate_);
	MV1SetAttachAnimBlendRate(modelHandle_, anim_, rate_);
	// 描画
	MV1SetAttachAnimTime(modelHandle_, prevAnim_, prevAnimTimer_);
	MV1SetAttachAnimTime(modelHandle_, anim_, animTimer_);

	Model::GetInstance().Draw(modelHandle_, rotation);
}

void AnimationDx::ChangeAnim(const int motion, const float frame)
{
	// 現在と同じモーションの場合は何もしない
	if (motion_ == motion) return;

	prevMotion_ = motion_;
	motion_		= motion;
	prevAnimTimer_ = animTimer_;
	animTimer_	= frame;
	rate_		= 0.0f;

	// 前アニメーションをデタッチ
	MV1DetachAnim(modelHandle_, anim_);
	MV1DetachAnim(modelHandle_, prevAnim_);

	// 今アニメーションをアタッチ
	anim_ = MV1AttachAnim(modelHandle_, motion_);
	// 前アニメーションをアタッチ
	prevAnim_ = MV1AttachAnim(modelHandle_, prevMotion_);

	maxAnimTime_ = MV1GetAttachAnimTotalTime(modelHandle_, anim_);
}

void AnimationDx::SetHandle(const int & handle)
{
	modelHandle_ = MV1DuplicateModel(handle);
}

bool AnimationDx::IsAnimEnd() const
{
	return isAnimEnd_;
}

float AnimationDx::GetCurrentAnimFrame() const
{
	return animTimer_;
}

float AnimationDx::GetEndAnimFrame(int motion) const
{
	return MV1GetAttachAnimTotalTime(modelHandle_, motion);
}

float AnimationDx::GetAnimMaxTime() const
{
	return maxAnimTime_/60.0f;
}

float AnimationDx::GetAnimMaxTime(int index) const
{
	return MV1GetAnimTotalTime(modelHandle_, index) / 60.0f;
}



