#pragma once
#include "../World/IWorld.h"
#include "../Math/Math.h"
#include "../UI/UI.h"
#include "../Graphic/Sprite.h"
#include "../Actor/Player/Player.h"
#include "SpecifiedDrawPtr.h"
#include "../Scene/GamePlayState.h"
#include <vector>
#include <map>

class Player;
class SpecifiedStepManager  : public UI{

	enum stepState {
		QUATER = 1,
		HALF = 2,
		TURN = 3,
		SPIN = 4,

		NONE,
	};

public:
	SpecifiedStepManager() = default;
	SpecifiedStepManager(IWorld * world);
	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw() const override;
	virtual void Notify(Notification type, void* param = nullptr);
	virtual void pause() override;
	virtual void restart() override;

	int stepMatching(int stepType);
	
private:
	IWorld * world_;
	Vector2 cursorPos_;
	Vector2 basePos_;
	float Xpos;
	float alpha_;
	std::shared_ptr<Player> target_;
	bool IsPause{ false };
	bool IsDeadEnd{ false };
	bool IsPad_{ false };
	int reciveStep_;
	float timer_;
	//表示するステップ
	std::vector<SpecifiedDrawPtr> stepdraw_;
	GamePlayState state_;
};