#pragma once
#include "../Math/Math.h"

class NumberManager {
private:
	NumberManager()=default;
public:
	static NumberManager &GetInstance() {
		static NumberManager n;
		return n;
	}
	//���l�`��t�H���g(�|�W�V�����A���l)
	void DrawNumber(const Vector2& position,const int number);
	//���l�`��t�H���g(�|�W�V�����A���l�A�F)(1:��,2:��,3:��,4:��)
	void DrawNumber(const Vector2& position, const int number,int colornumebr);
	//���l�`��e�N�X�`��(�e�N�X�`��ID�A�|�W�V�����A���l�A�摜�T�C�Y�A�\���T�C�Y)
	void DrawNumberTexture( const Vector2& position, int number, const Vector2& size, const Vector2& scale);
	//���l�`��e�N�X�`��(�e�N�X�`��ID�A�|�W�V�����A���l�A�摜�T�C�Y�A�\���T�C�Y)
	//�ԐF�̐���(�ォ��h�c�ŕς����悤�ɕύX���܂�)
	void DrawNumberTexture2(const Vector2& position, int number, const Vector2& size, const Vector2& scale);


	void drawT(const Vector2& position, int number, int digit);
private:
	int C{ 0 };
};