#pragma once
#include "../Math/Math.h"
#include "../game/ID.h"

class NumberManager {
private:
	NumberManager()=default;
public:
	static NumberManager &GetInstance() {
		static NumberManager n;
		return n;
	}
	///<summary>
	/// ���l�`��t�H���g(���W�A���l)
	///</summary>
	void DrawNumber(const Vector2& position,const int number);
	///<summary>
	/// ���l�`��t�H���g(���W�A���l�A�F)(1:��,2:��,3:��,4:��)
	///</summary>
	void DrawNumber(const Vector2& position, const int number,int colornumebr, FONT_ID id=FONT_ID::DEFAULT_FONT);
	///<summary>
	/// ���l�`��e�N�X�`��(�X�v���C�gID�A���W�A���l�A������̃T�C�Y�A�\���T�C�Y)
	///</summary>
	void DrawNumberTexture(const SPRITE_ID &id, const Vector2& position, int number, const Vector2& size, const Vector2& scale);
	///<summary>
	/// ���l�`��e�N�X�`��(�X�v���C�gID�A���W�A���l�A������̃T�C�Y�A�\���T�C�Y)
	/// 9�ȉ��Ő^�񒆂ɕ\�������悤�ɂȂ�܂�
	///</summary>
	void DrawNumberTexture2(const SPRITE_ID &id, const Vector2& position, int number, const Vector2& size, const Vector2& scale);
	///<summary>
	/// ���l�`��t�H���g(���W�A���l�A�ő包��)
	///</summary>
	void DrawNumber_digit(const Vector2& position,  int number, int digit);
private:
	int C{ 0 };
};