#pragma once

#include"../../Math/Math.h"
#include"../../Input/DualShock4Manager.h"

class GyroRotateChecker{
public:
	GyroRotateChecker():rotate_(Vector2::Zero) {
		initialize();
	}
	//�����x�Z���T�[�̒l���g���Ċp�x������������
	void initialize() {
		Vector3 accelAngle = DualShock4Manager::GetInstance().GetAngle3D();

		rotate_.x = accelAngle.x;
		rotate_.y = accelAngle.y;
	}
	//�x�N�g�������Z����
	void update() {
		//�W���C�����痈�钼�ړI�ȉ�]�����擾����
		Vector3 rotate = DualShock4Manager::GetInstance().GetGyroVector();
		//�W���C����]�l�����݊p�x��ɕϊ���(y������]������+�ɁA��]���������������)�x�N�g�����쐬
		Vector2 rotate2d = Vector2(rotate.y, -rotate.x);
		rotate_ += rotate2d;
		OutputDebugString(std::to_string(rotate_.x).c_str());
		OutputDebugString(":");
		OutputDebugString(std::to_string(rotate_.y).c_str());
		OutputDebugString("\n");
	}
	//��]�x�N�g�����擾����
	Vector2 getRotate()const { return rotate_; }
private:
	//���݊p�x
	Vector2 rotate_;
};