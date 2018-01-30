#pragma once
#include"../Actor.h"

class TutorialPoint:public Actor {
public:
	explicit TutorialPoint(const Vector3& position);
	~TutorialPoint();

	void onDraw()const override;
	void onCollide(Actor& other)override;

private:
	int id_;
};