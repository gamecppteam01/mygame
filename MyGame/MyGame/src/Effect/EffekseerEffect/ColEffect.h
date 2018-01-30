#pragma once
#include "../../Graphic/EffekseerManager.h"
#include "../../Math/Math.h"
#include "../../World/IWorld.h"
#include "../../Actor/Player/Player.h"

class Player;

class ColEffect {
public:
	explicit ColEffect(IWorld* world);
	~ColEffect() {}
	void Initialize();
	void Update(float deltaTime);
	void Draw() const;
	void End();

private:
	IWorld* world_;
	std::shared_ptr<Player> player_;
};