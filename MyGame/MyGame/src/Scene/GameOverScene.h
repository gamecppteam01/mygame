#pragma once
#include "Scene.h"

class GameOverScene : public Scene {
public:
	GameOverScene();
	~GameOverScene() override;
	void start() override;
	void update(float detlaTime) override;
	void draw() const;
	void end() override;

private:


};