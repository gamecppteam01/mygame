#pragma once
#include "../../Actor/Player/Player.h"
#include "../../World/IWorld.h"
#include <memory>

class Player;
class Step_NowEffect {
	Step_NowEffect(IWorld* world);
	~Step_NowEffect(){}
	void Initialize();
	void Update(float deltaTime);
	void Draw() const;
	void End();

private:
	std::shared_ptr<Player> player_;
	IWorld* world_;
	Vector3 playerPos_;
};