#include "ComboSupportUI.h"
#include"StepParts.h"
#include"../Graphic/Sprite.h"

static const float slideSize{ 200.0f };

void ComboSupportUI::drawCombo(const std::vector<StepParts>& stepUIs_)
{
	if (stepUIs_.empty())return;//ãÛÇ»ÇÁèIÇÌÇË
	float alpha = stepUIs_.front().getAlpha()*0.5f;
	if (stepUIs_.front().getDrawType() == SPRITE_ID::QUATER_SPRITE) {
		Vector2 pos = stepUIs_.front().getPos() + Vector2{ slideSize ,0.0f };
		Sprite::GetInstance().Draw(SPRITE_ID::QUATER_SPRITE, pos, alpha);
		pos += Vector2{ slideSize ,0.0f };
		Sprite::GetInstance().Draw(SPRITE_ID::TURN_SPRITE, pos, alpha);

	}
	else if (stepUIs_.front().getDrawType() == SPRITE_ID::TURN_SPRITE) {
		Vector2 pos = stepUIs_.front().getPos() + Vector2{ slideSize ,0.0f };
		Sprite::GetInstance().Draw(SPRITE_ID::QUATER_SPRITE, pos, alpha);
		pos += Vector2{ slideSize ,0.0f };
		Sprite::GetInstance().Draw(SPRITE_ID::TURN_SPRITE, pos, alpha);
	}
}
