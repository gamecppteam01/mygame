#pragma once
#include "Scene.h"

#include"../Math/Vector3.h"
#include"../Math/Vector2.h"
#include"../Define.h"

#include<vector>
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
	//�J�[�\���ʒu
	int cursor_{ 0 };

	Vector3 scale{ Vector3::One };
	//��ʏ��
	TitleState titleState_;
	//�T�C���g
	int SinCount_;
	float temp;

private:
	//�J�[�\���̈ʒu�y�у{�^���̈ʒu���X�g
	const std::vector<std::pair<Vector2, SceneType>> cursorPoses{
		{Vector2{ 300.0f,500.f },SceneType::SCENE_GAMEPLAY},
		{Vector2{ 300.0f,600.f },SceneType::SCENE_EXIT }//�Q�[���I��(�J�ڐ�̓_�~�[)
	};
};