#ifndef COLOR_H_
#define COLOR_H_

// �J���[
struct Color {
	float	r;	// ��
	float	g;	// ��
	float	b;	// ��
	float	a;	// �A���t�@

	// �R���X�g���N�^
	Color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
	// 2�̃J���[�Ԃ̐��`��Ԃ��s���܂�
	static Color Lerp(const Color& value1, const Color& value2, float amount);
	// ��v����e�����y�A�̍ł��Ⴂ�l���܂ރJ���[��Ԃ��܂�
	static Color Min(const Color& value1, const Color& value2);
	// ��v����e�����y�A�̍ł������l���܂ރJ���[��Ԃ��܂�
	static Color Max(const Color& value1, const Color& value2);
	//	�l���w�肳�ꂽ�͈͓��ɐ������܂�
	static Color Clamp(const Color& value1, const Color& min = Color(0.0f, 0.0f, 0.0f, 0.0f), const Color& max = Color(1.0f, 1.0f, 1.0f, 1.0f));

	// �萔
	static const Color Black;			// Color(0, 0, 0, 1)
	static const Color White;			// Color(1, 1, 1, 1)
};

// ������Z�q�I�[�o�[���[�h
Color& operator += (Color& c1, const Color& c2);
Color& operator -= (Color& c1, const Color& c2);
Color& operator *= (Color& c1, const Color& c2);
Color& operator *= (Color& c, float s);
Color& operator /= (Color& c, float s);

// �Q�����Z�q�I�[�o�[���[�h
Color operator + (Color c1, const Color& c2);
Color operator - (Color c1, const Color& c2);
Color operator * (Color c1, const Color& c2);
Color operator * (Color c, float s);
Color operator * (float s, Color c);
Color operator / (Color c, float s);

#endif

// end of file
