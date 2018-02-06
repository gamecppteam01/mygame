#include "SoftwareKeyboard.h"
#include"../../Input/InputChecker.h"
#include"../../Math/MathHelper.h"
#include"../../Graphic/Sprite.h"

SoftwareKeyboard::SoftwareKeyboard()
{
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

	//if (keylist.at(currentKey_.y).at(currentKey_.x).character == "EX") {//特殊文字列時の例外処理
	//	currentKey_ += PointChangeEX(keylist.at(currentKey_.y).at(currentKey_.x).decorateVec.front(), currentChange);
	//}

	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::R1)) {
		keylist.at(currentKey_.y).at(currentKey_.x)->push(this);
		//std::string chara = keylist.at(currentKey_.y).at(currentKey_.x).character;
		//auto deco = keylist.at(currentKey_.y).at(currentKey_.x).decorateVec;
		//if (name_.size() <= 4)name_.emplace_back(chara, deco);
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::L1)) {
		if (!name_.empty())name_.pop_back();
	}
}

void SoftwareKeyboard::draw(const Vector2 & position)const
{
	Sprite::GetInstance().Draw(SPRITE_ID::KEYBOARD_FRAME_SPRITE, position + Vector2{ -50.0f,-30.0f });
	
	for (auto& k : keylist) {
		for (auto& kc : k) {
			//if (kc.character == "EX")continue;
			kc->draw(position);
		}
	}
	Vector2 pos = position + keylist.at(currentKey_.y).at(currentKey_.x)->getDrawPos();
	DrawCircle(pos.x, pos.y, 16, GetColor(255, 0, 0));

	for (int i = 0; i < name_.size(); i++) {
		FontManager::GetInstance().DrawTextApplyFont(800 + i * 20, 50, GetColor(255, 255, 255), FONT_ID::KEYBOARD_FONT, name_.at(i).getCurrentText());
	}
}

void KeyChar::push(SoftwareKeyboard * kbd)
{
	if (kbd->getName().size() < 4) {//最大文字数は4
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
