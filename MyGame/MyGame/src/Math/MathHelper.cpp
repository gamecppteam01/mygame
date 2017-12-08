#include "MathHelper.h"
#include <cmath>
#include <algorithm>

// �΂̒l��\���܂��B
const float MathHelper::Pi = 3.14159265359f;

// ������n���A��Βl��Ԃ�
int MathHelper::Abs(int value)
{
	return (int)fabsf((float)value);
}

// ������n���A��Βl��Ԃ�
float MathHelper::Abs(float value)
{
	return fabsf(value);
}

// 2�̐����l�̍��̐�Βl���v�Z���܂�
int MathHelper::Distance(int n1, int n2)
{
	return MathHelper::Abs(n1 - n2);
}

// 2�̎����l�̍��̐�Βl���v�Z���܂�
float MathHelper::Distance(float n1, float n2)
{
	return MathHelper::Abs(n1 - n2);
}

// �Q�̐�����n���A�������ق���Ԃ�
int MathHelper::Min(int value1, int value2)
{
	return std::min(value1, value2);
}

// �Q�̎�����n���A�������ق���Ԃ�
float MathHelper::Min(float value1, float value2)
{
	return std::min(value1, value2);
}

// �Q�̐�����n���A�傫���ق���Ԃ�
int MathHelper::Max(int value1, int value2)
{
	return std::max(value1, value2);
}

// �Q�̎�����n���A�傫���ق���Ԃ�
float MathHelper::Max(float value1, float value2)
{
	return std::max(value1, value2);
}

// �����̕��������߂�
int MathHelper::Sign(int value)
{
	return (value > 0) - (value < 0);
}

// �����̕��������߂�
int MathHelper::Sign(float value)
{
	return static_cast<int>((value > 0) - (value < 0));
}

// �����̕�������Ԃ�
float MathHelper::Sqrt(int value)
{
	return sqrtf(static_cast<float>(value));
}

// �����̕�������Ԃ�
float MathHelper::Sqrt(float value)
{
	return sqrtf(value);
}

// �����l���w�肳�ꂽ�͈͓��ɐ������܂�
int MathHelper::Clamp(int value, int min, int max)
{
	return MathHelper::Max(min, MathHelper::Min(value, max));
}

// �����l���w�肳�ꂽ�͈͓��ɐ������܂�
float MathHelper::Clamp(float value, float min, float max)
{
	return MathHelper::Max(min, MathHelper::Min(value, max));
}

// 2�̒l�̊Ԃ���`��Ԃ��܂�
float MathHelper::Lerp(float value1, float value2, float amount)
{
	return (value1 * (1.0f - amount)) + (value2 * amount);
}

float MathHelper::Smoothstep(float edge0, float edge1, float x)
{
	float t = MathHelper::Clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
	return t * t * (3 - 2 * t);
}

// ���W�A����x�ɕϊ����܂��B
float MathHelper::ToDegrees(float radians)
{
	return radians * (180.f / MathHelper::Pi);
}

// �x�����W�A���ɕϊ����܂��B
float MathHelper::ToRadians(float degree)
{
	return degree *  (MathHelper::Pi / 180.0f);
}

// �T�C���i�O�`�R�U�O�j
float MathHelper::Sin(float degree)
{
	return std::sin(ToRadians(degree));
}

// �R�T�C���i�O�`�R�U�O�j
float MathHelper::Cos(float degree)
{
	return std::cos(ToRadians(degree));
}

// �^���W�F���g�i�O�`�R�U�O�j
float MathHelper::Tan(float degree)
{
	return std::tan(ToRadians(degree));
}

// �t�T�C��
float MathHelper::ASin(float s)
{
	return ToDegrees(std::asin(s));
}

// �t�R�T�C��
float MathHelper::ACos(float c)
{
	return ToDegrees(std::acos(c));
}

// �t�^���W�F���g
float MathHelper::ATan(float y, float x)
{
	return ToDegrees(std::atan2(y, x));
}

// �����l���m�̗]����Z�o
int MathHelper::Mod(int value1, int value2)
{
	return (int)fmodf((int)value1, (int)value2);
}

// �����l���m�̗]����Z�o
float MathHelper::Mod(float value1, float value2)
{
	return fmodf(value1, value2);
}

// �����ׂ̂����Ԃ� (x��y��)
int MathHelper::Pow(int x, int y)
{
	return static_cast<int>(powf(x, y));
}

// �����ׂ̂����Ԃ� (x��y��)
float MathHelper::Pow(float x, float y)
{
	return powf(x, y);
}

