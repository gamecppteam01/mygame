#include "AnimationDx.h"
#include "../math/MathHelper.h"
#include"Model.h"
#include"../Math/Matrix.h"
#include <DxLib.h>
#include <math.h>
#include <algorithm>

AnimationDx::~AnimationDx()
{
	clearModel();
}

void AnimationDx::Update(const float frameTime)
{
	// �t���O������
	if(isLoop_)isAnimEnd_ = false;

	// �O�A�j���[�V�������f�^�b�`
	MV1DetachAnim(modelHandle_, anim_);
	MV1DetachAnim(modelHandle_, prevAnim_);

	// ���A�j���[�V�������A�^�b�`
	anim_ = MV1AttachAnim(modelHandle_, motion_);
	// ���A�j���[�V�������X�V
	maxAnimTime_ = MV1GetAttachAnimTotalTime(modelHandle_, anim_);
	animTimer_	+= frameTime*animSpeed_;
	if (animTimer_ >= maxAnimTime_)
	{
		if(isLoop_) animTimer_ = fmodf(animTimer_, maxAnimTime_);
		else isAnimEnd_ = true;
	}

	// �O�A�j���[�V�������A�^�b�`
	prevAnim_ = MV1AttachAnim(modelHandle_, prevMotion_);
	// �O�A�j���[�V�����X�V
	float prevMaxAnimTime = MV1GetAttachAnimTotalTime(modelHandle_, prevAnim_);
	if (prevLoop_) {
		prevAnimTimer_ += frameTime*animSpeed_;
		prevAnimTimer_ = fmodf(prevAnimTimer_, prevMaxAnimTime);
	}
	else {
		prevAnimTimer_ = prevMaxAnimTime;
	}
	// �u�����h���̍X�V
	rate_ += RATE_TIME;
	rate_ = MathHelper::Clamp(rate_, 0.0f, 1.0f);
}

void AnimationDx::Draw(const Matrix& rotation) const
{
	// �A�j���[�V�����̃u�����h
	MV1SetAttachAnimBlendRate(modelHandle_, prevAnim_, 1.0f - rate_);
	MV1SetAttachAnimBlendRate(modelHandle_, anim_, rate_);
	// �`��
	MV1SetAttachAnimTime(modelHandle_, prevAnim_, prevAnimTimer_);
	MV1SetAttachAnimTime(modelHandle_, anim_, animTimer_);

	Model::GetInstance().Draw(modelHandle_, rotation);
}

void AnimationDx::ChangeAnim(const int motion, const float frame,float animSpeed, bool isLoop,float blend)
{
	// ���݂Ɠ������[�V�����̏ꍇ�͉������Ȃ�
	if (motion_ == motion) return;

	prevMotion_ = motion_;
	motion_		= motion;
	prevAnimTimer_ = animTimer_;
	animTimer_	= frame;
	rate_		= 1.0f - blend;

	// �O�A�j���[�V�������f�^�b�`
	MV1DetachAnim(modelHandle_, anim_);
	MV1DetachAnim(modelHandle_, prevAnim_);

	// ���A�j���[�V�������A�^�b�`
	anim_ = MV1AttachAnim(modelHandle_, motion_);
	// �O�A�j���[�V�������A�^�b�`
	prevAnim_ = MV1AttachAnim(modelHandle_, prevMotion_);

	maxAnimTime_ = MV1GetAttachAnimTotalTime(modelHandle_, anim_);

	//���[�v����ۑ����Ď��̃��[�v��ݒ肷��
	prevLoop_ = isLoop_;
	isLoop_ = isLoop;
	animSpeed_ = animSpeed;
}

void AnimationDx::SetHandle(const int & handle)
{
	if (modelHandle_ != -1)clearModel();
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

void AnimationDx::clearModel()
{
	MV1DeleteModel(modelHandle_);
}



