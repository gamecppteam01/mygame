#include "DualShock4Manager.h"
#include<algorithm>

//DualShock4コントローラを認識する(成功したらtrueを返す)

DualShock4Manager::DualShock4Manager() : dataSize_(0) {
	xAngleList_.resize(10, 0.0f);
	yAngleList_.resize(10, 0.0f);
	zAngleList_.resize(10, 0.0f);

	Initialize();
}

DualShock4Manager::~DualShock4Manager() {
	free(currentData_);
	free(previousData_);
}

DualShock4Manager & DualShock4Manager::GetInstance() {
	static DualShock4Manager manager_;
	return manager_;
}

bool DualShock4Manager::Initialize() {
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
		previousData_ = (byte*)malloc(sizeof(byte)*dataSize_);
		memset(previousData_, 0, dataSize_);

		//ここまで来たら成功なのでtrueを返す
		return true;
	}
	//上で成功出来なかったためfalse
	return false;
}

//ReadFileがBluetoothだと正常に行えないため、そこで永遠に待機し続けて先に進めない問題あり(USBでの有線接続により使用する事)

void DualShock4Manager::Update() {
	//読み込み完了データ数
	DWORD readBytes;
	
	//1つ前のデータに書き込む
	memcpy(previousData_, currentData_, dataSize_);
	//読み込みを行う(読み込みデータはcurrentData_に格納される)
	if (ReadFile(handle_, currentData_, dataSize_, &readBytes, NULL) == TRUE) {
		Update_Angle();
		Update_Acceleration();
	}
	else {
		//OutputDebugString("失敗");
		//OutputDebugString("\n");
	}
	//ReadFile(handle_, &currentData_, caps_.InputReportByteLength, &readBytes, NULL);


}

//コントローラデータの保持を終了する

void DualShock4Manager::Clear() {
	CloseHandle(handle_);
}

//コントローラのz,x軸の傾きを取得する(xには左右の傾きが入り右が正、yには前後の傾きが入り奥が正とする)

Vector2 DualShock4Manager::GetAngle() const {
	return angle_;
}

//コントローラのx,y,z軸の傾きを取得する(x,yはどちらも-180～0,0～180の角度情報を持つ、zは-90～90の範囲で、表なら正、裏なら負を持つ)

Vector3 DualShock4Manager::GetAngle3D() const {
	return angle3d_;
}

Vector3 DualShock4Manager::GetGyroVector() const {
	return gyroVector_;
}

byte DualShock4Manager::GetByte(int key) const {
	if (dataSize_ == 0)return 0;
	return currentData_[key + isbluetooth_];
}

byte DualShock4Manager::GetPrevByte(int key) const
{
	if (dataSize_ == 0)return 0;
	return previousData_[key + isbluetooth_];
}

//加速度から、最初の角度を求める

void DualShock4Manager::First_Angle() {
	DWORD readBytes;
	if (ReadFile(handle_, currentData_, dataSize_, &readBytes, NULL) == TRUE) {
		//ここで角度を求める
	}
	else {
		acceleration_ = Vector3::Zero;
	}
}

//角度検出

void DualShock4Manager::Update_Angle() {
	//センサーの値を取得
	int x = currentData_[20 + isbluetooth_];
	int y = currentData_[24 + isbluetooth_];
	int z = currentData_[22 + isbluetooth_];


	//傾きが小さい場合は値を無視
	if (x < 3 || x>254) {
		x = 1;
	}
	if (y < 3 || y>254) {
		y = 1;
	}
	//200以上の場合はコントローラが裏を向いている
	if (z >= 128) {
		z = 0;
	}

	//コントローラを勢い良く振った際などに範囲外の数値が出るため、その場合は補正
	if (x >= 129 && x < 225)x = 225;
	if (x>33 && x < 129)x = 33;
	//225以上の数値を0基準にする(範囲は225～255,0～33)
	x += 31;
	x %= 256;
	//ここまでで傾きが左なら64,右なら0になる
	//-32～32の範囲に変換
	x -= 32;
	//計算結果を角度に代入する(右が正に変換)
	angle_.x = -((float)x / 32.f);

	//コントローラを勢い良く振った際などに範囲外の数値が出るため、その場合は補正
	if (y >= 127 && y < 223)y = 223;
	if (y>31 && y < 127)y = 31;
	//xと同じ手順で計算する(yは値が223～255,0～31なため、加算値をずらす)
	y += 33;
	y %= 256;
	y -= 32;
	angle_.y = ((float)y / 32.f);
}

void DualShock4Manager::Update_Gyro() {
	byte x[]{ currentData_[13 + isbluetooth_] ,currentData_[14 + isbluetooth_] };
	byte y[]{ currentData_[17 + isbluetooth_] ,currentData_[18 + isbluetooth_] };
	byte z[]{ currentData_[15 + isbluetooth_] ,currentData_[16 + isbluetooth_] };

	int nextGyro[]{
		ByteConverter::Byte_to_Int(x, 2),
		ByteConverter::Byte_to_Int(y, 2),
		ByteConverter::Byte_to_Int(z, 2)
	};

	for (int i = 0; i < 3; i++) {
		//中央値未満ならそのまま
		if (ByteConverter::ByteMaxSize(2) / 2 > nextGyro[i])continue;

		//中央値を超えていたらマイナスの値に変換
		nextGyro[i] = ByteConverter::ReverseNumber(nextGyro[i], 2);
	}
	//補正値はドリフトを目で見て適当に決めてるだけの数なため、参考にしない事(場合によっては消した方がいいかも)
	gyro_.x = nextGyro[0] + 1.2f;
	gyro_.y = nextGyro[1] - 3.12f;
	gyro_.z = nextGyro[2] + 1.5f;
	gyroVector_.x = (nextGyro[0] + 1.2f) / (float)maxGyro;
	gyroVector_.y = (nextGyro[1] - 3.12f) / (float)maxGyro;
	gyroVector_.z = (nextGyro[2] + 1.5f) / (float)maxGyro;

	frameGyroMat_ = Matrix::CreateFromAxisAngle(gyroMat_.Left(), gyroVector_.x)*Matrix::CreateFromAxisAngle(gyroMat_.Up(), gyroVector_.y)*Matrix::CreateFromAxisAngle(gyroMat_.Forward(), -gyroVector_.z);

	//gyroMat_ *= Matrix::CreateRotationX(gyroVector_.x)*Matrix::CreateRotationY(gyroVector_.y)*Matrix::CreateRotationZ(-gyroVector_.z);
	gyroMat_ *= frameGyroMat_;

	/*
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
	*/

}

