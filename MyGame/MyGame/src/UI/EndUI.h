#pragma once
#include "../Math/Math.h"
#include "../Graphic/Sprite.h"
#include "../UI/UI.h"
#include "../Sound/TempoManager.h"

class EndUI : public UI {
public:
	EndUI(TempoManager* tempoManager,const Vector2& position );
	void initialize() override;
	void update(float deltaTime) override;
	void draw() const override;
	bool end() const;

private:
	Vector2 position_;
	TempoManager* tempoManager_;
	float time_;
};