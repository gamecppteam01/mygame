#pragma once
#include "../../Graphic/EffekseerManager.h"
#include "../../World/IWorld.h"
#include"../../Math/Math.h"


class StepStanbyEffect {
public:
	StepStanbyEffect(IWorld * world);
	~StepStanbyEffect() { world_ = nullptr; }
	void start();
	void update(float deltaTime);
	void draw();
	void end();

private:
	IWorld* world_;
	Vector3 position_;
	int effect_;
};
