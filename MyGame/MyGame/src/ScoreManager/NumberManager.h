#pragma once
#include "../Math/Math.h"
#include"../Graphic/FontManager.h"

class NumberManager {
private:
	NumberManager()=default;
public:
	static NumberManager &GetInstance() {
		static NumberManager n;
		return n;
	}
	//数値描画(ポジション、数値、最大表示桁数,字間)
	void DrawNumber(Vector2& position,int score,int digit, int space);
	//数値描画(ポジション、数値)
	void DrawNumber(Vector2& position, int score);

	//処理
	void draw(Vector2& position, int score,int digit ,char fill = '0');
	void draw(Vector2& position,int score,char fill = '0');
	void draw(const Vector2& position, int score);
	void draw(const Vector2& positon, const std::string& score);

	void drawT(const Vector2& position, int score, int digit);
};