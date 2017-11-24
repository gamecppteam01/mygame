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
	//数値描画フォント(ポジション、数値)
	void DrawNumber(const Vector2& position,const int number);
	//数値描画フォント(ポジション、数値、色)(1:白,2:赤,3:緑,4:青)
	void DrawNumber(const Vector2& position, const int number,int colornumebr);
	//数値描画テクスチャ(テクスチャID、ポジション、数値、画像サイズ、表示サイズ)
	void DrawNumberTexture( const Vector2& position, int number, const Vector2& size, const Vector2& scale);
	//数値描画テクスチャ(テクスチャID、ポジション、数値、画像サイズ、表示サイズ)
	//赤色の数字(後からＩＤで変えれるように変更します)
	void DrawNumberTexture2(const Vector2& position, int number, const Vector2& size, const Vector2& scale);


	void drawT(const Vector2& position, int number, int digit);
private:
	int C{ 0 };
};