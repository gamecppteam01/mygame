#include "SoftwareKeyboard.h"
#include"../../Input/InputChecker.h"
#include"../../Math/MathHelper.h"
#include"../../Graphic/Sprite.h"
#include"../../DataManager/DataManager.h"

SoftwareKeyboard::SoftwareKeyboard():cursor_(keylist.at(currentKey_.y).at(currentKey_.x)->getDrawPos())
{
}

void SoftwareKeyboard::initialize()
{
	currentKey_=Point{ 0,0 };

	cursor_.initialize(keylist.at(currentKey_.y).at(currentKey_.x)->getDrawPos());

	state_.clear();
	state_.push_back(InputState::INPUT_NONE);
	state_.push_back(InputState::INPUT_WOMEN);
	state_.push_back(InputState::INPUT_MEN);

	name_.clear();

}

void SoftwareKeyboard::stateReset()
{
	state_.clear();
	state_.push_back(InputState::INPUT_NONE);
	state_.push_back(InputState::INPUT_WOMEN);
	state_.push_back(InputState::INPUT_MEN);

}

void SoftwareKeyboard::update(float deltaTime)
{
	Point currentChange{ 0,0 };
	bool isMove = true;//動いたか
	//入力があったら変更
	switch (InputChecker::GetInstance().GetPovTriggerDownAngle()) {
	case 0: {
		currentChange.y = -1;
		//currentKey_=keymoveList.at(currentKey_.y).at(currentKey_.x).next.at(0);
		break;
	}
	case 90: {
		currentChange.x = 1;
		//currentKey_ = keymoveList.at(currentKey_.y).at(currentKey_.x).next.at(1);
		break;
	}
	case 180: {
		currentChange.y = 1;
		//currentKey_ = keymoveList.at(currentKey_.y).at(currentKey_.x).next.at(2);
		break;
	}
	case 270: {
		currentChange.x = -1;
		//currentKey_ = keymoveList.at(currentKey_.y).at(currentKey_.x).next.at(3);
		break;
	}
	default: {
		isMove = false;
		break;
	}
	}
	//範囲内に収める
	currentKey_+=currentChange;

	currentKey_.y = MathHelper::Clamp(currentKey_.y, 0, keylist.size()-1);
	currentKey_.x = MathHelper::Clamp(currentKey_.x, 0, keylist.at(currentKey_.y).size()-1);

	if (isMove)keylist.at(currentKey_.y).at(currentKey_.x)->select(this, currentChange);
	
	cursor_.setPosition(keylist.at(currentKey_.y).at(currentKey_.x)->getDrawPos());
	//if (keylist.at(currentKey_.y).at(currentKey_.x).character == "EX") {//特殊文字列時の例外処理
	//	currentKey_ += PointChangeEX(keylist.at(currentKey_.y).at(currentKey_.x).decorateVec.front(), currentChange);
	//}

	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
		keylist.at(currentKey_.y).at(currentKey_.x)->push(this);
		//std::string chara = keylist.at(currentKey_.y).at(currentKey_.x).character;
		//auto deco = keylist.at(currentKey_.y).at(currentKey_.x).decorateVec;
		//if (name_.size() <= 4)name_.emplace_back(chara, deco);
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::B)) {
		if (!name_.empty())name_.pop_back();
	}

	cursor_.update(deltaTime);
}

void SoftwareKeyboard::draw(const Vector2 & position)const
{
	Vector2 leftVector{ -50.0f,-30.0f };
	Vector2 back = Sprite::GetInstance().GetSize(SPRITE_ID::KEYBOARD_FRAME_SPRITE);
	DrawBox(position.x + leftVector.x, position.y + leftVector.y, position.x + back.x + leftVector.x, position.y + back.y + leftVector.y, GetColor(160, 160, 160), TRUE);
	Sprite::GetInstance().Draw(SPRITE_ID::KEYBOARD_FRAME_SPRITE, position + leftVector);
	
	SetDrawBright(0, 0, 0);
	for (auto& k : keylist) {
		for (auto& kc : k) {
			//if (kc.character == "EX")continue;
			kc->draw(position + Vector2{ 3.f,3.f });
		}
	}
	SetDrawBright(255, 255, 255);
	for (auto& k : keylist) {
		for (auto& kc : k) {
			//if (kc.character == "EX")continue;
			kc->draw(position);
		}
	}
	//SetDrawBright(255, 255, 255);
	Vector2 pos = position + keylist.at(currentKey_.y).at(currentKey_.x)->getDrawPos();
	//DrawCircle(pos.x, pos.y, 16, GetColor(255, 0, 0));
	cursor_.draw(position);
	//for (int i = 0; i < name_.size(); i++) {
	//	FontManager::GetInstance().DrawTextApplyFont(800 + i * 20, 350, GetColor(255, 255, 255), FONT_ID::KEYBOARD_FONT, name_.at(i).getCurrentText());
	//}
}

void KeyChar::push(SoftwareKeyboard * kbd)
{
	if (kbd->getName().size() < 5) {//最大文字数は5
		kbd->getName().emplace_back(character, isCanSmall, decorateVec);
	}
}

void CursorMove::select(SoftwareKeyboard * kbd, const Point & currentMove)
{
	if (currentMove.x > 0) {//左から来た時
		kbd->getCurrentKey() += left_;
	}
	if (currentMove.x < 0) {//右から来た時
		kbd->getCurrentKey() += right_;
	}
	if (currentMove.y > 0) {//上から来た時
		kbd->getCurrentKey() += up_;
	}
	if (currentMove.y < 0) {//下から来た時
		kbd->getCurrentKey() += down_;
	}
}

void ChangeMinChara::push(SoftwareKeyboard * kbd) {
	if (kbd->getName().empty())return;//空なら終わり
	kbd->getName().back().changeMin();
}

void ChangeDecoChara::push(SoftwareKeyboard * kbd) {
	if (kbd->getName().empty())return;//空なら終わり
	kbd->getName().back().changeDeco();
}

void DecideName::push(SoftwareKeyboard * kbd)
{
	if (kbd->getName().empty())return;//空なら終わり
	std::string name{ "" };
	for (auto& n : kbd->getName()) {
		name += n.getCurrentText();
	}
	
	if (kbd->getState() == SoftwareKeyboard::InputState::INPUT_MEN) {
		DataManager::GetInstance().setMenName(name, kbd->getName().size());
		kbd->nextState();
	}
	else if (kbd->getState() == SoftwareKeyboard::InputState::INPUT_WOMEN) {
		DataManager::GetInstance().setWoMenName(name, kbd->getName().size());
		kbd->nextState();
	}
	kbd->clearName();
}
