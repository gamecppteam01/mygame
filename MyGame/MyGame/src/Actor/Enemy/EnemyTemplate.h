#pragma once
#include"Enemy.h"
//�J�v�Z������𗘗p���Ȃ��ꍇ��BoundingCapsule��include�͕K�v�Ȃ�
#include"../Body/BoundingCapsule.h"
//�G�l�~�[�̃e���v���[�g�N���X
class EnemyTemplate :public Enemy {
public:
	//�J�v�Z������͗�A�L�����N�^�[�̑̌^�ɉ����Đݒ��ύX���鎖
	EnemyTemplate(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body= std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));

private:
	// ���b�Z�[�W����
	virtual void onMessage(EventMessage message, void* param) override;
	// �X�V
	virtual void onUpdate(float deltaTime)override;
	// �`��
	virtual void onDraw() const override;
	// �Փ˂���
	virtual void onCollide(Actor& other) override;

private:
};
