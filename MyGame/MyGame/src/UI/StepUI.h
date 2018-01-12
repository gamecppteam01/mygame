#pragma once
#include"UI.h"
#include"../Actor/Player/Player.h"
#include"../World/World.h"

class StepUI : public UI {
	enum class UI_State {
		Initialize,
		Start,
		Staging,
		Before_End,
		Miss_Start,
		Miss_Staging,
		Zero,
		End,
	};
public:
	StepUI(IWorld* world);
	virtual void initialize() override;
	virtual void pause() override;
	virtual void restart() override;
	virtual void update(float deltaTime) override;
	virtual void draw() const override;
	virtual void Notify(Notification type, void* param) override;
private:
	IWorld* world_;

	//UIの座標、拡大率、透明度
	Vector2 position_;
	Vector2 scale_;
	float alpha_;

	//汎用UIの座標、拡大率、透明度
	Vector2 another_position_;
	Vector2 another_scale_;
	float another_alpha_;

	//移動演出の座標
	//開始座標
	Vector2 start_position_;
	//終了座標
	Vector2 end_position_;

	//汎用カウント
	float count{ 0.0f };
	//汎用第二カウント
	float another_count{ 0.0f };
	//UIのステート
	UI_State state_;
	UI_State state2_;
	//UIが表示されるか？
	bool ui_Play_{ false };
	//時間
	float timer_; 

	//ポーズ判定
	bool pause_;

	//Stepの成功か失敗か
	bool Step_Success;
	bool Step_Failed;
	//Stepの種類
	int Step;
};