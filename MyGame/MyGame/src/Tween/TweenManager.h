/*
ColoTween���p����
Unity��LeanTween�����f���ɍ쐬

***	�֐����� ***
Update / Remove			: ���t���[���K���X�V�����ꏊ�ŌĂяo��
Clear					: �V�[���̐؂�ւ������ɌĂяo��
Count					: ���s����Tween��
Play					: �o�^����Ă���Tween���Đ�
Stop / StopAll			: �o�^����Ă���Tween���~
SetLoop~				: ���ȍ~Add����tween�̃I�v�V�����錾�i�I�v�V���������������Ƃ���ResetOption�j
ResetOption				: �I�v�V�������f�t�H���g�ɖ߂�
Add						: Tween�ǉ�
Loop					: ����LoopTween�ǉ�			�icallback�Ăяo����1���[�v�� / �K���Ăяo�����̃f�X�g���N�^�Ȃ�� Cancel ���Ăԁj
LoopOnce				: ��x������LoopTween�ǉ�	�icallback�Ăяo����1���[�v���j
LoopCount				: �w�萔LoopTween�ǉ�		�icallback�Ăяo����1���[�v���j
LoopPingPong			: ����LoopTween�ǉ�			�icallback�Ăяo����1���[�v�� / �K���Ăяo�����̃f�X�g���N�^�Ȃ�� Cancel ���Ă� / �񐔎w�������ꍇ�͐�s��SetLoopCount���g���j
Delay					: �x���֐����s
Cancel / DelayCancel	: �o�^����Ă���Tween���L�����Z�� �i���������ꍇtrue��Ԃ��j

*** �������� ***
deltaTime				: �t���[���ԃ^�C��
value*					: �ϓ��l�i�[�|�C���^
type					: easing�^�C�v
b						: �J�n�l�ifrom�j
c						: �ړ��ʁito - from�j
from*					: �J�n�l / �ϓ��l�i�[�|�C���^
to						: �I���l�ib + c�j
d						: ���쎞��
callback				: �R�[���o�b�N
s						: EaseBack���̔�яo��� s > 1
delay					: �x������
count					: ���[�v��
debug*					: �x���m�F �� �F���n���h�� �i�l��1�Ŋ֐����s�j

*** �g�p���� ***
callback�ɂ��̃N���X��Clear���ĂԂ��̂����Ă͂����Ȃ�
������
if���Ńt���O���Ď����Ă���
�Ecallback���Ńt���O�𗧂Ă�
��
�E�t���O���m�F��Clear���Ă�
��
�E���������Ńt���O��܂�
*/

#pragma once
#include "TweenObject.h"
#include "../math/Easing.h"
#include <list>
#include <unordered_map>
#include <functional>
#include <memory>

struct Vector2;
struct Vector3;

enum EaseType
{
	Linear,
	EaseInQuad,
	EaseOutQuad,
	EaseInOutQuad,
	EaseInCubic,
	EaseOutCubic,
	EaseInOutCubic,
	EaseInQuart,
	EaseOutQuart,
	EaseInOutQuart,
	EaseInQuint,
	EaseOutQuint,
	EaseInOutQuint,
	EaseInSine,
	EaseOutSine,
	EaseInOutSine,
	EaseInExpo,
	EaseOutExpo,
	EaseInOutExpo,
	EaseInCirc,
	EaseOutCirc,
	EaseInOutCirc,
	EaseInElastic,
	EaseOutElastic,
	EaseInOutElastic,
	EaseInBack,
	EaseOutBack,
	EaseInOutBack,
	EaseInBounce,
	EaseOutBounce,
	EaseInOutBounce
};

// �c�C�[���}�l�[�W���[�N���X
class TweenManager
{
private:
	// �R���X�g���N�^
	TweenManager();
	// �f�X�g���N�^
	~TweenManager();

	/* �R�s�[�֎~ */
	TweenManager(const TweenManager&) = delete;
	TweenManager& operator =(const TweenManager&) = delete;

public:
	static TweenManager &GetInstance() {
		static TweenManager t;
		return t;
	}

	// ������
	void Initialize();
	// �X�V
	void Update(const float deltaTime);
	// �폜
	void Remove();
	// �N���A
	void Clear();
	// ���s����Tween��
	int Count() const;

