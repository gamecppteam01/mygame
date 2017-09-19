#pragma once
#include "Scene.h"


class TitleScene : public Scene {
public:
	//
	TitleScene();
	//
	~TitleScene() override;
	//
	void start() override;
	//
	void update(float deltaTime) override;
	//
	void draw() const override;
	//
	void end() override;

private:
	//
	int _counter;

};