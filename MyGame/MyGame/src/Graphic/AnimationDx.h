#pragma once

class AnimationDx
{
public:
	// �R���X�g���N�^
	explicit AnimationDx() = default;
	// �f�X�g���N�^
	~AnimationDx() = default;
	// �X�V
	void Update(const float frameTime);
	// �`��
	void Draw() const;
	// �A�j���[�V�����؂�ւ�
	void ChangeAnim(const int motion, const float frame = 0.0f);
	// ���f���n���h���o�^
	void SetHandle(const int& handle);
	// �A�j���[�V�����G���h�t���O
	bool IsAnimEnd() const;
	// ���̃A�j���[�V�����t���[�����󂯎��
	float GetCurrentAnimFrame() const;
	// ���[�V�����̍ŏI�t���[�����󂯎��
	float GetEndAnimFrame(const int motion) const;

private:
	// �R�s�[�R���X�g���N�^
	AnimationDx(const AnimationDx& other) = delete;
	// ������Z�q
	AnimationDx& operator =(const AnimationDx& other) = delete;

private:
	// �u�����h���[�g�^�C��
	const float RATE_TIME = 0.1f;
	// ���f���n���h��
	int		modelHandle_;
	// �����[�V����
	int		motion_;
	// �O���[�V����
	int		prevMotion_;
	// �A�j���[�V�����^�C�}�[
	float	animTimer_;
	// �O�A�j���[�V�����^�C�}�[
	float	prevAnimTimer_;
	// �A�j���[�V�����}�b�N�X�^�C��
	float	maxAnimTime_;
	// �A�j���[�V�����I���t���O
	bool	isAnimEnd_;
	// �u�����h���[�g
	float	rate_;
	// ���A�j���[�V����
	int		anim_;
	// �O�A�j���[�V����
	int		prevAnim_;
};
