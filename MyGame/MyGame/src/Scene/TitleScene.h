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
	//�O�i�K
	third,
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
	//1�i�K�ڂ̍X�V
	void firstUpdate();
	//2�i�K�ڂ̍X�V
	void secondUpdate(float deltaTime);
	//3�i�K�ڂ̍X�V
	void thirdUpdate(float deltaTime);
	//1�i�K�ڂ̕`��
	void firstDraw() const;
	//2�i�K�ڂ̕`��
	void secondDraw() const;
	//3�i�K�ڂ̕`��
	void thirdDraw() const;
	//�{�^���������ꂽ���H
	bool is_Triger_Chack();

private:
	//�J�[�\���ʒu
	int cursor_{ 0 };

	Vector3 scale{ Vector3::One };
	//��ʏ��
	TitleState titleState_;
	//�T�C���g
	int SinCount_;
	float temp;
	int brightCount_{ 0 };

	//�^�C�g�����S
	Vector2 logoPos_{ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 40 };
	Vector2 logoPos2_{ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 140 };
	float timer_{ 0 }, maxTimer{ 1.0f };
	//�����x
	float alpha_{ 0.0f };

	
private:
	//�J�[�\���̈ʒu�y�у{�^���̈ʒu���X�g
	const std::vector<std::pair<Vector2, SceneType>> cursorPoses{
		{ Vector2{ 450.0f,400.f },SceneType::SCENE_TUTORIAL },
		{ Vector2{ 450.0f,525.f },SceneType::SCENE_NAMING },
		{ Vector2{ 450.0f,650.f },SceneType::SCENE_EXIT }//�Q�[���I��(�J�ڐ�̓_�~�[)
	};
	//�J�[�\���̈ʒu
	const std::vector<std::pair<Vector2, bool>> cursorPoses2{
		{ Vector2{450.0f,525.0f},true},
		{ Vector2{ 450.0f,650.0f },false }
	};
};