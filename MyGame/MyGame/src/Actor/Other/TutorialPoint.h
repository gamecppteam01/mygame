#pragma once
#include"../Actor.h"

class TutorialPoint:public Actor {
public:
	TutorialPoint(const Vector3& position);
	~TutorialPoint();

	void onDraw()const override;
	void onCollide(Actor& other)override;
};