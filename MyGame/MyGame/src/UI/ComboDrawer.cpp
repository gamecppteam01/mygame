#include "ComboDrawer.h"
#include"../Math/MathHelper.h"
#include"../Graphic/Sprite.h"
#include"ComboSupportUI.h"

static const Vector2 defCursorPos{ 100.0f, 600.0f };
static const float slideSize{ 200.0f };
ComboDrawer::ComboDrawer():
	UI("ComboDrawer",Vector2::Zero)
{
}

void ComboDrawer::initialize()
{
	stepUIs_.clear();
	comboType_ = SuccessComboType::None;
	alpha_ = 0.0f;

}

void ComboDrawer::update(float deltaTime)
{
	if (comboType_ == SuccessComboType::None) {
		alpha_ -= deltaTime*2.0f;
	}
	else {
		alpha_ += deltaTime*2.0f;

	}
	alpha_ = MathHelper::Clamp(alpha_, 0.0f, 1.0f);

	for (auto& s : stepUIs_) {
		s.update(deltaTime);
	}
	if (stepUIs_.empty())return;

	if (stepUIs_.front().isDead()) {
		uiDead();
	}
}

void ComboDrawer::draw() const
{
	ComboSupportUI::drawCombo(stepUIs_);
	for (auto& s : stepUIs_) {
		s.draw();
	}
	Sprite::GetInstance().Draw(id_, Vector2{ 100.0f,340.0f }, alpha_);
}

void ComboDrawer::Notify(Notification type, void * param)
{
	switch (type)
	{
	case Notification::Call_CreateJustEffect:
		break;
	case Notification::Call_JustStep:
		break;
	case Notification::Call_StepSuccess:
		break;
	case Notification::Call_StepFailed:
		break;
	case Notification::Call_ReciveStep:
		break;
	case Notification::Call_ComboStep:
		break;
	//case Notification::Call_ComboParts: {
	//	if (isCombo_)return;

	//	auto parts = *(std::vector<Player_Animation>*)param;
	//	//í«â¡
	//	if (parts.size() > stepUIs_.size()) {
	//		int size = parts.size() - stepUIs_.size();//çÏê¨êî
	//		for (int i = 0; i < size; i++) {
	//			int target = parts.size() - size + i;//í«â¡ëŒè€
	//			addStep(parts.at(target));
	//		}
	//	}
	//	else if (parts.size() < stepUIs_.size()) {
	//		int size = stepUIs_.size() - parts.size();//çÌèúêî

	//		for (int i = 0; i < stepUIs_.size(); i++) {
	//			if (i < size) {
	//				stepUIs_[i].dead();
	//			}
	//			else if (i >= parts.size()) {//îÕàÕäOÇÕçÌèú
	//				break;
	//			}
	//			else {
	//				int target = i - size;
	//				stepUIs_[i].setID(chooseID(parts[target]));
	//			}
	//		}
	//	}
	//	else {
	//		for (int i = 0; i < stepUIs_.size(); i++) {
	//			stepUIs_[i].setID(chooseID(parts[i]));
	//		}
	//	}
	//	break;
	//}
	case Notification::Call_Success_Combo_PointUp: {
		comboType_ = SuccessComboType::PointUp;
		id_ = SPRITE_ID::COMBO_POINTUP_SPRITE;
		break;
	}
	case Notification::Call_Success_Combo_Burst: {
		comboType_ = SuccessComboType::Burst;
		id_ = SPRITE_ID::COMBO_BURST_SPRITE;
		break;
	}
	case Notification::Call_Combo_Reset: {
		stepUIs_.clear();
		comboType_ = SuccessComboType::None;
		alpha_ = 0.0f;
		break;
	}
	//	isCombo_ = true;
	//	if (stepUIs_.size() < 3) {
	//		int s = stepUIs_.size();
	//		for (int i = 0; i < 3-s; i++) {
	//			switch (s+i)
	//			{
	//			case 0: {
	//				addStep(Player_Animation::Quarter);
	//				break;
	//			}
	//			case 1: {
	//				addStep(Player_Animation::Quarter);
	//				break;
	//			}
	//			case 2: {
	//				addStep(Player_Animation::Turn);
	//				break;

	//			}
	//			default:
	//				break;
	//			}
	//		}
	//	}
	//	break;
	//case Notification::Call_Success_Combo_Burst:
	//	isCombo_ = true;
	//	if (stepUIs_.size() < 3) {
	//		int s = stepUIs_.size();
	//		for (int i = 0; i < 3 - s; i++) {
	//			switch (s + i)
	//			{
	//			case 0: {
	//				addStep(Player_Animation::Turn);
	//				break;
	//			}
	//			case 1: {
	//				addStep(Player_Animation::Quarter);
	//				break;
	//			}
	//			case 2: {
	//				addStep(Player_Animation::Turn);
	//				break;

	//			}
	//			default:
	//				break;
	//			}
	//		}
	//	}

	//	break;
	case Notification::Call_Combo_End: {
		int deleteCount = 3;
		for (auto& s : stepUIs_) {
			if (deleteCount <= 0)break;
			if (s.isStartDead())continue;
			s.dead();
			deleteCount--;
		}
		comboType_ = SuccessComboType::None;
		break;
	}
		//isCombo_ = false;
		//for (auto& s : stepUIs_) {
		//	s.dead();
		//}
	case Notification::Call_Combo_Add: {
		auto next = *(Player_Animation*)param;
		addStep(next);
		break;
	}
	case Notification::Call_Combo_Delete: {
		auto deleteCount = *(int*)param;
		for (auto& s : stepUIs_) {
			if (deleteCount <= 0)break;
			if (s.isStartDead())continue;
			s.dead();
			deleteCount--;
		}
		break;
	}
	default:
		break;
	}
}

void ComboDrawer::uiDead()
{
	stepUIs_.erase(stepUIs_.begin());
	for (int i = 0; i < stepUIs_.size();i++) {
		Vector2 pos = defCursorPos + Vector2{ slideSize*i,0.0f };
		stepUIs_[i].startSlide(pos);
	}
}

void ComboDrawer::addStep(Player_Animation type)
{
	StepParts::DrawStepType stepType;
	switch (type)
	{
	case Player_Animation::Quarter:
		stepType = StepParts::DrawStepType::Quarter;
		break;
	case Player_Animation::Shoot:
		stepType = StepParts::DrawStepType::Spin;
		break;
	case Player_Animation::Turn:
		stepType = StepParts::DrawStepType::Turn;
		break;
	case Player_Animation::Half:
		stepType = StepParts::DrawStepType::Half;
		break;
	default:
		break;
	}
	Vector2 pos = defCursorPos + Vector2{ slideSize*stepUIs_.size(),0.0f };
	stepUIs_.emplace_back(stepType, pos);
}

StepParts::DrawStepType ComboDrawer::chooseID(Player_Animation type)
{
	StepParts::DrawStepType stepType;
	switch (type)
	{
	case Player_Animation::Quarter:
		stepType = StepParts::DrawStepType::Quarter;
		break;
	case Player_Animation::Shoot:
		stepType = StepParts::DrawStepType::Spin;
		break;
	case Player_Animation::Turn:
		stepType = StepParts::DrawStepType::Turn;
		break;
	case Player_Animation::Half:
		stepType = StepParts::DrawStepType::Half;
		break;
	default:
		break;
	}
	return stepType;
}
