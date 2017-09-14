#pragma once

#include "DxLib.h"
#include <string>

// ���f���̃A�j���[�V�����N���X
class Animation {
public:
	// �A�j���[�V�����p�����[�^
	struct AnimParams{
		int mID;
		float mCount;
	};
	// �R���X�g���N�^
	explicit Animation(const unsigned int &modelHandle_);
	// �X�V����
	void update(float deltaTime);
	// �X�V�̒��g
	void process();
	// �A�j���[�V�����̕ύX
	void changeAnim(int id, float speed);
	// �A�j���[�V�������I���������ǂ���
	bool isAnimEnd();
	// �Đ����̃A�j���[�V�����̍Đ�����
	float animTime();
private:
	// ���f���n���h��
	unsigned int mModelHandle;
	// �A�j���[�V�������x
	float mAnimSpeed;
	// �A�j���[�V�����u�����h��
	float mAnimBlendRate;
	// ���݂̃A�j���[�V�����̃p�����[�^
	AnimParams mCurrAnim;
	// �O��̃A�j���[�V�����̃p�����[�^
	AnimParams mPrevAnim;
	// ���݂̃A�j���[�V������ID
	int mID;
};