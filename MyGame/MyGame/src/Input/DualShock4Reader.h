#pragma once

#include"hidsdi.h"
#include"setupapi.h"

#pragma comment(lib, "hid.lib")
#pragma comment(lib, "SetupAPI.lib") 

class DualShock4Reader {
public:
	DualShock4Reader() {
		Initialize();
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

			handle_.push_back(HANDLE());
			//�f�o�C�X�̃f�[�^���擾����
			handle_.back() = CreateFile(dev_det->DevicePath, GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
			if (handle_.back() == INVALID_HANDLE_VALUE) { continue; }

			HIDD_ATTRIBUTES attr;
			HidD_GetAttributes(handle_.back(), &attr);

			//�f�o�C�X��DualShock��ID�ƈ�v���邩�𒲂ׂ�A��v���Ȃ���Ύ���HID�@��ōČ���
			if (attr.VendorID != 0x054C || attr.ProductID != 0x05C4) {
				CloseHandle(handle_.back());
				handle_.pop_back();
				continue;
			}
			PHIDP_PREPARSED_DATA ppd;
			HidD_GetPreparsedData(handle_.back(), &ppd);
			caps_.push_back(HIDP_CAPS());
			if (!HidP_GetCaps(ppd, &caps_.back())) {
				CloseHandle(handle_.back());
				handle_.pop_back();
				caps_.pop_back();
				break;
			}
			dataSize_.push_back(caps_.back().InputReportByteLength);
			WCHAR m_DS4Serial[127];
			if (dataSize_.back() > 64) {
				isbluetooth_.push_back(2);
				if (!HidD_GetSerialNumberString(handle_.back(), m_DS4Serial, sizeof(m_DS4Serial)))
				{
					handle_.pop_back();
					caps_.pop_back();
					isbluetooth_.pop_back();
					dataSize_.pop_back();
					continue;
				}
			}
			else {
				isbluetooth_.push_back(0);
			}
			currentData_.push_back((byte*)malloc(sizeof(byte)*dataSize_.back()));
			memset(currentData_.back(), 0, dataSize_.back());

		}
		//��Ő����o���Ȃ���������false
		return handle_.size()>0;
	}
	void Update() {
		//�ǂݍ��݊����f�[�^��
		DWORD readBytes;
		for (int i = 0; i < handle_.size(); i++) {
			//�ǂݍ��݂��s��(�ǂݍ��݃f�[�^��currentData_�Ɋi�[�����)
			if (ReadFile(handle_[i], currentData_[i], dataSize_[i], &readBytes, NULL) == TRUE) {
			}
			else {
				OutputDebugString("���s");
				OutputDebugString("\n");
			}
		}
	}
private:
	//�R���g���[���̃n���h��
	std::vector<HANDLE> handle_;
	//�Ώ�HID�̑���M�T�C�Y��������
	std::vector<HIDP_CAPS>	caps_;
	//�R���g���[���̓��̓f�[�^�z��
	std::vector<byte*> currentData_;
	std::vector<DWORD> dataSize_;

	//Bluetooth�̎��̃f�[�^�Y������������l�ABluetooth�Ȃ�2,�L���Ȃ�0(Bluetooth���ƃf�[�^��2�Y������ۂ����?)
	std::vector<int> isbluetooth_;

};