#include "Camera.h"
#include "../math/MathHelper.h"
#include <DxLib.h>

// �J�����̍X�V����
void Camera::Update()
{
	SetCameraPositionAndTargetAndUpVec(
		VGet(Position.Get().x, Position.Get().y, Position.Get().z),
		VGet(Target.Get().x, Target.Get().y, Target.Get().z),
		VGet(Up.Get().x, Up.Get().y, Up.Get().z));
}

// �J�����̕`�拗����ݒ肷��i��O�`��A���`��j
void Camera::SetRange(float Near, float Far)
{
	SetCameraNearFar(Near, Far);
}

// �J�����̉�]�p�x��ݒ肷��i���W�A������]�p�x�E������]�p�x�E�P���]�p�x�j
void Camera::SetRotation(Vector3 rotate)
{
	SetCameraPositionAndAngle(
		VGet(Position.Get().x, Position.Get().y, Position.Get().z),
		rotate.x, rotate.y, rotate.z);
}

// �w�肵�����W���J�����̎��E�ɓ����Ă��邩�ۂ�
bool Camera::IsCheckView(Vector3 position)
{
	return CheckCameraViewClip(VGet(position.x, position.y, position.z));
}

bool Camera::IsCheckView(Vector3 min, Vector3 max)
{
	return CheckCameraViewClip_Box(
		VGet(min.x, min.y, min.z),
		VGet(max.x, max.y, max.z));
}

// �J�����̎���p��ݒ肷��
void Camera::SetViewAngle(float degree)
{
	SetupCamera_Perspective(MathHelper::ToRadians(degree));
}
