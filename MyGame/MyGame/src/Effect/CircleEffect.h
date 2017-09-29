#pragma once
#include"Effect.h"

class CircleEffect :public Effect {
public:
	CircleEffect(float maxSize,float effectTime);
	virtual void Update(float deltaTime) override;
	virtual void Draw(const Vector3& position)const override;

private:
	//�k���G�t�F�N�g
	void EffectUpdate(float deltaTime);
	//�g��G�t�F�N�g
	void ToHoldUpdate(float deltaTime);
	//�Œ�G�t�F�N�g
	void HoldUpdate(float deltaTime);
private:
	//�G�t�F�N�g�̍ő�T�C�Y
	float maxSize_;
	//���k�G�t�F�N�g�̎���
	float effectTime_;
	//���k�G�t�F�N�g�̍ő厞��
	float effectMaxTime_;

	//�ŏI�G�t�F�N�g�̎�������
	float holdTime_;

	//�G�t�F�N�g�̏��0����Effect->ToHold->Hold�̏���
	int effectMode_;
};