	/*** ��{ ***/
	// �Đ� /* scale : �Đ��{�� */
	void Play(float scale = 1.0f);
	// ��~�i�ϓ��l�i�[�|�C���^�w��j
	void Stop(const float* value);
	// ��~�i�ϓ��l�i�[�|�C���^�w��j
	void Stop(const Vector2* value);
	// ��~�i�ϓ��l�i�[�|�C���^�w��j
	void Stop(const Vector3* value);
	// �S��~
	void StopAll();

	/*** ��s�I�v�V�����錾 ***/
	// ���[�v���w�� (0 = �������[�v)
	void SetLoopCount(const int count = 1);
	// ���[�v�^�C�v�w��
	void SetLoopType(const TweenObject::UpdateType type = TweenObject::Common);
	// �I�v�V�������Z�b�g
	void ResetOption();

	/*** �ǉ��֘A ***/
	// �ǉ� /* *value : �ϓ��l�i�[�|�C���^ / type : Easetype / b : �J�n�l / c : �ړ��� / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void Add(float* value, const EaseType& type, const float b, const float c, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// �ǉ� /* *value : �ϓ��l�i�[�|�C���^ / type : Easetype / b : �J�n�l / c : �ړ��� / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void Add(Vector2* value, const EaseType& type, const Vector2& b, const Vector2& c, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// �ǉ� /* *value : �ϓ��l�i�[�|�C���^ / type : Easetype / b : �J�n�l / c : �ړ��� / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void Add(Vector3* value, const EaseType& type, const Vector3& b, const Vector3& c, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// �ǉ� /* type : Easetype / *from : �J�n�l�|�C���^ / to : �I���l / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void Add(const EaseType& type, float* from, const float to, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// �ǉ� /* type : Easetype / *from : �J�n�l�|�C���^ / to : �I���l / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void Add(const EaseType& type, Vector2* from, const Vector2& to, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// �ǉ� /* type : Easetype / *from : �J�n�l�|�C���^ / to : �I���l / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void Add(const EaseType& type, Vector3* from, const Vector3& to, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);

