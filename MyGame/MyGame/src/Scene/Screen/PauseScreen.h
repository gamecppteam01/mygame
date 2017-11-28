#pragma once
#include<vector>
#include<tuple>
#include"../../Math/Vector2.h"
#include"../SceneType.h"
#include"../GamePlayState.h"

enum GamePlayState;

class PauseScreen{
public:
	PauseScreen();

	void initialize();
	void start();
	//�|�[�Y��ʂ̍X�V�Ǝ���J�ڃV�[���̎w����s��(0=�J�ڂ��Ȃ� 1=�J�ڂ��� 2=��Ԃ�ς���)
	int update(float deltaTime,SceneType& type, GamePlayState& state);
	void draw()const;

private:
	//�J�[�\���^�[�Q�b�g
	int cursor_{ 0 };
	int sinCount_{ 0 };
	//�J�[�\���̈ʒu�y�у{�^���̈ʒu���X�g
	const std::vector<std::tuple<Vector2, SceneType,GamePlayState>> cursorPoses{
		std::make_tuple( Vector2{ 450.0f,400.f },SceneType::SCENE_EXIT,GamePlayState::Play ),
		std::make_tuple( Vector2{ 450.0f,525.f },SceneType::SCENE_EXIT,GamePlayState::Reload ),
		std::make_tuple( Vector2{ 450.0f,650.f },SceneType::SCENE_TITLE,GamePlayState::Pause )
	};

};