#pragma once
#include "Scene.h"

class CreditScene : public Scene {
public:
	CreditScene();
	~CreditScene() override; 
	void start() override;
	void update(float deltaTime) override;
	void draw() const;
	void end() override;

private:


};