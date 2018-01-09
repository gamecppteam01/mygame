#pragma once
#include "../World/IWorld.h"
#include "../Math/Math.h"
#include "../UI/UI.h"
#include "../Graphic/Sprite.h"
#include "../Actor/Player/Player.h"
#include "SpecifiedDrawPtr.h"
#include <vector>
#include <map>

class Player;
//�w�����o����
//static const int Directiv{ 4 };
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

private:

	int stepMatching();
	void stepRecive();

private:
	IWorld * world_;
	Vector2 cursorPos_;
	Vector2 basePos_;
	float Xpos;
	std::shared_ptr<Player> target_;
	bool IsPause{ false };
	float timer_{ 0.0f };
	std::list<int> reciveList_;
	std::map<int, SPRITE_ID> stepMap;
	int reciveStep_;
	stepState step_;
	//�\������X�e�b�v
	std::vector<SpecifiedDrawPtr> stepdraw_;
};