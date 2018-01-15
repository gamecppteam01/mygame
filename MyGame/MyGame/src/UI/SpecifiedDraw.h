#pragma once
#include "../Graphic/Sprite.h"
#include "../Math/Math.h"
#include "UI.h"
#include "SpecifiedDrawPtr.h"
#include "../Actor/Player/Player.h"
#include <vector>
#include <map>
#include <list>

class Player;

class SpecifiedDraw : public UI{
public:

	SpecifiedDraw( const SPRITE_ID& id, const Vector2& position);
	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw() const override;

	void IsStart();
	SPRITE_ID getid() const;
	bool getIsDead() const;
	bool getIsStart() const;
	void addPosition(const Vector2& pos);
	int getPos();
	Vector2 getPosition() const;

private:
	SPRITE_ID id_;
	Vector2 position_;
	bool IsDead_{ false };
	bool IsStart_{ false };
	float timer_{ 0.0f };
	float pos;
	float alpha_;
	std::shared_ptr<Player> player_;
};