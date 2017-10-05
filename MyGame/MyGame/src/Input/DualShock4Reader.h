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
	//DualShock4コントローラを認識する(成功したらtrueを返す)
	bool Initialize() {
		//USB接続機器のIDを取得
		GUID	hidGuid;
		HidD_GetHidGuid(&hidGuid);
		//デバイス一覧を作成
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
			//HID機器の周回が終了したらループを離脱する
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
			//デバイスのデータを取得する
			handle_.back() = CreateFile(dev_det->DevicePath, GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
			if (handle_.back() == INVALID_HANDLE_VALUE) { continue; }

			HIDD_ATTRIBUTES attr;
			HidD_GetAttributes(handle_.back(), &attr);

			//デバイスがDualShockのIDと一致するかを調べる、一致しなければ次のHID機器で再検索
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
		//上で成功出来なかったためfalse
		return handle_.size()>0;
	}
	void Update() {
		//読み込み完了データ数
		DWORD readBytes;
		for (int i = 0; i < handle_.size(); i++) {
			//読み込みを行う(読み込みデータはcurrentData_に格納される)
			if (ReadFile(handle_[i], currentData_[i], dataSize_[i], &readBytes, NULL) == TRUE) {
			}
			else {
				OutputDebugString("失敗");
				OutputDebugString("\n");
			}
		}
	}
private:
	//コントローラのハンドル
	std::vector<HANDLE> handle_;
	//対象HIDの送受信サイズ等を持つ
	std::vector<HIDP_CAPS>	caps_;
	//コントローラの入力データ配列
	std::vector<byte*> currentData_;
	std::vector<DWORD> dataSize_;

	//Bluetoothの時のデータズレを解消する値、Bluetoothなら2,有線なら0(Bluetoothだとデータが2ズレるっぽい･･･?)
	std::vector<int> isbluetooth_;

};