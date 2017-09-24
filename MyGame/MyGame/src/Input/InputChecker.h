#pragma once
#include"Keyboard.h"
#include"GamePad.h"
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
		Key_Count//���p����L�[�̐�
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
	//�L�[�������ꂽ����Ԃ�
	bool KeyTriggerDown(Input_Key key)const;
	//�L�[������������Ԃ�
	bool KeyTriggerUp(Input_Key key)const;
	//�L�[�������Ă��邩��Ԃ�
	bool KeyStateDown(Input_Key key)const;
	//�L�[��������Ă��邩��Ԃ�
	bool KeyStateUp(Input_Key key)const;

	//�X�e�B�b�N�̌X����Ԃ�
	Vector2 Stick()const;

	//�w������ɃX�e�B�b�N���|��Ă��邩��Ԃ�
	bool StickStateDown(Input_Stick stick)const;
	//�w������ɃX�e�B�b�N��|��������Ԃ�
	bool StickTriggerDown(Input_Stick stick)const;

	//�E�X�e�B�b�N�̌X����Ԃ�
	Vector2 RightStick()const;
	//�w������ɉE�X�e�B�b�N���|��Ă��邩��Ԃ�
	bool RightStickStateDown(Input_Stick stick)const;
	//�w������ɉE�X�e�B�b�N��|��������Ԃ�
	bool RightStickTriggerDown(Input_Stick stick)const;

	bool AnyInputStateDown()const;

	void Update();
private:
	using Connect_Key_Pad = std::pair<UINT, UINT>;
	std::map<Input_Key, Connect_Key_Pad> inputList_;

};