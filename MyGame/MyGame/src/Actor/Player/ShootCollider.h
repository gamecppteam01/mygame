#pragma once
#include"../Actor.h"

class Player;
class ShootCollider:public Actor {
public:
	explicit ShootCollider(Player* player);

	void onUpdate(float deltaTime)override;

	void onDraw()const override;
	virtual void onCollide(Actor& other);
private:
	Player* player_;
};