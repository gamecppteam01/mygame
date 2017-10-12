#pragma once

#include"DualShock4Reader.h"
#include"../Math/Math.h"
#include"../Conv/ByteConverter.h"

/*
DualShock4�R���g���[���̌X����(��܂���)�擾���邽�߂̃N���X
��1)���m�Ȋp�x���o���Ă���킯�ł͂Ȃ�
��2)������DualShock4�R���g���[�����ڑ������ꍇ�ɂ��Ă͍l�����Ă��Ȃ�
*/
class DualShock4Manager {
	friend class TitleScene;
private:
	DualShock4Manager() : dataSize_(0) {
		xAngleList_.resize(10, 0.0f);
		yAngleList_.resize(10, 0.0f);
		zAngleList_.resize(10, 0.0f);

		Initialize();
	}
	~DualShock4Manager() {
		free(currentData_);
	}
public:
	static DualShock4Manager& GetInstance() {
		static DualShock4Manager manager_;
		return manager_;
	}

	//DualShock4�R���g���[����F������(����������true��Ԃ�)
	bool Initialize() {
		//USB�ڑ��@���ID���擾
		GUID	hidGuid;
		HidD_GetHidGuid(&hidGuid);
		//�f�o�C�X�ꗗ���쐬
		HDEVINFO	hdevinfo;
		hdevinfo = SetupDiGetClassDevs(
			&hidGuid,
			NULL,
			NULL,
			DIGCF_PRESENT
			| DIGCF_DEVICEINTERFACE
			| DIGCF_ALLCLASSES
		);
		SP_DEVICE_INTERFACE_DATA	deviceInfoData;
		deviceInfoData.cbSize = sizeof(deviceInfoData);

		for (int index = 0; ; index++) {
			//HID�@��̎��񂪏I�������烋�[�v�𗣒E����
			if (!SetupDiEnumDeviceInterfaces(
				hdevinfo,
				0,
				&hidGuid,
				index,
				&deviceInfoData
			)) {
				break;
			}
			unsigned long size;
			SetupDiGetDeviceInterfaceDetail(hdevinfo, &deviceInfoData, NULL, 0, &size, 0);

			PSP_INTERFACE_DEVICE_DETAIL_DATA dev_det = PSP_INTERFACE_DEVICE_DETAIL_DATA(new char[size]);
			dev_det->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);

			SetupDiGetDeviceInterfaceDetail(hdevinfo, &deviceInfoData, dev_det, size, &size, 0);

			//�f�o�C�X�̃f�[�^���擾����
			handle_ = CreateFile(dev_det->DevicePath, GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
			if (handle_ == INVALID_HANDLE_VALUE) { continue; }

			HIDD_ATTRIBUTES attr;
			HidD_GetAttributes(handle_, &attr);

			//�f�o�C�X��DualShock��ID�ƈ�v���邩�𒲂ׂ�A��v���Ȃ���Ύ���HID�@��ōČ���
			if (attr.VendorID != 0x054C || attr.ProductID != 0x05C4) {
				CloseHandle(handle_);
				continue;
			}
			PHIDP_PREPARSED_DATA ppd;
			HidD_GetPreparsedData(handle_, &ppd);
			if (!HidP_GetCaps(ppd, &caps_)) {
				CloseHandle(handle_);
				break;
			}
			dataSize_ = caps_.InputReportByteLength;
			WCHAR m_DS4Serial[127];
			if (dataSize_ > 64) {
				isbluetooth_ = 2;
				if (!HidD_GetSerialNumberString(handle_, m_DS4Serial, sizeof(m_DS4Serial)))
					continue;
			}
			currentData_ = (byte*)malloc(sizeof(byte)*dataSize_);
			memset(currentData_, 0, dataSize_);

			//�����܂ŗ����琬���Ȃ̂�true��Ԃ�
			return true;
		}
		//��Ő����o���Ȃ���������false
		return false;
	}
	//ReadFile��Bluetooth���Ɛ���ɍs���Ȃ����߁A�����ŉi���ɑҋ@�������Đ�ɐi�߂Ȃ���肠��(USB�ł̗L���ڑ��ɂ��g�p���鎖)
	void Update() {
		//�ǂݍ��݊����f�[�^��
		DWORD readBytes;
		//�ǂݍ��݂��s��(�ǂݍ��݃f�[�^��currentData_�Ɋi�[�����)
		if (ReadFile(handle_, currentData_, dataSize_, &readBytes, NULL) == TRUE) {
			Update_Angle();
			Update_Acceleration();
		}
		else {
			OutputDebugString("���s");
			OutputDebugString("\n");
		}
		//ReadFile(handle_, &currentData_, caps_.InputReportByteLength, &readBytes, NULL);


	}
	//�R���g���[���f�[�^�̕ێ����I������
	void Clear() {
		CloseHandle(handle_);
	}

