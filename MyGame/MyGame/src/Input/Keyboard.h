#pragma once

#include "DxLib.h"
#include <array>

namespace KEYCODE
{
	const UINT RIGHT = KEY_INPUT_RIGHT;
	const UINT LEFT = KEY_INPUT_LEFT;
	const UINT UP = KEY_INPUT_UP;
	const UINT DOWN = KEY_INPUT_DOWN;
	const UINT A = KEY_INPUT_A;
	const UINT B = KEY_INPUT_B;
	const UINT C = KEY_INPUT_C;
	const UINT D = KEY_INPUT_D;
	const UINT E = KEY_INPUT_E;
	const UINT F = KEY_INPUT_F;
	const UINT G = KEY_INPUT_G;
	const UINT H = KEY_INPUT_H;
	const UINT I = KEY_INPUT_I;
	const UINT J = KEY_INPUT_J;
	const UINT K = KEY_INPUT_K;
	const UINT L = KEY_INPUT_L;
	const UINT M = KEY_INPUT_M;
	const UINT N = KEY_INPUT_N;
	const UINT O = KEY_INPUT_O;
	const UINT P = KEY_INPUT_P;
	const UINT Q = KEY_INPUT_Q;
	const UINT R = KEY_INPUT_R;
	const UINT S = KEY_INPUT_S;
	const UINT T = KEY_INPUT_T;
	const UINT U = KEY_INPUT_U;
	const UINT V = KEY_INPUT_V;
	const UINT W = KEY_INPUT_W;
	const UINT X = KEY_INPUT_X;
	const UINT Y = KEY_INPUT_Y;
	const UINT Z = KEY_INPUT_Z;
	const UINT LSHIFT = KEY_INPUT_LSHIFT;
	const UINT LCTRL = KEY_INPUT_LCONTROL;
	const UINT RSHIFT = KEY_INPUT_RSHIFT;
	const UINT RCTRL = KEY_INPUT_RCONTROL;
	const UINT SPACE = KEY_INPUT_ESCAPE;
	const UINT NUM1 = KEY_INPUT_1;
	const UINT NUM2 = KEY_INPUT_2;
	const UINT NUM3 = KEY_INPUT_3;
	const UINT NUM4 = KEY_INPUT_4;
	const UINT NUM5 = KEY_INPUT_5;
	const UINT NUM6 = KEY_INPUT_6;
	const UINT NUM7 = KEY_INPUT_7;
	const UINT NUM8 = KEY_INPUT_8;
	const UINT NUM9 = KEY_INPUT_9;
	const UINT NUM0 = KEY_INPUT_0;
	const UINT TAB = KEY_INPUT_TAB;
	const UINT ESC = KEY_INPUT_ESCAPE;
}

class Keyboard
{
private:
	Keyboard();
	~Keyboard() = default;

public:
	static Keyboard &GetInstance() {
		static Keyboard k;
		return k;
	}

	/// <summary>
	/// �w�肳�ꂽ�L�[�����͂��ꂽ�u�Ԃ����ׂ�
	/// </summary>
	bool KeyTriggerDown(UINT keycode);
	/// <summary>
	/// �w�肳�ꂽ�L�[�����͂���Ă��邩���ׂ�
	/// </summary>
	bool KeyStateDown(UINT keycode);
	/// <summary>
	/// �w�肳�ꂽ�L�[�����ꂽ�u�Ԃ����ׂ�
	/// </summary>
	bool KeyTriggerUp(UINT keycode);
	/// <summary>
	/// �w�肳�ꂽ�L�[������Ă��邩���ׂ�
	/// </summary>
	bool KeyStateUp(UINT keycode);
	/// <summary>
	/// �����ꂩ�̃L�[�����͂��ꂽ�u�Ԃ����ׂ�
	/// </summary>
	bool AnyTriggerDown();
	/// <summary>
	/// �����ꂩ�̃L�[�����͂���Ă��邩���ׂ�
	/// </summary>
	bool AnyStateDown();
	/// <summary>
	/// �����ꂩ�̃L�[�����ꂽ�u�Ԃ����ׂ�
	/// </summary>
	bool AnyTriggerUp();
	/// <summary>
	/// �����ꂩ�̃L�[������Ă��邩���ׂ�
	/// </summary>
	bool AnyStateUp();

	void Update();
private:
	void UpdateKey(char key, int num);
	char m_keycode[256];
	std::array<int, 256> m_onkey;
	std::array<int, 256> m_offkey;
};