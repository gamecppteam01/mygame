#pragma once

#include <Dxlib.h>
#include "../math/Vector2.h"
#include <unordered_map>
#include <vector>
#include <array>

//�ڑ����Ă���p�b�h�̔ԍ�(����pad�̂Ƃ���Ɏg�p)
namespace PADNUM
{
	const UINT PAD1 = DX_INPUT_PAD1;
	const UINT PAD2 = DX_INPUT_PAD2;
	const UINT PAD3 = DX_INPUT_PAD3;
	const UINT PAD4 = DX_INPUT_PAD4;
}

//�p�b�h�̃{�^��(����button�̂Ƃ���Ɏg�p)
namespace PADBUTTON
{
	const UINT RIGHT = PAD_INPUT_RIGHT;
	const UINT LEFT = PAD_INPUT_LEFT;
	const UINT UP = PAD_INPUT_UP;
	const UINT DOWN = PAD_INPUT_DOWN;
	const UINT NUM1 = PAD_INPUT_1;
	const UINT NUM2 = PAD_INPUT_2;
	const UINT NUM3 = PAD_INPUT_3;
	const UINT NUM4 = PAD_INPUT_4;
	const UINT NUM5 = PAD_INPUT_5;
	const UINT NUM6 = PAD_INPUT_6;
	const UINT NUM7 = PAD_INPUT_7;
	const UINT NUM8 = PAD_INPUT_8;
	const UINT NUM9 = PAD_INPUT_9;
	const UINT NUM10 = PAD_INPUT_10;
	const UINT NUM11 = PAD_INPUT_11;
	const UINT NUM12 = PAD_INPUT_12;
}

class GamePad
{
private:
	GamePad();
	~GamePad() = default;
public:
	static GamePad &GetInstance(){
		static GamePad g;
		return g;
	}

	///<summary>
	/// �w��̃p�b�h�̎w��̃{�^�������͂��ꂽ�u�Ԃ����ׂ�
	///</summary>
	bool ButtonTriggerDown(int button, int pad = PADNUM::PAD1);
	///<summary>
	/// �w��̃p�b�h�̎w��̃{�^�������͂���Ă��邩���ׂ�
	///</summary>
	bool ButtonStateDown(int button, int pad = PADNUM::PAD1);
	///<summary>
	/// �w��̃p�b�h�̎w��̃{�^�������ꂽ�u�Ԃ����ׂ�
	///</summary>
	bool ButtonTriggerUp(int button, int pad = PADNUM::PAD1);
	///<summary>
	/// �w��̃p�b�h�̎w��̃{�^��������Ă��邩���ׂ�
	///</summary>
	bool ButtonStateUp(int button, int pad = PADNUM::PAD1);
	/// <summary>
	/// �����ꂩ�̃{�^�������͂��ꂽ�u�Ԃ����ׂ�
	/// </summary>
	bool AnyTriggerDown(int pad = PADNUM::PAD1);
	/// <summary>
	/// �����ꂩ�̃{�^�������͂���Ă��邩���ׂ�
	/// </summary>
	bool AnyStateDown(int pad = PADNUM::PAD1);
	/// <summary>
	/// �����ꂩ�̃{�^�������ꂽ�u�Ԃ����ׂ�
	/// </summary>
	bool AnyTriggerUp(int pad = PADNUM::PAD1);
	/// <summary>
	/// �����ꂩ�̃{�^��������Ă��邩���ׂ�
	/// </summary>
	bool AnyStateUp(int pad = PADNUM::PAD1);
	///<summary>
	/// �w��̃p�b�h��POV�����͂��ꂽ�u�Ԃ̕������󂯎��
	///</summary>
	int POVTriggerDown(int pad = PADNUM::PAD1);
	///<summary>
	/// �w��̃p�b�h��POV�����͂��ꂽ�������󂯎��
	///</summary>
	int POVStateDown(int pad = PADNUM::PAD1);
	///<summary>
	/// �w��̃p�b�h�̃A�i���O�X�e�B�b�N�̓��͋�𒲂ׂ�
	/// (X = -1.0�`1.0, Y = -1.0�`1.0)
	///</summary>
	Vector2 Stick(int pad = PADNUM::PAD1);
	///<summary>
	/// ���t���[����1�ԖڃR���g���[���̃X�e�B�b�N���͂��󂯎��
	///</summary>
	Vector2 GetCurrentStick();
	///<summary>
	/// �O�t���[����1�ԖڃR���g���[���̃X�e�B�b�N���͂��󂯎��
	///</summary>
	Vector2 GetPreviousStick();
	///<summary>
	/// ���t���[����1�ԖڃR���g���[���̉E�X�e�B�b�N���͂��󂯎��
	///</summary>
	Vector2 GetCurrentRightStick();
	///<summary>
	/// �O�t���[����1�ԖڃR���g���[���̉E�X�e�B�b�N���͂��󂯎��
	///</summary>
	Vector2 GetPreviousRightStick();
	///<summary>
	/// �w��̃p�b�h�̉E�A�i���O�X�e�B�b�N�̓��͋�𒲂ׂ�
	/// (X = -1.0�`1.0, Y = -1.0�`1.0)
	///</summary>
	Vector2 RightStick(int pad = PADNUM::PAD1);
	///<summary>
	/// �w��̃p�b�h�̐U�����J�n����
	///</summary>
	void VibrationStart(int power, int time, int pad = PADNUM::PAD1);
	///<summary>
	/// �w��̃p�b�h�̐U�����I������
	///</summary>
	void VibrationEnd(int pad = PADNUM::PAD1);
	void Update();
private:
	void Exception(int pad, int button);

	//std::unordered_map<int, std::array<int, 50000>> m_currentbutton;// ���݂̃{�^�����
	//std::unordered_map<int, std::array<int, 50000>> m_previosbutton;// 1�t���[���O�̃{�^�����

	//<�p�b�h�ԍ�, <PAD_INPUT_1�Ȃ�, �J�E���^�[>
	std::unordered_map<int, std::unordered_map<int, int>> m_onbuttons;
	std::unordered_map<int, std::unordered_map<int, int>> m_offbuttons;

	std::unordered_map<int, int> m_onpovbuttons;

	std::vector<int> m_inputbuttons;// �{�^�����͔���B
	std::vector<int> m_pads;// �p�b�h�ԍ��B
	
	Vector2 curStick_;//���t���[���̃X�e�B�b�N����
	Vector2 prevStick_;//�O�t���[���̃X�e�B�b�N����

	Vector2 curRightStick_;//���t���[���̉E�X�e�B�b�N����
	Vector2 prevRightStick_;//�O�t���[���̉E�X�e�B�b�N����
};