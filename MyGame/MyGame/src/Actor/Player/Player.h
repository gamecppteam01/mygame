#pragma once
#include"../Actor.h"
#include"../../Graphic/Animation.h"

enum class EventMessage;

class Player :public Actor {
public:
	Player(IWorld* world,const std::string& name,const Vector3& position, const IBodyPtr& body);


private:
	// ƒƒbƒZ[ƒWˆ—
	virtual void onMessage(EventMessage message, void* param);
	// XV
	virtual void onUpdate(float deltaTime);
	// •`‰æ
	virtual void onDraw() const;
	// Õ“Ë‚µ‚½
	virtual void onCollide(Actor& other);

private:
	//virtual bool field() override;
private:
	//’~Ï‚·‚éˆÚ“®—Ê‚ğŠi”[‚·‚é
	Vector3 velocity_;

	float gravity_;

	Animation animation_;
};