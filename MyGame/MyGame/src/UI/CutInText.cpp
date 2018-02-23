#include "CutInText.h"
#include"../DataManager/DataManager.h"

const std::vector<FONT_ID> CutInText::fontIDs{
	FONT_ID::CUTIN_10_FONT,
	FONT_ID::CUTIN_9_FONT,
	FONT_ID::CUTIN_8_FONT,
	FONT_ID::CUTIN_7_FONT,
	FONT_ID::CUTIN_6_FONT,
	FONT_ID::CUTIN_UNDER_5_FONT,

	FONT_ID::CUTIN_SMALL_10_FONT,
	FONT_ID::CUTIN_SMALL_9_FONT,
	FONT_ID::CUTIN_SMALL_8_FONT,
	FONT_ID::CUTIN_SMALL_7_FONT,
	FONT_ID::CUTIN_SMALL_6_FONT,
	FONT_ID::CUTIN_SMALL_UNDER_5_FONT,

};
const std::vector<FONT_ID> CutInText::rankIDs{

	FONT_ID::CUTIN_RANK_10_FONT,
	FONT_ID::CUTIN_RANK_9_FONT,
	FONT_ID::CUTIN_RANK_8_FONT,
	FONT_ID::CUTIN_RANK_7_FONT,
	FONT_ID::CUTIN_RANK_6_FONT,
	FONT_ID::CUTIN_RANK_UNDER_5_FONT,
};

void CutInText::Draw(const Vector2 & position, const Vector2 & origin, const Vector2 & scale) {
	Sprite::GetInstance().Draw(SPRITE_ID::RANK_PLAYER_SPRITE, position, origin, scale);
	std::string text{ "" };
	auto name = DataManager::GetInstance().getName();
	int frontspaceSize = 0;
	int backspaceSize = 2;
	int length = name.menSize + name.womenSize;

	FONT_ID type = CUTIN_UNDER_5_FONT;
	if (length >= 5) {
		type = fontIDs[maxNameSize - length];

	}
	else if (length == 4) {
		frontspaceSize = 3;
		backspaceSize = 2;
	}
	else if (length == 3) {
		frontspaceSize = 5;
		backspaceSize = 2;
	}
	else if (length == 2) {
		frontspaceSize = 7;
		backspaceSize = 3;
	}

	for (int i = 0; i < frontspaceSize; i++) {
		text += " ";
	}
	text += name.men_name;
	text += "&";
	text += name.women_name;
	for (int i = 0; i < backspaceSize; i++) {
		text += " ";
	}
	text += "ペア";


	SetDrawBright(0, 0, 0);
	FontManager::GetInstance().DrawTextApplyFont(position.x + 23.0f + 7.0f, position.y + 27.0f + 7.0f, GetColor(255, 255, 255), type, text);
	SetDrawBright(255, 255, 255);
	FontManager::GetInstance().DrawTextApplyFont(position.x + 23.0f, position.y + 27.0f, GetColor(255, 255, 255), type, text);

}

void CutInText::DrawMin(const Vector2 & position) {
	float rate = 0.4f;
	Sprite::GetInstance().Draw(SPRITE_ID::RANK_PLAYER_SPRITE, position, Vector2::Zero, Vector2::One*rate, 0.0f);
	std::string text{ "" };
	auto name = DataManager::GetInstance().getName();
	int frontspaceSize = 0;
	int backspaceSize = 2;
	int length = name.menSize + name.womenSize;

	FONT_ID type = CUTIN_SMALL_UNDER_5_FONT;
	if (length >= 5) {
		type = fontIDs[maxNameSize - length + (fontIDs.size() / 2)];

	}
	else if (length == 4) {
		frontspaceSize = 3;
		backspaceSize = 2;
	}
	else if (length == 3) {
		frontspaceSize = 5;
		backspaceSize = 2;
	}
	else if (length == 2) {
		frontspaceSize = 7;
		backspaceSize = 3;
	}

	for (int i = 0; i < frontspaceSize; i++) {
		text += " ";
	}
	text += name.men_name;
	text += "&";
	text += name.women_name;
	for (int i = 0; i < backspaceSize; i++) {
		text += " ";
	}
	text += "ペア";


	SetDrawBright(0, 0, 0);
	float shadowPos = 7.0f;
	FontManager::GetInstance().DrawTextApplyFont(position.x + (23.0f + shadowPos)*rate, position.y + (27.0f + shadowPos)* rate, GetColor(255, 255, 255), type, text);
	SetDrawBright(255, 255, 255);
	FontManager::GetInstance().DrawTextApplyFont(position.x + (23.0f * rate), position.y + (27.0f * rate), GetColor(255, 255, 255), type, text);

}

void CutInText::DrawRank(const Vector2 & position) {
	float rate = 0.2f;
	auto origin = Vector2(Sprite::GetInstance().GetSize(SPRITE_ID::RANK_PLAYER_SPRITE))*0.2f / 2;
	Sprite::GetInstance().Draw(SPRITE_ID::RANK_PLAYER_SPRITE, position, origin, Vector2::One*rate, 0.0f);
	std::string text{ "" };
	auto name = DataManager::GetInstance().getName();
	int frontspaceSize = 0;
	int backspaceSize = 2;
	int length = name.menSize + name.womenSize;

	FONT_ID type = CUTIN_RANK_UNDER_5_FONT;
	if (length >= 5) {
		type = rankIDs[maxNameSize - length];

	}
	else if (length == 4) {
		frontspaceSize = 3;
		backspaceSize = 2;
	}
	else if (length == 3) {
		frontspaceSize = 5;
		backspaceSize = 2;
	}
	else if (length == 2) {
		frontspaceSize = 7;
		backspaceSize = 3;
	}

	for (int i = 0; i < frontspaceSize; i++) {
		text += " ";
	}
	text += name.men_name;
	text += "&";
	text += name.women_name;
	for (int i = 0; i < backspaceSize; i++) {
		text += " ";
	}
	text += "ペア";


	SetDrawBright(0, 0, 0);
	float shadowPos = 7.0f;
	Vector2 slidepos{ 80.f,15.f };
	FontManager::GetInstance().DrawTextApplyFont(position.x- origin.x+ slidepos.x + (23.0f + shadowPos)*rate, position.y- origin.y+ slidepos.y + (27.0f + shadowPos)* rate, GetColor(255, 255, 255), type, text);
	SetDrawBright(255, 255, 255);
	FontManager::GetInstance().DrawTextApplyFont(position.x- origin.x+ slidepos.x + (23.0f * rate), position.y- origin.y+ slidepos.y + (27.0f * rate), GetColor(255, 255, 255), type, text);

}
