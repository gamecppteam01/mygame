#include "hidsdi.h"
#include"setupapi.h"
#pragma comment(linker,"/entry:mainCRTStartup")
#pragma comment(lib, "hid.lib")
#pragma comment(lib, "SetupAPI.lib") 

#include"../Math/Math.h"
/*
DualShock4コントローラの傾きを(大まかに)取得するためのクラス
注1)正確な角度を出しているわけではない
注2)複数個のDualShock4コントローラが接続される場合については考慮していない
*/
class DualShock4Manager {
private:
	DualShock4Manager() {
		Initialize();
	}
public:
	static DualShock4Manager& GetInstance() {
		static DualShock4Manager manager_;
		return manager_;
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

			//デバイスのデータを取得する
			handle_ = CreateFile(dev_det->DevicePath, GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
			if (handle_ == INVALID_HANDLE_VALUE) { continue; }

			HIDD_ATTRIBUTES attr;
			HidD_GetAttributes(handle_, &attr);

			//デバイスがDualShockのIDと一致するかを調べる、一致しなければ次のHID機器で再検索
			if (attr.VendorID != 0x054C || attr.ProductID != 0x05C4) {
				CloseHandle(handle_);
				continue;
			}
			PHIDP_PREPARSED_DATA ppd;
			HidD_GetPreparsedData(handle_, &ppd);
			caps_;
			if (!HidP_GetCaps(ppd, &caps_)) {
				CloseHandle(handle_);
				break;
			}

			//ここまで来たら成功なのでtrueを返す
			return true;
		}
		//上で成功出来なかったためfalse
		return false;
	}
	//ReadFileがBluetoothだと正常に行えないため、そこで永遠に待機し続けて先に進めない問題あり(USBでの有線接続により使用する事)
	void Update() {
		//読み込み完了データ数
		DWORD readBytes;

		//読み込みを行う(読み込みデータはcurrentData_に格納される)
		if (ReadFile(handle_, &currentData_, caps_.InputReportByteLength, &readBytes, NULL) == TRUE) {
			//センサーの値を取得
			int x = currentData_[20];
			int y = currentData_[24];
			int z = currentData_[22];
			//傾きが小さい場合は値を無視
			if (x < 3 || x>254) {
				x = 1;
			}
			if (y < 3 || y>254) {
				y = 1;
			}
			//200以上の場合はコントローラが裏を向いている
			if (z > 29 || z>200) {
				z = 0;
			}

			//角度が水平、垂直の時にまれに範囲外の数値が出るため、その場合は補正
			if (x>200 && x < 225)x = 225;
			if (x>33 && x < 100)x = 33;
			//225以上の数値を0基準にする(範囲は225～255,0～33)
			x += 31;
			x %= 256;
			//ここまでで傾きが左なら64,右なら0になる
			//-32～32の範囲に変換
			x -= 32;
			//計算結果を角度に代入する(右が正に変換)
			angle_.x = -((float)x / 32.f);

			//角度が水平、垂直の時にまれに範囲外の数値が出るため、その場合は補正
			if (y>200 && y < 223)y = 223;
			if (y>31 && y < 100)y = 31;
			//xと同じ手順で計算する(yは値が223～255,0～31なため、加算値をずらす)
			y += 33;
			y %= 256;
			y -= 32;
			angle_.y = ((float)y / 32.f);

		}
		//ReadFile(handle_, &currentData_, caps_.InputReportByteLength, &readBytes, NULL);


	}
	//コントローラデータの保持を終了する
	void Clear() {
		CloseHandle(handle_);
	}

	//コントローラのz,x軸の傾きを取得する（xには左右の傾きが入り右が正、yには前後の傾きが入り奥が正とする)
	Vector2 GetAngle() const {
		return angle_;
	}
private:
	//コントローラのハンドル
	HANDLE handle_{};
	//対象HIDの送受信サイズ等を持つ
	HIDP_CAPS	caps_{};
	//コントローラの入力データ配列
	byte currentData_[64]{ "\0" };
	Vector2 angle_{ Vector2::Zero };
};

