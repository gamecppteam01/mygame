#pragma once

#include"../Math/Math.h"
#include"../Conv/ByteConverter.h"
#include"hidsdi.h"
#include"setupapi.h"
#include<list>

#pragma comment(lib, "hid.lib")
#pragma comment(lib, "SetupAPI.lib") 

/*
DualShock4コントローラの傾きを(大まかに)取得するためのクラス
注1)正確な角度を出しているわけではない
注2)複数個のDualShock4コントローラが接続される場合については考慮していない
*/
class DualShock4Manager {
	friend class TitleScene;

private:
	DualShock4Manager();
	~DualShock4Manager();
public:
	static DualShock4Manager& GetInstance();

	//DualShock4コントローラを認識する(成功したらtrueを返す)
	bool Initialize();
	//ReadFileがBluetoothだと正常に行えないため、そこで永遠に待機し続けて先に進めない問題あり(USBでの有線接続により使用する事)
	void Update();
	//コントローラデータの保持を終了する
	void Clear();

	//コントローラのz,x軸の傾きを取得する(xには左右の傾きが入り右が正、yには前後の傾きが入り奥が正とする)
	Vector2 GetAngle() const;

	//コントローラのx,y,z軸の傾きを取得する(x,yはどちらも-180～0,0～180の角度情報を持つ、zは-90～90の範囲で、表なら正、裏なら負を持つ)
	Vector3 GetAngle3D() const;
	Vector3 GetGyroVector()const;
	byte GetByte(int key)const;
	byte GetPrevByte(int key)const;
private:
	//加速度から、最初の角度を求める
	void First_Angle();
	//角度検出
	void Update_Angle();
	void Update_Gyro();
	//加速度の更新
	void Update_Acceleration();
	void SelectAngle();

private:
	//コントローラのハンドル
	HANDLE handle_{};
	//対象HIDの送受信サイズ等を持つ
	HIDP_CAPS	caps_{};
	//コントローラの入力データ配列
	byte *currentData_;
	byte *previousData_;
	DWORD dataSize_;
	//Bluetoothの時のデータズレを解消する値、Bluetoothなら2,有線なら0(Bluetoothだとデータが2ズレるっぽい･･･?)
	int isbluetooth_{ 0 };
	//xzのゲーム用角度
	Vector2 angle_{ Vector2::Zero };
	//コントローラのxyz角度
	Vector3 angle3d_{ Vector3::Zero };
	//傾きxyz
	Vector3 gyroVector_{ Vector3::Zero };
	//生の加速度
	Vector3 acceleration_{ Vector3::Zero };
	//生のジャイロ値
	Vector3 gyro_{ Vector3::Zero };

	Vector3 currentAngle_{ Vector3::Zero };
	
	Matrix accelMat_{ Matrix::Identity };
	//ジャイロ回転行列の合成値
	Matrix gyroMat_{ Matrix::Identity };
	//現フレームのジャイロ回転行列
	Matrix frameGyroMat_{ Matrix::Identity };

	std::list<float> xAngleList_;
	std::list<float> yAngleList_;
	std::list<float> zAngleList_;
private:
	//加速度センサーの傾き検出時の最大値,重力加速度もこの値と同値
	const int maxAcceleration{ 8192 };
	//加速度1当たりの加速度検出値
	const int baseAcceleration{ 836 };
	const int maxGyro{ 1024 };
};

