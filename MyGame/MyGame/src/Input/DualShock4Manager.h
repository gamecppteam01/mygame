#include "hidsdi.h"
#include"setupapi.h"
#pragma comment(linker,"/entry:mainCRTStartup")
#pragma comment(lib, "hid.lib")
#pragma comment(lib, "SetupAPI.lib") 

#include"../Math/Math.h"
/*
DualShock4�R���g���[���̌X����(��܂���)�擾���邽�߂̃N���X
��1)���m�Ȋp�x���o���Ă���킯�ł͂Ȃ�
��2)������DualShock4�R���g���[�����ڑ������ꍇ�ɂ��Ă͍l�����Ă��Ȃ�
*/
class DualShock4Manager {
private:
	DualShock4Manager(): dataSize_(0){
		Initialize();
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

			//�Z���T�[�̒l���擾
			int x = currentData_[20 + isbluetooth_];
			int y = currentData_[24 + isbluetooth_];
			int z = currentData_[22 + isbluetooth_];

			OutputDebugString("x:");
			OutputDebugString(std::to_string(x).c_str());
			OutputDebugString(" y:");
			OutputDebugString(std::to_string(y).c_str());
			OutputDebugString(" z:");
			OutputDebugString(std::to_string(z).c_str());
			OutputDebugString("\n");

			//�X�����������ꍇ�͒l�𖳎�
			if (x < 3 || x>254) {
				x = 1;
			}
			if (y < 3 || y>254) {
				y = 1;
			}
			//200�ȏ�̏ꍇ�̓R���g���[�������������Ă���
			if (z > 29 || z>200) {
				z = 0;
			}

			//�p�x�������A�����̎��ɂ܂�ɔ͈͊O�̐��l���o�邽�߁A���̏ꍇ�͕␳
			if (x>200 && x < 225)x = 225;
			if (x>33 && x < 100)x = 33;
			//225�ȏ�̐��l��0��ɂ���(�͈͂�225�`255,0�`33)
			x += 31;
			x %= 256;
			//�����܂łŌX�������Ȃ�64,�E�Ȃ�0�ɂȂ�
			//-32�`32�͈̔͂ɕϊ�
			x -= 32;
			//�v�Z���ʂ��p�x�ɑ������(�E�����ɕϊ�)
			angle_.x = -((float)x / 32.f);

			//�p�x�������A�����̎��ɂ܂�ɔ͈͊O�̐��l���o�邽�߁A���̏ꍇ�͕␳
			if (y>200 && y < 223)y = 223;
			if (y>31 && y < 100)y = 31;
			//x�Ɠ����菇�Ōv�Z����(y�͒l��223�`255,0�`31�Ȃ��߁A���Z�l�����炷)
			y += 33;
			y %= 256;
			y -= 32;
			angle_.y = ((float)y / 32.f);

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

	//�R���g���[����z,x���̌X�����擾����ix�ɂ͍��E�̌X��������E�����Ay�ɂ͑O��̌X�������艜�����Ƃ���)
	Vector2 GetAngle() const {
		return angle_;
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
	Vector2 angle_{ Vector2::Zero };
};

