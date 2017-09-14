#pragma once
#include "../Define.h"
#include "../math/Vector2.h"
#include <stack>
#include <functional>
#include <vector>

// �t�F�[�h�N���X
class FadePanel
{
public:
	enum ColorType
	{
		White,
		Black
	};
	enum FADE_STATUS
	{
		eStandby = 0,	// ���s�҂�
		eFadeIn	 = 1,	// �t�F�[�h�C��
		eFadeOut = 2		// �t�F�[�h�A�E�g
	};


private:
	// �R���X�g���N�^
	FadePanel();
	// �f�X�g���N�^
	~FadePanel();

	/* �R�s�[�֎~ */
	FadePanel(const FadePanel& other) = delete;
	FadePanel & operator = (const FadePanel& other) = delete;


public:
	static FadePanel &GetInstance(){
		static FadePanel f;
		return f;
	}

	// ������
	void Initialize();
	// �X�V
	void Update(float deltaTime);
	// �`��
	void Draw() const;
	// �t�F�[�h�C��
	void FadeIn();
	// �t�F�[�h�A�E�g
	void FadeOut(ColorType type = ColorType::Black, float maxAlpha = 1.0f);
	// �ψْ����H
	bool IsAction() const;
	// ��ʂ����܂��Ă��邩�H
	bool IsFillScreen() const;
	// ��ʂ��������H
	bool IsClearScreen() const;

	// �t�F�[�h�C���^�C���̎擾
	float GetInTime() const;
	// �t�F�[�h�C���^�C���̐ݒ�
	void  SetInTime(const float sec, const float delay = 0.0f);
	// �t�F�[�h�A�E�g�^�C���̎擾
	float GetOutTime() const;
	// �t�F�[�h�A�E�g�^�C���̐ݒ�
	void  SetOutTime(const float sec, const float delay = 0.0f);

	// �f�B���C�^�C���擾
	float GetDelayTime() const;

	// �R�[���o�b�N�֓o�^(�����_�Ŋ֐��ǉ�)
	void AddCollBack(std::function<void()> collback);

	int Count() const;

private:
	// �t�F�[�h�C���A�b�v�f�[�g
	void FadeInUpdate(float deltaTime);
	// �t�F�[�h�A�E�g�A�b�v�f�[�g
	void FadeOutUpdate(float deltaTime);

private:
	// ���\�[�X�T�C�Y
	const Vector2 RES_SIZE = Vector2(800, 600);
	// �X�N���[���T�C�Y
	const Vector2 SCALE	   = Vector2((float)WINDOW_WIDTH / RES_SIZE.x, (float)WINDOW_HEIGHT / RES_SIZE.y);

	// �X�e�[�g�X�^�b�N
	std::stack<FADE_STATUS>	stateStack_;

	// �R�[���o�b�N�֐��錾
	using CallBack = std::function<void()>;
	// �R�[���o�b�N�x�N�^�[
	std::vector<CallBack>	callbacks_;

	// �^�C�v
	ColorType	color_;
	// �A���t�@�l
	float		alpha_;
	// �A���t�@�ő�l
	float		maxAlpha_;
	// �ψَ���
	float		actionTime_;
	// �t�F�[�h�C���^�C��
	float		inTime_;
	// �t�F�[�h�A�E�g�^�C��
	float		outTime_;
	// �f�B���C�^�C��
	float		delayTime_;
};