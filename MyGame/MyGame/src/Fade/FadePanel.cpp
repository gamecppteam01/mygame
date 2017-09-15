#include "FadePanel.h"
#include "../graphic/Sprite.h"
#include "../math/MathHelper.h"

FadePanel::FadePanel() :
color_(ColorType::Black),
alpha_(1.0f),
maxAlpha_(1.0f),
actionTime_(0.0f),
inTime_(1.0f),
outTime_(1.0f),
delayTime_(0.0f)
{
	// �X�e�[�g���Z�b�g
	while (!stateStack_.empty())
	{
		stateStack_.pop();
	}
	stateStack_.push(FADE_STATUS::eStandby);
}

FadePanel::~FadePanel()
{
}

void FadePanel::Initialize()
{
	color_		= ColorType::Black;
	alpha_		= 0.0f;
	maxAlpha_	= 1.0f;
	actionTime_	= 0.0f;
	inTime_		= 1.0f;
	outTime_	= 1.0f;
	delayTime_  = 0.0f;

	while (!stateStack_.empty())
		stateStack_.pop();
	stateStack_.push(FADE_STATUS::eStandby);

	callbacks_.clear();
}

void FadePanel::Update(float deltaTime)
{
	// �ψْ��͏ȗ�
	if (!IsAction()) return;
	  
	// �f�B���C�ȗ�
	if (delayTime_ > 0.0f)
	{
		delayTime_ -= deltaTime;
		delayTime_  = MathHelper::Max(0.0f, delayTime_);
		return;
	}

	switch (stateStack_.top())
	{
	// �t�F�[�h�C��
	case FADE_STATUS::eFadeIn:	FadeInUpdate(deltaTime);	break;
	case FADE_STATUS::eFadeOut:	FadeOutUpdate(deltaTime);	break;
	}

	// �A���t�@�N�����v
	alpha_ = MathHelper::Clamp(alpha_, 0.0f, maxAlpha_);
}

void FadePanel::Draw()const
{
	switch (color_)
	{
	case FadePanel::White:
		Sprite::GetInstance().Draw(SPRITE_ID::WHITE_SCREEN_SPRITE, Vector2::Zero, Vector2::Zero, alpha_, SCALE, 0.0f, false, false);
		break;
	case FadePanel::Black:
		Sprite::GetInstance().Draw(SPRITE_ID::BLACK_SCREEN_SPRITE, Vector2::Zero, Vector2::Zero, alpha_, SCALE, 0.0f, false, false);
		break;
	}
}

// �t�F�[�h�C���J�n
void FadePanel::FadeIn()
{
	stateStack_.push(FADE_STATUS::eFadeIn);
	actionTime_ = GetInTime();
}

// �t�F�[�h�A�E�g�J�n
void FadePanel::FadeOut(ColorType type, float maxAlpha)
{
	stateStack_.push(FADE_STATUS::eFadeOut);
	color_	= type;
	maxAlpha_	= maxAlpha;
	actionTime_ = GetOutTime();
}

// �ψْ����H
bool FadePanel::IsAction() const
{
	return stateStack_.top() != FADE_STATUS::eStandby;
}

// ��ʂ����܂��Ă��邩�H
bool FadePanel::IsFillScreen() const
{
	return alpha_ >= maxAlpha_;
}

// ��ʂ��������H
bool FadePanel::IsClearScreen() const
{
	return alpha_ <= 0.0f;
}

// �t�F�[�h�C���^�C���̎擾
float FadePanel::GetInTime() const
{
	return inTime_;
}

// �t�F�[�h�C���^�C���̐ݒ�
void FadePanel::SetInTime(const float sec, const float delay)
{
	inTime_	   = sec;
	delayTime_ = delay;
}

// �t�F�[�h�A�E�g�^�C���̎擾
float FadePanel::GetOutTime() const
{
	return outTime_;
}

// �t�F�[�h�A�E�g�^�C���̐ݒ�
void FadePanel::SetOutTime(const float sec, const float delay)
{
	outTime_   = sec;
	delayTime_ = delay;
}

// �f�B���C�^�C���擾
float FadePanel::GetDelayTime() const
{
	return delayTime_;
}

void FadePanel::AddCollBack(std::function<void()> collback)
{
	callbacks_.push_back(collback);
}

int FadePanel::Count() const
{
	return stateStack_.size();
}

// �t�F�[�h�C���A�b�v�f�[�g
void FadePanel::FadeInUpdate(float deltaTime)
{
	alpha_ -= (deltaTime / actionTime_) * (maxAlpha_ / 1.0f);

	// �I������
	if (IsClearScreen())
	{
		stateStack_.pop();
		
		// �R�[���o�b�N�Ăяo��
		auto tempCallbacks = callbacks_;
		callbacks_.clear();
		for (auto& callback : tempCallbacks)
			callback();
		tempCallbacks.clear();
	}
}

// �t�F�[�h�A�E�g�A�b�v�f�[�g
void FadePanel::FadeOutUpdate(float deltaTime)
{
	alpha_ += (deltaTime / actionTime_) * (maxAlpha_ / 1.0f);

	// �I������
	if (IsFillScreen())
	{
		stateStack_.pop();

		// �R�[���o�b�N�Ăяo��
		auto tempCallbacks = callbacks_;
		callbacks_.clear();
		for (auto& callback : tempCallbacks)
			callback();
		tempCallbacks.clear();
	}
}
