#pragma once
#include "../Graphic/Sprite.h"
#include "../Math/Math.h"
#include "UI.h"
#include "SpecifiedDrawPtr.h"
#include <vector>
#include <map>
#include <list>

class SpecifiedDraw : public UI{
public:

	SpecifiedDraw( const SPRITE_ID& id, const Vector2& position);
	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw() const override;

private:
	SPRITE_ID id_;
	Vector2 position_;
	

};