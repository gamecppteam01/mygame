#pragma once
#include "../../Graphic/EffekseerManager.h"
#include "../../World/IWorld.h"
#include"../../Math/Math.h"
#include "../../Sound/Sound.h"

class HalfEffect {
public:
	HalfEffect(IWorld * world);
	~HalfEffect() { world_ = nullptr; }
	void start();
	void update(float deltaTime);
	void draw();
	void end();

private:
	IWorld* world_;
	Vector3 position_;
	int effect_;
};