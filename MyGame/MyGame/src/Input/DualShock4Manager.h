#pragma once

#include"../Math/Math.h"
#include"../Conv/ByteConverter.h"
#include"hidsdi.h"
#include"setupapi.h"
#include<list>

#pragma comment(lib, "hid.lib")
#pragma comment(lib, "SetupAPI.lib") 

/*
DualShock4�R���g���[���̌X����(��܂���)�擾���邽�߂̃N���X
��1)���m�Ȋp�x���o���Ă���킯�ł͂Ȃ�
��2)������DualShock4�R���g���[�����ڑ������ꍇ�ɂ��Ă͍l�����Ă��Ȃ�
*/
class DualShock4Manager {
	friend class TitleScene;

private:
	DualShock4Manager();
	~DualShock4Manager();
public:
	static DualShock4Manager& GetInstance();

	//DualShock4�R���g���[����F������(����������true��Ԃ�)
	bool Initialize();
	//ReadFile��Bluetooth���Ɛ���ɍs���Ȃ����߁A�����ŉi���ɑҋ@�������Đ�ɐi�߂Ȃ���肠��(USB�ł̗L���ڑ��ɂ��g�p���鎖)
	void Update();
	//�R���g���[���f�[�^�̕ێ����I������
	void Clear();

	//�R���g���[����z,x���̌X�����擾����(x�ɂ͍��E�̌X��������E�����Ay�ɂ͑O��̌X�������艜�����Ƃ���)
	Vector2 GetAngle() const;

	//�R���g���[����x,y,z���̌X�����擾����(x,y�͂ǂ����-180�`0,0�`180�̊p�x�������Az��-90�`90�͈̔͂ŁA�\�Ȃ琳�A���Ȃ畉������)
	Vector3 GetAngle3D() const;
	Vector3 GetGyroVector()const;
	byte GetByte(int key)const;
	byte GetPrevByte(int key)const;
private:
	//�����x����A�ŏ��̊p�x�����߂�
	void First_Angle();
	//�p�x���o
	void Update_Angle();
	void Update_Gyro();
	//�����x�̍X�V
	void Update_Acceleration();
	void SelectAngle();

private:
	//�R���g���[���̃n���h��
	HANDLE handle_{};
	//�Ώ�HID�̑���M�T�C�Y��������
	HIDP_CAPS	caps_{};
	//�R���g���[���̓��̓f�[�^�z��
	byte *currentData_;
	byte *previousData_;
	DWORD dataSize_;
	//Bluetooth�̎��̃f�[�^�Y������������l�ABluetooth�Ȃ�2,�L���Ȃ�0(Bluetooth���ƃf�[�^��2�Y������ۂ����?)
	int isbluetooth_{ 0 };
	//xz�̃Q�[���p�p�x
	Vector2 angle_{ Vector2::Zero };
	//�R���g���[����xyz�p�x
	Vector3 angle3d_{ Vector3::Zero };
	//�X��xyz
	Vector3 gyroVector_{ Vector3::Zero };
	//���̉����x
	Vector3 acceleration_{ Vector3::Zero };
	//���̃W���C���l
	Vector3 gyro_{ Vector3::Zero };

	Vector3 currentAngle_{ Vector3::Zero };
	
	Matrix accelMat_{ Matrix::Identity };
	//�W���C����]�s��̍����l
	Matrix gyroMat_{ Matrix::Identity };
	//���t���[���̃W���C����]�s��
	Matrix frameGyroMat_{ Matrix::Identity };

	std::list<float> xAngleList_;
	std::list<float> yAngleList_;
	std::list<float> zAngleList_;
private:
	//�����x�Z���T�[�̌X�����o���̍ő�l,�d�͉����x�����̒l�Ɠ��l
	const int maxAcceleration{ 8192 };
	//�����x1������̉����x���o�l
	const int baseAcceleration{ 836 };
	const int maxGyro{ 1024 };
};

