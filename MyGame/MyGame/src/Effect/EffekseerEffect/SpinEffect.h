#pragma once
#include "../../World/IWorld.h"
#include "../../Math/Math.h"

class SpinEffect {
public:
	SpinEffect(IWorld * world);
	~SpinEffect() { world_ = nullptr; }
	void start();
	void update(float deltaTime);
	void draw() const;
	void end();

private:
	IWorld* world_;
	Vector3 position_;
	int effect_;
};