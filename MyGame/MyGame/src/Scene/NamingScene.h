#pragma once
#include"Scene.h"
#include"Screen/SoftwareKeyboard.h"

class NamingScene :public Scene {
public:
	NamingScene();
	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	SoftwareKeyboard key_{};

};