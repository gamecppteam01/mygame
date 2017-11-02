#pragma once
#include "../BaseEnemy.h"

class Enemy_Quick : public BaseEnemy {
public:
	//�R���X�g���N�^
	Enemy_Quick(IWorld* world, const std::string& name, const Vector3& position, int playerNumber, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));
	
private:
	//�X�e�b�v�ʒm���̏���
	virtual void JustStep()override;

	virtual void updateNormal(float deltaTime)override;

	virtual void to_Normal()override;
	//���G
	void searchTarget(float deltaTime);

private:
	float m_MoveSpeed{ 3.0f };
	float m_Timer;
};