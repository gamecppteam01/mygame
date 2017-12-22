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
		End,
	};
	enum class Miss_State {
		Start,
		Staging,
		End,
	};
public:
	StepUI(IWorld* world);
	virtual void initialize() override;
	virtual void pause() override;
	virtual void restart() override;
	virtual void update(float deltaTime) override;
	virtual void draw() const override;
	bool is_StepSuccess() const;
	void player_MissStep();

	virtual void Notify(Notification type, void* param) override;
private:
	IWorld* world_;
	std::weak_ptr<Player> player_;

	//UI�̍��W�A�g�嗦�A�����x
	Vector2 position_;
	Vector2 scale_;
	float alpha_;

	//�ėpUI�̍��W�A�g�嗦�A�����x
	Vector2 another_position_;
	Vector2 another_scale_;
	float another_alpha_;

	//�ړ����o�̍��W
	//�J�n���W
	Vector2 start_position_;
	//�I�����W
	Vector2 end_position_;

	//�ėp�J�E���g
	float count{ 0.0f };
	//�ėp���J�E���g
	float another_count{ 0.0f };
	//UI�̃X�e�[�g
	UI_State state_;
	Miss_State miss_state_;
	//UI���\������邩�H
	bool ui_Play_{ false };
	//����
	float timer_; 

	bool pause_;
};