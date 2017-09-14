#include "AnimationDx.h"
#include "../math/MathHelper.h"
#include <DxLib.h>
#include <math.h>
#include <algorithm>

void AnimationDx::Update(const float frameTime)
{
	// �t���O������
	isAnimEnd_ = false;

	// �O�A�j���[�V�������f�^�b�`
	MV1DetachAnim(modelHandle_, anim_);
	MV1DetachAnim(modelHandle_, prevAnim_);

	// ���A�j���[�V�������A�^�b�`
	anim_ = MV1AttachAnim(modelHandle_, motion_);
	// ���A�j���[�V�������X�V
	maxAnimTime_ = MV1GetAttachAnimTotalTime(modelHandle_, anim_);
	animTimer_	+= frameTime;
	if (animTimer_ >= maxAnimTime_)
	{
		isAnimEnd_ = true;
		animTimer_ = fmodf(animTimer_, maxAnimTime_);
	}

	// �O�A�j���[�V�������A�^�b�`
	prevAnim_ = MV1AttachAnim(modelHandle_, prevMotion_);
	// �O�A�j���[�V�����X�V
	float prevMaxAnimTime = MV1GetAttachAnimTotalTime(modelHandle_, prevAnim_);
	prevAnimTimer_ += frameTime;
	prevAnimTimer_ = fmodf(prevAnimTimer_, prevMaxAnimTime);

	// �u�����h���̍X�V
	rate_ += RATE_TIME;
	rate_ = MathHelper::Clamp(rate_, 0.0f, 1.0f);
}

void AnimationDx::Draw() const
{
	// �A�j���[�V�����̃u�����h
	MV1SetAttachAnimBlendRate(modelHandle_, prevAnim_, 1.0f - rate_);
	MV1SetAttachAnimBlendRate(modelHandle_, anim_, rate_);
	// �`��
	MV1SetAttachAnimTime(modelHandle_, prevAnim_, prevAnimTimer_);
	MV1SetAttachAnimTime(modelHandle_, anim_, animTimer_);
}

void AnimationDx::ChangeAnim(const int motion, const float frame)
{
	// ���݂Ɠ������[�V�����̏ꍇ�͉������Ȃ�
	if (motion_ == motion) return;

	prevMotion_ = motion_;
	motion_		= motion;
	prevAnimTimer_ = animTimer_;
	animTimer_	= frame;
	rate_		= 0.0f;
}

void AnimationDx::SetHandle(const int & handle)
{
	modelHandle_ = handle;
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



