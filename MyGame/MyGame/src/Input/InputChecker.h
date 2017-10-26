#pragma once
#include"Keyboard.h"
#include"DualShock4Input.h"
#include"../Math/Vector2.h"
#include<map>

class InputChecker {
public:
	enum Input_Key {
		A,
		B,
		X,
		Y,
		R1,
		L1,
		Start,
		Back,
		Key_Count//利用するキーの数
	};
	enum Input_Stick {
		Up,
		Down,
		Left,
		Right
	};

private:
	InputChecker();
public:
	static InputChecker& GetInstance() {
		static InputChecker ic;
		return ic;
	}
	//キーが押されたかを返す
	bool KeyTriggerDown(Input_Key key)const;
	//キーが離したかを返す
	bool KeyTriggerUp(Input_Key key)const;
	//キーを押しているかを返す
	bool KeyStateDown(Input_Key key)const;
	//キーが離されているかを返す
	bool KeyStateUp(Input_Key key)const;

	//スティックの傾きを返す
	Vector2 Stick()const;
	//ハットスイッチの入力角度を取得する(未入力なら-1)
	int GetPovAngle()const;
	//ハットスイッチの入力角度を取得する(未入力なら-1)
	int GetPovTriggerDownAngle()const;
	//指定方向にスティックが倒れているかを返す
	bool StickStateDown(Input_Stick stick)const;
	//指定方向にスティックを倒したかを返す
	bool StickTriggerDown(Input_Stick stick)const;

	//右スティックの傾きを返す
	Vector2 RightStick()const;
	//指定方向に右スティックが倒れているかを返す
	bool RightStickStateDown(Input_Stick stick)const;
	//指定方向に右スティックを倒したかを返す
	bool RightStickTriggerDown(Input_Stick stick)const;

	bool AnyInputStateDown()const;

	void Update();
private:
	using Connect_Key_Pad = std::pair<UINT, std::pair<int, int>>;
	std::map<Input_Key, Connect_Key_Pad> inputList_;

};