	//�R���g���[����z,x���̌X�����擾����(x�ɂ͍��E�̌X��������E�����Ay�ɂ͑O��̌X�������艜�����Ƃ���)
	Vector2 GetAngle() const {
		return angle_;
	}

	//�R���g���[����x,y,z���̌X�����擾����(x,y�͂ǂ����-180�`0,0�`180�̊p�x�������Az��-90�`90�͈̔͂ŁA�\�Ȃ琳�A���Ȃ畉������)
	Vector3 GetAngle3D() const {
		return angle3d_;
	}

private:
	//�����x����A�ŏ��̊p�x�����߂�
	void First_Angle() {
		DWORD readBytes;
		if (ReadFile(handle_, currentData_, dataSize_, &readBytes, NULL) == TRUE) {
			//�����Ŋp�x�����߂�
		}
		else {
			acceleration_ = Vector3::Zero;
		}
	}
	//�p�x���o
	void Update_Angle() {
		//�Z���T�[�̒l���擾
		int x = currentData_[20 + isbluetooth_];
		int y = currentData_[24 + isbluetooth_];
		int z = currentData_[22 + isbluetooth_];


		//�X�����������ꍇ�͒l�𖳎�
		if (x < 3 || x>254) {
			x = 1;
		}
		if (y < 3 || y>254) {
			y = 1;
		}
		//200�ȏ�̏ꍇ�̓R���g���[�������������Ă���
		if (z >= 128) {
			z = 0;
		}

		//�R���g���[���𐨂��ǂ��U�����ۂȂǂɔ͈͊O�̐��l���o�邽�߁A���̏ꍇ�͕␳
		if (x >= 129 && x < 225)x = 225;
		if (x>33 && x < 129)x = 33;
		//225�ȏ�̐��l��0��ɂ���(�͈͂�225�`255,0�`33)
		x += 31;
		x %= 256;
		//�����܂łŌX�������Ȃ�64,�E�Ȃ�0�ɂȂ�
		//-32�`32�͈̔͂ɕϊ�
		x -= 32;
		//�v�Z���ʂ��p�x�ɑ������(�E�����ɕϊ�)
		angle_.x = -((float)x / 32.f);

		//�R���g���[���𐨂��ǂ��U�����ۂȂǂɔ͈͊O�̐��l���o�邽�߁A���̏ꍇ�͕␳
		if (y >= 127 && y < 223)y = 223;
		if (y>31 && y < 127)y = 31;
		//x�Ɠ����菇�Ōv�Z����(y�͒l��223�`255,0�`31�Ȃ��߁A���Z�l�����炷)
		y += 33;
		y %= 256;
		y -= 32;
		angle_.y = ((float)y / 32.f);
	}
	void Update_Gyro() {
		byte x[]{ currentData_[13 + isbluetooth_] ,currentData_[14 + isbluetooth_] };
		byte y[]{ currentData_[17 + isbluetooth_] ,currentData_[18 + isbluetooth_] };
		byte z[]{ currentData_[15 + isbluetooth_] ,currentData_[16 + isbluetooth_] };

		int nextGyro[]{
			ByteConverter::Byte_to_Int(x, 2),
			ByteConverter::Byte_to_Int(y, 2),
			ByteConverter::Byte_to_Int(z, 2)
		};

		for (int i = 0; i < 3; i++) {
			//�����l�����Ȃ炻�̂܂�
			if (ByteConverter::ByteMaxSize(2) / 2 > nextGyro[i])continue;

			//�����l�𒴂��Ă�����}�C�i�X�̒l�ɕϊ�
			nextGyro[i] = ByteConverter::ReverseNumber(nextGyro[i], 2);
		}
		//�␳�l�̓h���t�g��ڂŌ��ēK���Ɍ��߂Ă邾���̐��Ȃ��߁A�Q�l�ɂ��Ȃ���(�ꍇ�ɂ���Ă͏�����������������)
		gyro_.x = nextGyro[0] + 1.2f;
		gyro_.y = nextGyro[1] - 3.12f;
		gyro_.z = nextGyro[2] + 1.5f;
		gyroVector_.x = (nextGyro[0] + 1.2f) / (float)maxGyro;
		gyroVector_.y = (nextGyro[1] - 3.12f) / (float)maxGyro;
		gyroVector_.z = (nextGyro[2] + 1.5f) / (float)maxGyro;

		frameGyroMat_= Matrix::CreateFromAxisAngle(gyroMat_.Left(), gyroVector_.x)*Matrix::CreateFromAxisAngle(gyroMat_.Up(), gyroVector_.y)*Matrix::CreateFromAxisAngle(gyroMat_.Forward(), -gyroVector_.z);

		//gyroMat_ *= Matrix::CreateRotationX(gyroVector_.x)*Matrix::CreateRotationY(gyroVector_.y)*Matrix::CreateRotationZ(-gyroVector_.z);
		gyroMat_ *= frameGyroMat_;
		OutputDebugString("L[");
		OutputDebugString(std::to_string(gyroMat_.Left().x).c_str());
		OutputDebugString(" ,");
		OutputDebugString(std::to_string(gyroMat_.Left().y).c_str());
		OutputDebugString(" ,");
		OutputDebugString(std::to_string(gyroMat_.Left().z).c_str());
		OutputDebugString("]");
		OutputDebugString("\n");

		OutputDebugString("U[");
		OutputDebugString(std::to_string(gyroMat_.Up().x).c_str());
		OutputDebugString(" ,");
		OutputDebugString(std::to_string(gyroMat_.Up().y).c_str());
		OutputDebugString(" ,");
		OutputDebugString(std::to_string(gyroMat_.Up().z).c_str());
		OutputDebugString("]");
		OutputDebugString("\n");

		OutputDebugString("F[");
		OutputDebugString(std::to_string(gyroMat_.Forward().x).c_str());
		OutputDebugString(" ,");
		OutputDebugString(std::to_string(gyroMat_.Forward().y).c_str());
		OutputDebugString(" ,");
		OutputDebugString(std::to_string(gyroMat_.Forward().z).c_str());
		OutputDebugString("]");
		OutputDebugString("\n");
		OutputDebugString("\n");


		}
	//�����x�̍X�V
	void Update_Acceleration() {
		byte x[]{ currentData_[19 + isbluetooth_] ,currentData_[20 + isbluetooth_] };
		byte y[]{ currentData_[23 + isbluetooth_] ,currentData_[24 + isbluetooth_] };
		byte z[]{ currentData_[21 + isbluetooth_] ,currentData_[22 + isbluetooth_] };

		int nextAcceleration[]{
			ByteConverter::Byte_to_Int(x, 2),
			ByteConverter::Byte_to_Int(y, 2),
			ByteConverter::Byte_to_Int(z, 2)
		};

		for (int i = 0; i < 3; i++) {
			//�����l�����Ȃ炻�̂܂�
			if (ByteConverter::ByteMaxSize(2) / 2 > nextAcceleration[i])continue;

			//�����l�𒴂��Ă�����}�C�i�X�̒l�ɕϊ�
			nextAcceleration[i] = ByteConverter::ReverseNumber(nextAcceleration[i], 2);
		}
		acceleration_.x = nextAcceleration[0];
		acceleration_.y = nextAcceleration[1];
		acceleration_.z = nextAcceleration[2];


		Update_Gyro();
		//��������X���̌v�Z(�����x�݂̂Ɉˑ������v�Z���s���Ă���)
		//�����肽���p�x�v�Z�̕��@
		//1)Initialize���ɉ����x����Ƃ��������p�x��ݒ�
		//2)��{�I�ɂ̓W���C���ɂ��p�x���X�V���Ă���
		//3)����10�t���[�����x�̉����x�z������
		//4)�����x�z��̍ő�l�ƍŒ�l�̍�������Ȃ��������ꍇ�Ɍ���A���ɋL�q���������x�ɂ��p�x�v�Z�ŏ㏑������

		SelectAngle();
	}
	void SelectAngle() {
		Vector3 nextAngle = Vector3::Zero;
		////z�����Ȃ�\�̌v�Z
		//if (acceleration_.z >= 0) {
		//	//x�͐��̒l�̂��傫�����畉�ɃY����
		//	nextAngle.x = ((acceleration_.x - 256.f) / maxAcceleration) * 90;
		//	//y�͕��̒l�̂��傫�����琳�ɃY����
		//	nextAngle.y = ((acceleration_.y + 256.f) / maxAcceleration) * 90;
		//}
		////z�����Ȃ痠�̌v�Z
		//else {
		//	//x�͐��̒l�̂��傫�����畉�ɃY����
		//	nextAngle.x = ((acceleration_.x - 256) / maxAcceleration) * 90;
		//	//y�͕��̒l�̂��傫�����琳�ɃY����
		//	nextAngle.y = ((acceleration_.y + 256) / maxAcceleration) * 90;
		//	//���̏ꍇ��
		//	nextAngle.x = MathHelper::Sign(nextAngle.x) * 180 - nextAngle.x;
		//	nextAngle.y = MathHelper::Sign(nextAngle.y) * 180 - nextAngle.y;
		//
		//}
		//x�͐��̒l�̂��傫�����畉�ɃY����
		nextAngle.x = ((acceleration_.x - 256.f) / maxAcceleration) * 90;
		//y�͕��̒l�̂��傫�����琳�ɃY����
		nextAngle.y = ((acceleration_.y + 256.f) / maxAcceleration) * 90;

		//z�͂��̂܂�
		nextAngle.z = ((acceleration_.z) / maxAcceleration) * 90;

		accelMat_ = Matrix::Identity*Matrix::CreateRotationX(nextAngle.x)*Matrix::CreateRotationY(nextAngle.y)*Matrix::CreateRotationZ(nextAngle.z);
		
		/*
		OutputDebugString("L[");
		OutputDebugString(std::to_string(accelMat_.Left().x).c_str());
		OutputDebugString(" ,");
		OutputDebugString(std::to_string(accelMat_.Left().y).c_str());
		OutputDebugString(" ,");
		OutputDebugString(std::to_string(accelMat_.Left().z).c_str());
		OutputDebugString("]");
		OutputDebugString("\n");

		OutputDebugString("U[");
		OutputDebugString(std::to_string(accelMat_.Up().x).c_str());
		OutputDebugString(" ,");
		OutputDebugString(std::to_string(accelMat_.Up().y).c_str());
		OutputDebugString(" ,");
		OutputDebugString(std::to_string(accelMat_.Up().z).c_str());
		OutputDebugString("]");
		OutputDebugString("\n");

		OutputDebugString("F[");
		OutputDebugString(std::to_string(accelMat_.Forward().x).c_str());
		OutputDebugString(" ,");
		OutputDebugString(std::to_string(accelMat_.Forward().y).c_str());
		OutputDebugString(" ,");
		OutputDebugString(std::to_string(accelMat_.Forward().z).c_str());
		OutputDebugString("]");
		OutputDebugString("\n");
		OutputDebugString("\n");
		*/	

		//x,y,z���ꂼ��̉����x���X�g���X�V
		xAngleList_.push_front(nextAngle.x);
		yAngleList_.push_front(nextAngle.y);
		zAngleList_.push_front(nextAngle.z);

		xAngleList_.pop_back();
		yAngleList_.pop_back();
		zAngleList_.pop_back();


		//x,y,z���ꂼ��A�����x�̕ϓ����������ꍇ�͉����x�̒l���p�x�ɂ���A�傫���ꍇ�̓W���C���̌X�������Z����
		auto x = std::minmax_element(xAngleList_.begin(), xAngleList_.end());
		if (std::abs(*x.first - *x.second) <= 10.0f)angle3d_.x = nextAngle.x;
		else {
			angle3d_.x += gyroVector_.x;
		}
		auto y = std::minmax_element(yAngleList_.begin(), yAngleList_.end());
		if (std::abs(*y.first - *y.second) <= 10.0f)angle3d_.y = nextAngle.y;
		else {
			angle3d_.y += gyroVector_.y;
		}
		auto z = std::minmax_element(zAngleList_.begin(), zAngleList_.end());
		if (std::abs(*z.first - *z.second) <= 10.0f)angle3d_.z = nextAngle.z;
		else {
			angle3d_.z += gyroVector_.z;
		}

		//OutputDebugString("x:");
		//OutputDebugString(std::to_string(nextAngle.x).c_str());
		//OutputDebugString(" y:");
		//OutputDebugString(std::to_string(nextAngle.y).c_str());
		//OutputDebugString(" z:");
		//OutputDebugString(std::to_string(nextAngle.z).c_str());
		//OutputDebugString("\n");
		
		//���݂�gyro�̒l���������@�\���ĂȂ��A�R���g���[�������邮��񂷂ƒl�����ł�
	}

private:
	//�R���g���[���̃n���h��
	HANDLE handle_{};
	//�Ώ�HID�̑���M�T�C�Y��������
	HIDP_CAPS	caps_{};
	//�R���g���[���̓��̓f�[�^�z��
	byte *currentData_;
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

