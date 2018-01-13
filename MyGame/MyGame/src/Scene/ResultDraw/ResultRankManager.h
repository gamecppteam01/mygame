#pragma once
#include<vector>

#include"../../ScoreManager/ScoreData.h"
#include"ResultCamera.h"
#include"../../Light/StandardLight.h"
#include"../../Light/LightHandle.h"
#include"../../Math/Vector2.h"
#include"../../Math/Vector3.h"
#include"../../Math/Matrix.h"
#include"ResultModelDrawer.h"

class ResultRankManager {
private:
	enum class State {
		Start,
		MoveLeft,
		CameraMove,
		CameraReturn,
		Light,
		Animation,
		EndLight,
		MoveDown,
		Next,
		End

	};
public:
	ResultRankManager();

	void init();
	
	void update(float deltaTime);

	void draw()const;

	void end();

	bool isEnd()const;
private:
	void Start(float deltaTime);
	void MoveLeft(float deltaTime);
	void CameraMove(float deltaTime);
	void CameraReturn(float deltaTime);
	void Light(float deltaTime);
	void Animation(float deltaTime);
	void EndLight(float deltaTime);
	void MoveDown(float deltaTime);
	void Next(float deltaTime);
	void End(float deltaTime);


	void changeState(State state, bool isLoop=false);


	//ライトの設定関数
	void settingLight();

private:
	int currentTarget_{ 0 };//現在の表示対象
	
	ResultCamera camera_;

	//標準ライトクラス
	StandardLight standardLight_{};
	//ライトハンドルクラス
	LightHandle lightHandle_{};

	int animType_{ 0 };

	State state_{ State::Start };

	bool isLast_{ false };

	float lerpTimer_;

	int stage_{ 1 };//ステージ番号
	int incSize_{ 0 };//ずらし値
	float timer_;
	std::vector<std::tuple<ScoreData, Vector3, Matrix, std::shared_ptr<ResultModelDrawer>, Vector2>> characters_;
};