//加速度の更新

void DualShock4Manager::Update_Acceleration() {
	byte x[]{ currentData_[19 + isbluetooth_] ,currentData_[20 + isbluetooth_] };
	byte y[]{ currentData_[23 + isbluetooth_] ,currentData_[24 + isbluetooth_] };
	byte z[]{ currentData_[21 + isbluetooth_] ,currentData_[22 + isbluetooth_] };

	int nextAcceleration[]{
		ByteConverter::Byte_to_Int(x, 2),
		ByteConverter::Byte_to_Int(y, 2),
		ByteConverter::Byte_to_Int(z, 2)
	};

	for (int i = 0; i < 3; i++) {
		//中央値未満ならそのまま
		if (ByteConverter::ByteMaxSize(2) / 2 > nextAcceleration[i])continue;

		//中央値を超えていたらマイナスの値に変換
		nextAcceleration[i] = ByteConverter::ReverseNumber(nextAcceleration[i], 2);
	}
	acceleration_.x = nextAcceleration[0];
	acceleration_.y = nextAcceleration[1];
	acceleration_.z = nextAcceleration[2];


	Update_Gyro();
	//ここから傾きの計算(加速度のみに依存した計算を行っている)
	//今後やりたい角度計算の方法
	//1)Initialize時に加速度を基準とした初期角度を設定
	//2)基本的にはジャイロにより角度を更新していく
	//3)直近10フレーム程度の加速度配列を作る
	//4)加速度配列の最大値と最低値の差が限りなく小さい場合に限り、下に記述した加速度による角度計算で上書きする

	SelectAngle();
}

void DualShock4Manager::SelectAngle() {
	Vector3 nextAngle = Vector3::Zero;
	////zが正なら表の計算
	//if (acceleration_.z >= 0) {
	//	//xは正の値のが大きいから負にズラす
	//	nextAngle.x = ((acceleration_.x - 256.f) / maxAcceleration) * 90;
	//	//yは負の値のが大きいから正にズラす
	//	nextAngle.y = ((acceleration_.y + 256.f) / maxAcceleration) * 90;
	//}
	////zが負なら裏の計算
	//else {
	//	//xは正の値のが大きいから負にズラす
	//	nextAngle.x = ((acceleration_.x - 256) / maxAcceleration) * 90;
	//	//yは負の値のが大きいから正にズラす
	//	nextAngle.y = ((acceleration_.y + 256) / maxAcceleration) * 90;
	//	//負の場合は
	//	nextAngle.x = MathHelper::Sign(nextAngle.x) * 180 - nextAngle.x;
	//	nextAngle.y = MathHelper::Sign(nextAngle.y) * 180 - nextAngle.y;
	//
	//}
	//xは正の値のが大きいから負にズラす
	nextAngle.x = ((acceleration_.x - 256.f) / maxAcceleration) * 90;
	//yは負の値のが大きいから正にズラす
	nextAngle.y = ((acceleration_.y + 256.f) / maxAcceleration) * 90;

	//zはそのまま
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

	//x,y,zそれぞれの加速度リストを更新
	xAngleList_.push_front(nextAngle.x);
	yAngleList_.push_front(nextAngle.y);
	zAngleList_.push_front(nextAngle.z);

	xAngleList_.pop_back();
	yAngleList_.pop_back();
	zAngleList_.pop_back();


	//x,y,zそれぞれ、加速度の変動が小さい場合は加速度の値を角度にする、大きい場合はジャイロの傾きを加算する
	auto x = std::minmax_element(xAngleList_.begin(), xAngleList_.end());
	if (std::abs(*x.first - *x.second) <= 10.0f)angle3d_.x = nextAngle.x;
	else {
		angle3d_.x += gyroVector_.y;
		//angle3d_.x = MathHelper::Sign(angle3d_.x + gyroVector_.x)*fmodf(std::abs(angle3d_.x + gyroVector_.x), 180.0f);
	}
	auto y = std::minmax_element(yAngleList_.begin(), yAngleList_.end());
	if (std::abs(*y.first - *y.second) <= 10.0f)angle3d_.y = nextAngle.y;
	else {
		angle3d_.y -= gyroVector_.x;
		//angle3d_.y = MathHelper::Sign(angle3d_.y + gyroVector_.y)*fmodf(std::abs(angle3d_.y + gyroVector_.y),180.0f);
	}
	angle3d_.z = nextAngle.z;

	/*
	OutputDebugString("x:");
	OutputDebugString(std::to_string(angle3d_.x).c_str());
	OutputDebugString(" y:");
	OutputDebugString(std::to_string(angle3d_.y).c_str());
	OutputDebugString(" z:");
	OutputDebugString(std::to_string(angle3d_.z).c_str());
	OutputDebugString("\n");
	*/

	//現在はgyroの値が正しく機能してない、コントローラをぐるぐる回すと値が飛んでく
}