	/*** ���[�v�֘A ***/
	// ���[�v /* *value : �ϓ��l�i�[�|�C���^ / type : Easetype / b : �J�n�l / c : �ړ��� / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void Loop(float* value, const EaseType& type, const float b, const float c, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���[�v /* *value : �ϓ��l�i�[�|�C���^ / type : Easetype / b : �J�n�l / c : �ړ��� / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void Loop(Vector2* value, const EaseType& type, const Vector2& b, const Vector2& c, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���[�v /* *value : �ϓ��l�i�[�|�C���^ / type : Easetype / b : �J�n�l / c : �ړ��� / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void Loop(Vector3* value, const EaseType& type, const Vector3& b, const Vector3& c, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���[�v /* type : Easetype / *from : �J�n�l�|�C���^ / to : �I���l / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void Loop(const EaseType& type, float* from, const float to, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���[�v /* type : Easetype / *from : �J�n�l�|�C���^ / to : �I���l / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void Loop(const EaseType& type, Vector2* from, const Vector2& to, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���[�v /* type : Easetype / *from : �J�n�l�|�C���^ / to : �I���l / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void Loop(const EaseType& type, Vector3* from, const Vector3& to, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���[�v�i��x�̂݁j /* *value : �ϓ��l�i�[�|�C���^ / type : Easetype / b : �J�n�l / c : �ړ��� / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void LoopOnce(float* value, const EaseType& type, const float b, const float c, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���[�v�i��x�̂݁j /* *value : �ϓ��l�i�[�|�C���^ / type : Easetype / b : �J�n�l / c : �ړ��� / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void LoopOnce(Vector2* value, const EaseType& type, const Vector2& b, const Vector2& c, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���[�v�i��x�̂݁j /* *value : �ϓ��l�i�[�|�C���^ / type : Easetype / b : �J�n�l / c : �ړ��� / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void LoopOnce(Vector3* value, const EaseType& type, const Vector3& b, const Vector3& c, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���[�v�i��x�̂݁j /* type : Easetype / *from : �J�n�l�|�C���^ / to : �I���l / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void LoopOnce(const EaseType& type, float* from, const float to, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���[�v�i��x�̂݁j /* type : Easetype / *from : �J�n�l�|�C���^ / to : �I���l / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void LoopOnce(const EaseType& type, Vector2* from, const Vector2& to, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���[�v�i��x�̂݁j /* type : Easetype / *from : �J�n�l�|�C���^ / to : �I���l / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void LoopOnce(const EaseType& type, Vector3* from, const Vector3& to, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���[�v�i�w��񐔁j /* *value : �ϓ��l�i�[�|�C���^ / type : Easetype / count : loop�� / b : �J�n�l / c : �ړ��� / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void LoopCount(float* value, const EaseType& type, const int count, const float b, const float c, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���[�v�i�w��񐔁j /* *value : �ϓ��l�i�[�|�C���^ / type : Easetype / count : loop�� / b : �J�n�l / c : �ړ��� / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void LoopCount(Vector2* value, const EaseType& type, const int count, const Vector2& b, const Vector2& c, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���[�v�i�w��񐔁j /* *value : �ϓ��l�i�[�|�C���^ / type : Easetype / count : loop�� / b : �J�n�l / c : �ړ��� / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void LoopCount(Vector3* value, const EaseType& type, const int count, const Vector3& b, const Vector3& c, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���[�v�i�w��񐔁j /* type : Easetype / count : loop�� / *from : �J�n�l�|�C���^ / to : �I���l / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void LoopCount(const EaseType& type, const int count, float* from, const float to, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���[�v�i�w��񐔁j /* type : Easetype / count : loop�� / *from : �J�n�l�|�C���^ / to : �I���l / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void LoopCount(const EaseType& type, const int count, Vector2* from, const Vector2& to, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���[�v�i�w��񐔁j /* type : Easetype / count : loop�� / *from : �J�n�l�|�C���^ / to : �I���l / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void LoopCount(const EaseType& type, const int count, Vector3* from, const Vector3& to, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���ꃋ�[�v�i���p�����K�ǁj /* *value : �ϓ��l�i�[�|�C���^ / type : Easetype / b : �J�n�l / c : �ړ��� / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void LoopPingPong(float* value, const EaseType& type, const float b, const float c, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���ꃋ�[�v�i���p�����K�ǁj /* *value : �ϓ��l�i�[�|�C���^ / type : Easetype / b : �J�n�l / c : �ړ��� / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void LoopPingPong(Vector2* value, const EaseType& type, const Vector2& b, const Vector2& c, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���ꃋ�[�v�i���p�����K�ǁj /* *value : �ϓ��l�i�[�|�C���^ / type : Easetype / b : �J�n�l / c : �ړ��� / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void LoopPingPong(Vector3* value, const EaseType& type, const Vector3& b, const Vector3& c, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���ꃋ�[�v�i���p�����K�ǁj /* type : Easetype / *from : �J�n�l�|�C���^ / to : �I���l / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void LoopPingPong(const EaseType& type, float* from, const float to, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���ꃋ�[�v�i���p�����K�ǁj /* type : Easetype / *from : �J�n�l�|�C���^ / to : �I���l / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void LoopPingPong(const EaseType& type, Vector2* from, const Vector2& to, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);
	// ���ꃋ�[�v�i���p�����K�ǁj /* type : Easetype / *from : �J�n�l�|�C���^ / to : �I���l / d : �I������ / callback : �֐� / s : back�g�p���̕␳�l */
	void LoopPingPong(const EaseType& type, Vector3* from, const Vector3& to, const float d = 1.0f, const std::function<void()>& callback = nullptr, const float s = 1.0f);

	/*** �x�� ***/
	// �x���Ăяo�� /* delay : �x������ / func : �֐� / *debag : �ψڒl�i�[�|�C���^ */
	void Delay(const float delay, const std::function<void()>& func, float* debug = nullptr);

	/*** �L�����Z���֘A ***/
	// �L�����Z�� /* *value : �ϓ��l�i�[�|�C���^ */
	bool Cancel(const float* value);
	// �L�����Z�� /* *value : �ϓ��l�i�[�|�C���^ */
	bool Cancel(const Vector2* value);
	// �L�����Z�� /* *value : �ϓ��l�i�[�|�C���^ */
	bool Cancel(const Vector3* value);
	// �L�����Z�� /* *value : �ϓ��l�i�[�|�C���^ */
	bool DelayCancel(const float* value = nullptr);

private:
	// easing�C���X�^���X
	Easing	ease_;
	// tween�p�V�F�A�h�|�C���^
	using TweenPtr = std::shared_ptr<TweenObject>;
	// tweenlist
	std::list<TweenPtr> tweenList_;
	// �ǉ��ҋ@tweenList
	std::list<TweenPtr> addTweenList_;
	// easing�֐��}�b�v
	std::unordered_map<EaseType,TweenObject::TweenFuncParam>	easeFuncMap_;
	// ���[�v��
	int			loopCount_;
	// �X�V�^�C�v
	TweenObject::UpdateType	updateType_;
};