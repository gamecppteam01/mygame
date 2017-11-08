#pragma once
#include"BaseEnemy.h"

class Player;
class NormalEnemy :public BaseEnemy {
public:
	NormalEnemy(IWorld* world,const std::string& name,const Vector3& position,int playerNumber,const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));

private:
	//�X�e�b�v�ʒm���̏���
	virtual void JustStep()override;

	virtual void updateNormal(float deltaTime)override;

	virtual void to_Normal()override;
private:
	int getNearestPoint(const Vector3& position);

	//���̖ړI�n��ݒ肷��
	void setNextPosition();
private:
	//���̃|�C���g
	int nextPoint_;
	//���̖ړI�n
	Vector3 nextPosition_;

	std::weak_ptr<Player> player_;
	//�{�[�i�X
	bool isGoBonus_{ false };

	//�X�e�[�W����|�C���g�z��
	std::vector<Vector3> roundPoint_;
};