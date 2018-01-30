#pragma once

#include"../BaseEnemy.h"
#include"../../../ScoreManager/ScoreData.h"

class Enemy_Round:public BaseEnemy {
public:
	Enemy_Round();
	Enemy_Round(IWorld* world, const std::string& name, const Vector3& position, int playerNumber);

	virtual std::shared_ptr<BaseEnemy> Create(IWorld* world, const Vector3& position, int playerNumber)override;

	virtual void to_Normal() override;
	virtual void JustStep() override;
	virtual void updateNormal(float deltaTime) override;
	virtual void onShadowDraw()const override;
	void setNearestPoint();
	void nextPosition();
	void Step();
	//������1�ʂ����������H
	bool Distance_First();
	//������1�ʂ��ǂ����H
	bool RankedFirst();

	//�͈͓��̓G�̐�
	int Around_Enemy(float distance);

private:
	std::vector<Vector3> points_;
	//�|�C���g�L�[
	int nextKey_;
	//�X�e�b�v
	int nextStep;
	//1�ʂ�ScoreData
	ScoreData firstdata;
};