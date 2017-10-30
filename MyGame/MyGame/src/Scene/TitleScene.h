#pragma once
#include "Scene.h"

#include"../Math/Vector3.h"
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
	int _Counter;
	int handle;
	Vector3 scale{ Vector3::One };
};