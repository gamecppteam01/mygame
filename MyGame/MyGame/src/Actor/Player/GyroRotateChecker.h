#pragma once

#include"../../Math/Math.h"
#include"../../Input/DualShock4Manager.h"

class GyroRotateChecker{
public:
	GyroRotateChecker():rotate_(Vector2::Zero), angle_(0.0f){
		initialize();
	}
	//加速度センサーの値を使って角度を初期化する
	void initialize() {
		Vector3 accelAngle = DualShock4Manager::GetInstance().GetAngle3D();

		rotate_.x = accelAngle.x;
		rotate_.y = accelAngle.y;

		angle_ = 0.0f;
	}
	//加速度依存の傾きをリセット
	void initRotate() {
		Vector3 accelAngle = DualShock4Manager::GetInstance().GetAngle3D();

		rotate_.x = accelAngle.x;
		rotate_.y = accelAngle.y;
	}
	//ジャイロセンサーによる回転をリセット
	void initAngle() {
		angle_ = angle_-MathHelper::Sign(angle_)*360;

	}
	//ベクトルを加算する
	void update() {
		//ジャイロから来る直接的な回転情報を取得する
		Vector3 rotate = DualShock4Manager::GetInstance().GetGyroVector();
		//ジャイロ回転値を現在角度基準に変換し(y方向回転を左が+に、回転を軸基準から方向基準に)ベクトルを作成
		Vector2 rotate2d = Vector2(rotate.y, -rotate.x);
		rotate_ += rotate2d;

		angle_ += rotate.z;
		angle_ = std::fmodf(angle_, 360.0f);

		//OutputDebugString(std::to_string(rotate_.x).c_str());
		//OutputDebugString(":");
		//OutputDebugString(std::to_string(rotate_.y).c_str());
		//OutputDebugString("\n");
	}
	//回転ベクトルを取得する
	Vector2 getRotate()const { return rotate_; }
	//コントローラのz軸周りを取得する
	float getAngle()const { return angle_; }
private:
	//現在角度
	Vector2 rotate_;
	//回転
	float angle_;
};