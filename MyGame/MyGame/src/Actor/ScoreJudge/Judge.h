#pragma once
#include"../Actor.h"


class Judge:public Actor {
public:
	Judge(IWorld* world, const std::string& name, const Vector3& position):
		Actor(world,name,position),viewAngle_(30.0f),scoreRate_(1.2f) {
		
	}
	void onUpdate(float deltaTime)override {
		//�^�[�Q�b�g�����݂��Ȃ���΍��G����
		if (target_ == nullptr)return;
		//�^�[�Q�b�g�̈ʒu������
		Vector3 targetPos = target_->position();
		//�^�[�Q�b�g�����̃x�N�g��
		Vector3 toTarget = targetPos - position_;
		//�p�x�����߂�
		float forwardAngle = MathHelper::ACos(Vector3::Dot(rotation_.Forward().Normalize(), toTarget.Normalize()));
		float leftAngle = MathHelper::ACos(Vector3::Dot(rotation_.Left().Normalize(), toTarget.Normalize()));

		//���E�͈͓���������
		if (forwardAngle < viewAngle_) {
			//���g����]������
			float rotateAngle = 3.0f;
			//���Ȃ�E��
			if (leftAngle > 90.0f) rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -rotateAngle);
			//�E�Ȃ獶��
			else if (leftAngle < 90.0f) rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), rotateAngle);

		}

	}
private:
	//���E�͈�
	float viewAngle_;
	//�X�R�A�㏸��
	float scoreRate_;
};