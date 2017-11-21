#pragma once

#include"../BaseEnemy.h"

class Enemy_Round:public BaseEnemy {
public:
	Enemy_Round(IWorld* world, const std::string& name, const Vector3& position, int playerNumber);

	virtual void JustStep()override;
	virtual void to_Normal() override;

	virtual void updateNormal(float deltaTime) override;

	void setNearestPoint();
	void nextPosition();
private:
	std::vector<Vector3> points_;
	//�|�C���g�L�[
	int nextKey_;
	//�|�C���g�֌�������
	bool isGoPoint_{ true };
};