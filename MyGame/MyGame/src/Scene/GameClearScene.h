#pragma once
#include "Scene.h"

class GameClearScene : public Scene {
public:
	GameClearScene();
	~GameClearScene() override;
	void start() override;
	void update(float deltaTime) override;
	void draw() const;
	void end() override;
		
private:


};