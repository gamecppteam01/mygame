#include "InputChecker.h"
#include<string>

InputChecker::InputChecker()
{
	//各種キーの関連付け
	inputList_[Input_Key::A] = Connect_Key_Pad(KEYCODE::N, DualshockKey::Circle);
	inputList_[Input_Key::B] = Connect_Key_Pad(KEYCODE::M, DualshockKey::Cross);
	inputList_[Input_Key::X] = Connect_Key_Pad(KEYCODE::Z, DualshockKey::Square);
	inputList_[Input_Key::Y] = Connect_Key_Pad(KEYCODE::X, DualshockKey::Triangle);
	inputList_[Input_Key::R1] = Connect_Key_Pad(KEYCODE::E, DualshockKey::R1);
	inputList_[Input_Key::L1] = Connect_Key_Pad(KEYCODE::Q, DualshockKey::L1);
	inputList_[Input_Key::Start] = Connect_Key_Pad(KEYCODE::H, DualshockKey::Option);
	inputList_[Input_Key::Back] = Connect_Key_Pad(KEYCODE::B, DualshockKey::Share);

}

bool InputChecker::KeyTriggerDown(Input_Key key)const
{
	return Keyboard::GetInstance().KeyTriggerDown(inputList_.at(key).first) || DualShock4Input::GetInstance().IsTriggerDown(inputList_.at(key).second);
}

bool InputChecker::KeyTriggerUp(Input_Key key)const
{
	return Keyboard::GetInstance().KeyTriggerUp(inputList_.at(key).first) || DualShock4Input::GetInstance().IsTriggerUp(inputList_.at(key).second);
}

bool InputChecker::KeyStateDown(Input_Key key)const
{
	return Keyboard::GetInstance().KeyStateDown(inputList_.at(key).first) || DualShock4Input::GetInstance().IsStateDown(inputList_.at(key).second);
}

bool InputChecker::KeyStateUp(Input_Key key)const
{
	return Keyboard::GetInstance().KeyStateUp(inputList_.at(key).first) && DualShock4Input::GetInstance().IsStateUp(inputList_.at(key).second);
}

Vector2 InputChecker::Stick()const
{
	Vector2 result = Vector2::Zero;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A)) result.x -= 1.f;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D)) result.x += 1.f;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W)) result.y -= 1.f;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S)) result.y += 1.f;

	Vector2 stickVector = DualShock4Input::GetInstance().GetStick();
	if (std::abs(stickVector.x) <= 0.05f)stickVector.x = 0.f;
	if (std::abs(stickVector.y) <= 0.05f)stickVector.y = 0.f;


	result += stickVector;
	result = Vector2::Clamp(result, Vector2(-1.f, -1.f), Vector2(1.f, 1.f));

	return result;
}

int InputChecker::GetPovAngle() const
{
	return DualShock4Input::GetInstance().GetPovAngle();
}

int InputChecker::GetPovTriggerDownAngle() const
{
	return DualShock4Input::GetInstance().GetPovTriggerDownAngle();
}

bool InputChecker::StickStateDown(Input_Stick stick) const
{
	switch (stick)
	{
	case Input_Stick::Down:
		return Stick().y >= 0.5f;
		break;
	case Input_Stick::Up:
		return Stick().y <= -0.5f;
		break;
	case Input_Stick::Left:
		return Stick().x <= -0.5f;
		break;
	case Input_Stick::Right:
		return Stick().x >= 0.5f;
		break;
	default:
		break;
	}
	return false;
}

bool InputChecker::StickTriggerDown(Input_Stick stick) const
{
	Vector2 result = Vector2::Zero;
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::A)) result.x -= 1.f;
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::D)) result.x += 1.f;
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::W)) result.y -= 1.f;
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::S)) result.y += 1.f;

	result += DualShock4Input::GetInstance().GetStick();
	result = Vector2::Clamp(result, Vector2(-1.f, -1.f), Vector2(1.f, 1.f));

	Vector2 previousStick = DualShock4Input::GetInstance().GetPrevStick();

	switch (stick)
	{
	case Input_Stick::Down:
		return result.y >= 0.5f&&previousStick.y<0.5f;
		break;
	case Input_Stick::Up:
		return result.y <= -0.5f&&previousStick.y>-0.5f;
		break;
	case Input_Stick::Left:
		return result.x <= -0.5f&&previousStick.x>-0.5f;
		break;
	case Input_Stick::Right:
		return result.x >= 0.5f&&previousStick.x<0.5f;
		break;
	default:
		break;
	}

	return false;

}

Vector2 InputChecker::RightStick() const
{
	Vector2 result = Vector2::Zero;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::J)) result.x -= 1.f;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::L)) result.x += 1.f;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::I)) result.y -= 1.f;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::K)) result.y += 1.f;

	result += DualShock4Input::GetInstance().GetRightStick();
	result = Vector2::Clamp(result, Vector2(-1.f, -1.f), Vector2(1.f, 1.f));

	return result;

}

bool InputChecker::RightStickStateDown(Input_Stick stick) const
{
	switch (stick)
	{
	case Input_Stick::Down:
		return RightStick().y >= 0.5f;
		break;
	case Input_Stick::Up:
		return RightStick().y <= -0.5f;
		break;
	case Input_Stick::Left:
		return RightStick().x <= -0.5f;
		break;
	case Input_Stick::Right:
		return RightStick().x >= 0.5f;
		break;
	default:
		break;
	}
	return false;
}

bool InputChecker::RightStickTriggerDown(Input_Stick stick) const
{
	Vector2 result = Vector2::Zero;
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::J)) result.x -= 1.f;
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::L)) result.x += 1.f;
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::I)) result.y -= 1.f;
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::K)) result.y += 1.f;

	result += DualShock4Input::GetInstance().GetRightStick();
	result = Vector2::Clamp(result, Vector2(-1.f, -1.f), Vector2(1.f, 1.f));

	Vector2 previousStick = DualShock4Input::GetInstance().GetPrevRightStick();

	switch (stick)
	{
	case Input_Stick::Down:
		return result.y >= 0.5f&&previousStick.y<0.5f;
		break;
	case Input_Stick::Up:
		return result.y <= -0.5f&&previousStick.y>-0.5f;
		break;
	case Input_Stick::Left:
		return result.x <= -0.5f&&previousStick.x>-0.5f;
		break;
	case Input_Stick::Right:
		return result.x >= 0.5f&&previousStick.x<0.5f;
		break;
	default:
		break;
	}

	return false;
}

bool InputChecker::AnyInputStateDown() const
{
	return
	Keyboard::GetInstance().AnyStateDown()||
	DualShock4Input::GetInstance().GetAnyStateDown()||
	StickStateDown(Input_Stick::Down)||
	StickStateDown(Input_Stick::Left)||
	StickStateDown(Input_Stick::Right)||
	StickStateDown(Input_Stick::Up);
}

void InputChecker::Update()
{
	Keyboard::GetInstance().Update();
}
