#pragma once

// �}�X�w���p�[�N���X
class MathHelper
{
public:
	// �΂̒l��\���܂��B
	static const float Pi;

	// ������n���A��Βl��Ԃ�
	static int Abs(int value);
	// ������n���A��Βl��Ԃ�
	static float Abs(float value);
	// �Q�̐����l�̍��̐�Βl���v�Z���܂�
	static int Distance(int n1, int n2);
	// �Q�̎����l�̍��̐�Βl���v�Z���܂�
	static float Distance(float n1, float n2);
	// �Q�̐�����n���A�������ق���Ԃ�
	static int Min(int value1, int value2);
	// �Q�̎�����n���A�������ق���Ԃ�
	static float Min(float value1, float value2);
	// �Q�̐�����n���A�傫���ق���Ԃ�
	static int Max(int value1, int value2);
	// �Q�̎�����n���A�傫���ق���Ԃ�
	static float Max(float value1, float value2);
	// �����̕��������߂�
	static int Sign(int value);
	// �����̕��������߂�
	static int Sign(float value);
	// �����̕�������Ԃ�
	static float Sqrt(int value);
	// �����̕�������Ԃ�
	static float Sqrt(float value);

	// �����l���w�肳�ꂽ�͈͓��ɐ������܂�
	static int Clamp(int value, int min, int max);
	// �����l���w�肳�ꂽ�͈͓��ɐ������܂�
	static float Clamp(float value, float min, float max);
	// 2�̒l�̊Ԃ���`��Ԃ��܂�
	static float Lerp(float value1, float value2, float amount);

	// ���W�A����x�ɕϊ����܂��B
	static float ToDegrees(float radians);
	// �x�����W�A���ɕϊ����܂��B
	static float ToRadians(float degree);
	// �T�C���i�O�`�R�U�O�j
	static float Sin(float degree);
	// �R�T�C���i�O�`�R�U�O�j
	static float Cos(float degree);
	// �^���W�F���g�i�O�`�R�U�O�j
	static float Tan(float degree);
	// �t�T�C��
	static float ASin(float s);
	// �t�R�T�C��
	static float ACos(float c);
	// �t�^���W�F���g
	static float ATan(float y, float x);

	// �����l���m�̗]����Z�o
	static int Mod(int value1, int value2);
	// �����l���m�̗]����Z�o
	static float Mod(float value1, float value2);

	// �����ׂ̂����Ԃ� (x��y��)
	static int Pow(int x, int y);
	// �����ׂ̂����Ԃ� (x��y��)
	static float Pow(float x, float y);
};