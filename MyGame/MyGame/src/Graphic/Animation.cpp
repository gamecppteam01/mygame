#include "Animation.h"

#include <math.h>

static const float ANIM_BLEND_SPEED = 0.1f;
//static const float PLAY_ANIM_SPEED = 0.8f;

// �R���X�g���N�^
Animation::Animation(const unsigned int &modelHandle_) :
	mModelHandle(modelHandle_), mAnimSpeed(1.0f), mAnimBlendRate(1.0f), mCurrAnim({-1, 0}), mPrevAnim({ -1, 0 }), mID(-1){

}

// �X�V����
void Animation::update(float deltaTime){
	process();
}

// �X�V�̒��g
void Animation::process(){
	float AnimTotalTime;		// �Đ����Ă���A�j���[�V�����̑�����

	// �u�����h�����P�ȉ��̏ꍇ�͂P�ɋ߂Â���
	if (mAnimBlendRate < 1.0f)
	{
		mAnimBlendRate += ANIM_BLEND_SPEED;
		if (mAnimBlendRate > 1.0f)
		{
			mAnimBlendRate = 1.0f;
		}
	}

	// �Đ����Ă���A�j���[�V�����P�̏���
	if (mCurrAnim.mID != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾
		AnimTotalTime = MV1GetAttachAnimTotalTime(mModelHandle, mCurrAnim.mID);

		// �Đ����Ԃ�i�߂�
		mCurrAnim.mCount += mAnimSpeed;

		// �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
		if (mCurrAnim.mCount >= AnimTotalTime)
		{
			mCurrAnim.mCount = fmodf(mCurrAnim.mCount, AnimTotalTime);
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(mModelHandle, mCurrAnim.mID, mCurrAnim.mCount);

		// �A�j���[�V�����P�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(mModelHandle, mCurrAnim.mID, mAnimBlendRate);
	}

	// �Đ����Ă���A�j���[�V�����Q�̏���
	if (mPrevAnim.mID != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾
		AnimTotalTime = MV1GetAttachAnimTotalTime(mModelHandle, mPrevAnim.mID);

		// �Đ����Ԃ�i�߂�
		mPrevAnim.mCount += mAnimSpeed;

		// �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
		if (mPrevAnim.mCount > AnimTotalTime)
		{
			mPrevAnim.mCount = fmodf(mPrevAnim.mCount, AnimTotalTime);
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(mModelHandle, mPrevAnim.mID, mPrevAnim.mCount);

		// �A�j���[�V�����Q�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(mModelHandle, mPrevAnim.mID, 1.0f - mAnimBlendRate);
	}
}

// �A�j���[�V�����̕ύX
void Animation::changeAnim(int id, float speed){
	mAnimSpeed = speed;
	if (mID == id)return;
	mID = id;
	// �Đ����̃��[�V�����Q���L����������f�^�b�`����
	if (mPrevAnim.mID != -1){
		MV1DetachAnim(mModelHandle, mPrevAnim.mID);
		mPrevAnim.mID = -1;
	}

	// ���܂ōĐ����̃��[�V�����P���������̂̏����Q�Ɉړ�����
	mPrevAnim = mCurrAnim;

	// �V���Ɏw��̃��[�V���������f���ɃA�^�b�`���āA�A�^�b�`�ԍ���ۑ�����
	mCurrAnim.mID = MV1AttachAnim(mModelHandle, id);
	mCurrAnim.mCount = 0.0f;

	// �u�����h���͍Đ����̃��[�V�����Q���L���ł͂Ȃ��ꍇ�͂P�D�O��( �Đ����̃��[�V�����P���P�O�O���̏�� )�ɂ���
	mAnimBlendRate = mPrevAnim.mID == -1 ? 1.0f : 0.0f;
}

// �A�j���[�V�������I���������ǂ���
bool Animation::isAnimEnd(){
	return 	mCurrAnim.mCount >= animTime() - 1;
}

// �Đ����̃A�j���[�V�����̍Đ�����
float Animation::animTime(){
	return MV1GetAttachAnimTotalTime(mModelHandle, mCurrAnim.mID);
}
