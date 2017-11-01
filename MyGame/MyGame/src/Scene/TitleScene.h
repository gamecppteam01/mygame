#pragma once
#include "Scene.h"

#include"../Math/Vector3.h"

enum TitleState
{
	//�������
	first,
	//��i�K
	second,
};

class TitleScene : public Scene {
public:
	//�R���X�g���N�^
	TitleScene();
	//�f�X�g���N�^
	~TitleScene() override;
	//�J�n
	void start() override;
	//�X�V
	void update(float deltaTime) override;
	//�`��
	void draw() const override;
	//�I��
	void end() override;

private:
	//
	int Counter_;
	int handle;
	Vector3 scale{ Vector3::One };
	//��ʏ��
	TitleState titleState_;
	//�T�C���g
	int SinCount_;
	float temp;
	float Cursol_;
};