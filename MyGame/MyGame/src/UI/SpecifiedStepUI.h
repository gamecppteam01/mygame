#pragma once
#include "../Graphic/Sprite.h"
#include "../Math/Math.h"
#include "../Math/Easing.h"
#include "../UI/UI.h"
#include "../World/IWorld.h"
#include "../Game/ID.h"
#include "../Actor/Player/Player.h"
#include "../Math/Random.h"
#include <map>
#include <list>
#include <vector>

class Player;
//ステップの指示を出す数
static const int Directiv{ 4 };

class SpecifiedStepUI : public UI {

	enum StepState {
		QUARTER = 1,
		TURN = 3,
		HALF = 2,
		SPIN = 4,

		NONE,
	};

	enum class State {
		One,
		Two,
		Three,
		Four,
	};
public:
	SpecifiedStepUI() = default;
	explicit SpecifiedStepUI(IWorld * world);
	~SpecifiedStepUI() { }
	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw() const override;
	virtual void pause() override;
	virtual void restart() override;
	virtual void Notify(Notification type, void* param = nullptr) override;
	
	int stepMatching();

private:

private:
	IWorld * world_;

	float Ypos, QYpos{ 0.0f }, HYpos{ 0.0f }, TYpos{ 0.0f }, SYpos{ 0.0f };
	float Xpos, QXpos{ 0.0f }, HXpos{ 0.0f }, TXpos{ 0.0f }, SXpos{ 0.0f };
	
	Vector2 cursorPos_{ Vector2::Zero };
	std::map<int, SPRITE_ID> stepMap_;
	std::shared_ptr<Player> target_;
	
	StepState stepState_;
	bool pause_{ false };
	bool IsRecive{ false };
	int ReciveStep_{ 0 };
	float alpha_{ 1.0f }, alpha2_{ 1.0f }, alpha3_{ 1.0f }, alpha4_{ 1.0f };
	
	float lerpTimer_{ 0.0f };
	int count_{ 0 };
	std::vector<int> reciveList_;
	State state_;
};