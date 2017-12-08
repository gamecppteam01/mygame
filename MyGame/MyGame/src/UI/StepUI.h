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

	//UI�̍��W�A�g�嗦�A�����x
	Vector2 position_;
	Vector2 scale_;
	float alpha_;

	//�ړ����o�̍��W
	//�J�n���W
	Vector2 start_position_;
	//�I�����W
	Vector2 end_position_;

	//�ėp�J�E���g
	float count{ 0.0f };
	//�ėp���J�E���g
	float another_count{ 0.0f };


	int ui_State_{ 0 };
	bool ui_Play_{ false };
	float time_;
};