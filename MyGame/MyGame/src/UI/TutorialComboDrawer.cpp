#include "TutorialComboDrawer.h"
#include"../Graphic/Sprite.h"
#include"ComboSupportUI.h"

TutorialComboDrawer::TutorialComboDrawer() :drawFunc_([](const std::vector<StepParts>& stepUIs_) {})
{
}

void TutorialComboDrawer::init(DrawComboType type)
{
	switch (type)
	{
	case TutorialComboDrawer::DrawComboType::Burst:
		drawFunc_ = [](const auto& stepUIs_) {ComboSupportUI::drawComboBurst(stepUIs_); };
		id_ = SPRITE_ID::COMBO_BURST_SPRITE;
		break;
	case TutorialComboDrawer::DrawComboType::PointUp:
		drawFunc_ = [](const auto& stepUIs_) {ComboSupportUI::drawComboPointUp(stepUIs_); };
		id_ = SPRITE_ID::COMBO_POINTUP_SPRITE;
		break;
	default:
		break;
	}
}

void TutorialComboDrawer::draw() const
{
	drawFunc_(stepUIs_);
	
	for (auto& s : stepUIs_) {
		s.draw();
	}
	Sprite::GetInstance().Draw(id_, Vector2{ 100.0f,340.0f }, alpha_);

}
