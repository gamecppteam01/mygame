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
	//ポーズ画面の更新と次回遷移シーンの指定を行う(0=遷移しない 1=遷移する 2=状態を変える)
	int update(float deltaTime,SceneType& type, GamePlayState& state);
	void draw()const;

private:
	//カーソルターゲット
	int cursor_{ 0 };
	int sinCount_{ 0 };
	//カーソルの位置及びボタンの位置リスト
	const std::vector<std::tuple<Vector2, SceneType,GamePlayState>> cursorPoses{
		std::make_tuple( Vector2{ 450.0f,400.f },SceneType::SCENE_EXIT,GamePlayState::Play ),
		std::make_tuple( Vector2{ 450.0f,525.f },SceneType::SCENE_EXIT,GamePlayState::Reload ),
		std::make_tuple( Vector2{ 450.0f,650.f },SceneType::SCENE_TITLE,GamePlayState::Pause )
	};

};