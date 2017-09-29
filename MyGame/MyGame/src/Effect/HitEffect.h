#pragma once
#include"Effect.h"

class HitEffect :public Effect {
public:
	HitEffect(float maxSize,int effectCount, float effectTime);
	virtual void Update(float deltaTime) override;
	virtual void Draw(const Vector3& position)const override;

private:
	//�G�t�F�N�g�̐�����
	int effectCount_;
	//�G�t�F�N�g�̍ő�T�C�Y
	float maxSize_;
	//�G�t�F�N�g�̑S����
	float timeCount_;
	//���k�G�t�F�N�g�̍ő厞��
	float effectMaxTime_;
};