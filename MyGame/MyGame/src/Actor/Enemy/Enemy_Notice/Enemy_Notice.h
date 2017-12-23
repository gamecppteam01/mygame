#pragma once

#include"../BaseEnemy.h"
#include"../../../ScoreManager/ScoreData.h"

class Enemy_Notice : public BaseEnemy{
private:
	enum Notice_State {
		Normal,
		Steal,
	};
public:
	Enemy_Notice();
	//�R���X�g���N�^
	Enemy_Notice(IWorld* world, const std::string& name, const Vector3& position, int playerNumber, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f));
	
	virtual std::shared_ptr<BaseEnemy> Create(IWorld* world, const Vector3& position, int playerNumber);

	// ���b�Z�[�W����
	virtual void onMessage(EventMessage message, void* param) override;
private:
	//�X�e�b�v�ʒm���̏���
	virtual void JustStep()override;

	virtual void updateNormal(float deltaTime) override;
	virtual void updateFever(float deltaTime) override;

	virtual void to_Normal() override;
	virtual void to_Fever() override;
private:
	int getNearestPoint(const Vector3& position);

	//���̖ړI�n��ݒ肷��
	void setNextPosition();
private:
	//�X�e�C�g
	Notice_State state_;
	//���̃|�C���g
	int nextPoint_;
	//���̖ړI�n
	Vector3 nextPosition_;
	//�{�[�i�X
	bool isGoBonus_{ false };
	//���C�g�̍��W
	Vector3 lightPosition_;
	//�X�e�b�v������m��
	int probability_{ 4 };
	//�����̃f�[�^
	ScoreData* data_;
	//�X�e�[�W����|�C���g�z��
	std::vector<Vector3> roundPoint_;
	//�X�e�b�v�t���O
	bool stepFlag_{ false };
	//�`�F���W�t���O
	bool changeFlag_{ false };

};
