#pragma once

#include"../../Math/Math.h"
#include"../../Input/DualShock4Manager.h"

class GyroRotateChecker{
public:
	GyroRotateChecker():rotate_(Vector2::Zero), angle_(0.0f){
		initialize();
	}
	//�����x�Z���T�[�̒l���g���Ċp�x������������
	void initialize() {
		Vector3 accelAngle = DualShock4Manager::GetInstance().GetAngle3D();

		rotate_.x = accelAngle.x;
		rotate_.y = accelAngle.y;

		angle_ = 0.0f;
	}
	//�����x�ˑ��̌X�������Z�b�g
	void initRotate() {
		Vector3 accelAngle = DualShock4Manager::GetInstance().GetAngle3D();

		rotate_.x = accelAngle.x;
		rotate_.y = accelAngle.y;
	}
	//�W���C���Z���T�[�ɂ���]�����Z�b�g
	void initAngle() {
		angle_ = angle_-MathHelper::Sign(angle_)*360;

	}
	//�x�N�g�������Z����
	void update() {
		//�W���C�����痈�钼�ړI�ȉ�]�����擾����
		Vector3 rotate = DualShock4Manager::GetInstance().GetGyroVector();
		//�W���C����]�l�����݊p�x��ɕϊ���(y������]������+�ɁA��]���������������)�x�N�g�����쐬
		Vector2 rotate2d = Vector2(rotate.y, -rotate.x);
		rotate_ += rotate2d;

		angle_ += rotate.z;
		angle_ = std::fmodf(angle_, 360.0f);

		//OutputDebugString(std::to_string(rotate_.x).c_str());
		//OutputDebugString(":");
		//OutputDebugString(std::to_string(rotate_.y).c_str());
		//OutputDebugString("\n");
	}
	//��]�x�N�g�����擾����
	Vector2 getRotate()const { return rotate_; }
	//�R���g���[����z��������擾����
	float getAngle()const { return angle_; }
private:
	//���݊p�x
	Vector2 rotate_;
	//��]
	float angle_;
};