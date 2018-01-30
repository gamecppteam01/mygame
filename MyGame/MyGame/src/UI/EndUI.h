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
	TempoManager* tempoManager_;
	float time_;
	Vector2 scale_{20.0f,20.0f};
};