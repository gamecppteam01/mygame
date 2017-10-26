#include "DualShock4Input.h"
#include"DualShock4Manager.h"

bool DualShock4Input::IsStateDown(const std::pair<int, int>& keyCode) const{
	int target = DualShock4Manager::GetInstance().GetByte(keyCode.first);

	return (target&keyCode.second) != 0;
}

bool DualShock4Input::IsStateUp(const std::pair<int, int>& keyCode) const
{
	int target = DualShock4Manager::GetInstance().GetByte(keyCode.first);

	return (target&keyCode.second) == 0;
}

bool DualShock4Input::IsTriggerDown(const std::pair<int, int>& keyCode)const
{
	int target = DualShock4Manager::GetInstance().GetByte(keyCode.first);
	int prevTarget= DualShock4Manager::GetInstance().GetPrevByte(keyCode.first);
	return ((target&keyCode.second) != 0)&&((prevTarget&keyCode.second) == 0);
}

bool DualShock4Input::IsTriggerUp(const std::pair<int, int>& keyCode) const
{
	int target = DualShock4Manager::GetInstance().GetByte(keyCode.first);
	int prevTarget = DualShock4Manager::GetInstance().GetPrevByte(keyCode.first);
	return ((target&keyCode.second) == 0) && ((prevTarget&keyCode.second) != 0);
}

bool DualShock4Input::GetAnyStateDown() const
{
	int data1 = DualShock4Manager::GetInstance().GetByte(5);
	int data2 = DualShock4Manager::GetInstance().GetByte(6);

	return data1 != 8 || data2 != 0;
}

Vector2 DualShock4Input::GetStick()const
{
	//右が+
	int x = DualShock4Manager::GetInstance().GetByte(1);
	//前が+
	int y = -DualShock4Manager::GetInstance().GetByte(2);
	//符号をつける
	x = x - 128; if (MathHelper::Sign(x) >= 0)x += 1;//0を無くす
	y = y + 128; if (MathHelper::Sign(y) <= 0)y -= 1;//0を無くす

	return Vector2(x / 128.0f, y / 128.0f);
}

Vector2 DualShock4Input::GetPrevStick() const
{
	//右が+
	int x = DualShock4Manager::GetInstance().GetPrevByte(1);
	//前が+
	int y = -DualShock4Manager::GetInstance().GetPrevByte(2);
	//符号をつける
	x = x - 128; if (MathHelper::Sign(x) >= 0)x += 1;//0を無くす
	y = y + 128; if (MathHelper::Sign(y) <= 0)y -= 1;//0を無くす

	return Vector2(x / 128.0f, y / 128.0f);
}

Vector2 DualShock4Input::GetRightStick()const
{
	//右が+
	int x = DualShock4Manager::GetInstance().GetByte(3);
	//前が+
	int y = -DualShock4Manager::GetInstance().GetByte(4);
	//符号をつける
	x = x - 128; if (MathHelper::Sign(x) >= 0)x += 1;//0を無くす
	y = y + 128; if (MathHelper::Sign(y) <= 0)y -= 1;//0を無くす

	return Vector2(x / 128.0f, y / 128.0f);
}

Vector2 DualShock4Input::GetPrevRightStick() const
{
	//右が+
	int x = DualShock4Manager::GetInstance().GetPrevByte(3);
	//前が+
	int y = -DualShock4Manager::GetInstance().GetPrevByte(4);
	//符号をつける
	x = x - 128; if (MathHelper::Sign(x) >= 0)x += 1;//0を無くす
	y = y + 128; if (MathHelper::Sign(y) <= 0)y -= 1;//0を無くす

	return Vector2(x / 128.0f, y / 128.0f);
}

int DualShock4Input::GetPovAngle() const
{
	int pov = DualShock4Manager::GetInstance().GetByte(5);
	if ((pov & 8) != 0)return -1;
	if ((pov & 7) == 7)return 315;
	if ((pov & 6) == 6)return 270;
	if ((pov & 5) == 5)return 225;
	if ((pov & 4) == 4)return 180;
	if ((pov & 3) == 3)return 135;
	if ((pov & 2) == 2)return 90;
	if ((pov & 1) == 1)return 45;
	return 0;

}

int DualShock4Input::GetPovTriggerDownAngle() const
{
	int pov = DualShock4Manager::GetInstance().GetByte(5);
	int prevPov = DualShock4Manager::GetInstance().GetPrevByte(5);
	if ((pov & 8) != 0)return -1;
	if ((pov & 7) == 7) {
		if((prevPov & 7) != 7)return 315;
		else return -1;
	}
	if ((pov & 6) == 6) {
		if((prevPov & 6) != 6)return 270;
		else return -1;
	}
	if ((pov & 5) == 5) {
		if((prevPov & 5) != 5)return 225;
		else return -1;
	}
	if ((pov & 4) == 4) {
		if((prevPov & 4) != 4)return 180;
		else return -1;
	}
	if ((pov & 3) == 3) {
		if((prevPov & 3) != 3)return 135;
		else return -1;
	}
	if ((pov & 2) == 2) {
		if((prevPov & 2) != 2)return 90;
		else return -1;
	}
	if ((pov & 1) == 1) {
		if((prevPov & 1) != 1)return 45;
		else return -1;
	}
	if ((prevPov & 8) == 0)return -1;
	else return 0;
}
