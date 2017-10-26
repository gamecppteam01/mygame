#pragma once
#include"DualShockKey.h"
#include"../Math/Vector2.h"

class DualShock4Input {
private:
	DualShock4Input() {

	}
public:
	static DualShock4Input& GetInstance() {
		static DualShock4Input ds;
		return ds;
	}
	//�L�[���͂��s���Ă��邩�𒲂ׂ�(DualshockKey�ɃL�[�ꗗ�����邽�߁A�������玝���Ă���)
	bool IsStateDown(const std::pair<int, int>& keyCode)const;
	//�L�[���͂��s���Ă��Ȃ����𒲂ׂ�(DualshockKey�ɃL�[�ꗗ�����邽�߁A�������玝���Ă���)
	bool IsStateUp(const std::pair<int, int>& keyCode)const;
	//�L�[���͂��s��ꂽ�u�Ԃ��𒲂ׂ�(DualshockKey�ɃL�[�ꗗ�����邽�߁A�������玝���Ă���)
	bool IsTriggerDown(const std::pair<int, int>& keyCode)const;
	//�L�[���͂��I������u�Ԃ��𒲂ׂ�(DualshockKey�ɃL�[�ꗗ�����邽�߁A�������玝���Ă���)
	bool IsTriggerUp(const std::pair<int, int>& keyCode)const;
	//�ǂ�������̃L�[��������Ă��邩
	bool GetAnyStateDown()const;

	//�X�e�B�b�N���͂��擾����A���S��0�ɂȂ鎖���������߁A�e���ŏ������l�𖳎����鎖
	Vector2 GetStick()const;
	//�O�̃X�e�B�b�N���͂��擾����A���S��0�ɂȂ鎖���������߁A�e���ŏ������l�𖳎����鎖
	Vector2 GetPrevStick()const;
	//�E�X�e�B�b�N���͂��擾����A���S��0�ɂȂ鎖���������߁A�e���ŏ������l�𖳎����鎖
	Vector2 GetRightStick()const;
	//�O�̉E�X�e�B�b�N���͂��擾����A���S��0�ɂȂ鎖���������߁A�e���ŏ������l�𖳎����鎖
	Vector2 GetPrevRightStick()const;
	//�n�b�g�X�C�b�`�̓��͊p�x���擾����
	int GetPovAngle()const;
	//�n�b�g�X�C�b�`�������ꂽ���u�Ԃ��ǂ���
	int GetPovTriggerDownAngle()const;
};
