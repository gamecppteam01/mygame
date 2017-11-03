#pragma once
#include "../World/IWorld.h"
#include "../Math/Math.h"

class SpinEffect {
public:
	SpinEffect(IWorld * world);
	~SpinEffect(){}
	void initialize();
	void update(float deltaTime);
	void draw() const;
	void end();

private:
	IWorld* world;
	Vector3 position_;
};