#pragma once
#include "../World/IWorld.h"
#include "../Math/Math.h"

class Player;

class StepEffect {
	StepEffect(IWorld* world_);
	~StepEffect(){}
	void Initialize();
	void Update(float deltaTime);
	void Draw() const;
	void End();

private:
	IWorld* world_;
	std::shared_ptr<Player> player_;
};