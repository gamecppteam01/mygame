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
	/// 数値描画フォント(座標、数値)
	///</summary>
	void DrawNumber(const Vector2& position,const int number);
	///<summary>
	/// 数値描画フォント(座標、数値、色)(1:白,2:赤,3:緑,4:青)
	///</summary>
	void DrawNumber(const Vector2& position, const int number,int colornumebr, FONT_ID id=FONT_ID::DEFAULT_FONT);
	///<summary>
	/// 数値描画テクスチャ(スプライトID、座標、数値、数字一つのサイズ、表示サイズ)
	///</summary>
	void DrawNumberTexture(const SPRITE_ID &id, const Vector2& position, int number, const Vector2& size, const Vector2& scale);
	///<summary>
	/// 数値描画テクスチャ(スプライトID、座標、数値、数字一つのサイズ、表示サイズ)
	/// 9以下で真ん中に表示されるようになります
	///</summary>
	void DrawNumberTexture2(const SPRITE_ID &id, const Vector2& position, int number, const Vector2& size, const Vector2& scale);
	///<summary>
	/// 数値描画フォント(座標、数値、最大桁数)
	///</summary>
	void DrawNumber_digit(const Vector2& position,  int number, int digit);
private:
	int C{ 0 };
};