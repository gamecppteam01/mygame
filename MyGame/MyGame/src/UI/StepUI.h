#pragma once
#include"UI.h"
#include"../Actor/Player/Player.h"
#include"../World/World.h"

class StepUI : public UI {
public:
	StepUI(IWorld* world);
	void initialize() override;
	void update(float deltaTime) override;
	void draw() const override;
	bool End_time(float deltaTime);
	bool is_StepSuccess() const;

private:
	IWorld* world_;
	std::weak_ptr<Player> player_;

	//UIの座標、拡大率、透明度
	Vector2 position_;
	Vector2 scale_;
	float alpha_;

	//移動演出の座標
	//開始座標
	Vector2 start_position_;
	//終了座標
	Vector2 end_position_;

	//汎用カウント
	float count{ 0.0f };
	//汎用第二カウント
	float another_count{ 0.0f };


	int ui_State_{ 0 };
	bool ui_Play_{ false };
	float time_;
};