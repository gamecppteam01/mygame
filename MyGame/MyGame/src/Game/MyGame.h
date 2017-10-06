#pragma once
#include"Game.h"
#include"../Scene/SceneManager.h"
class MyGame :public Game {
public:
	MyGame(const Vector2& screen_size = Vector2(800, 600), float rate = 1.0f, int window = TRUE, float fps = 60.0f):Game(screen_size,rate,window,fps), sceneManager_(){
	}

	virtual void start() override {
		sceneManager_.start();

	}
	// �X�V
	virtual void update() override {
		sceneManager_.update(Time::GetInstance().deltaTime());
	}
	// �`��
	virtual void draw() override {
		sceneManager_.draw();
		EffekseerManager::GetInstance().Draw();
	}
	virtual void frameEnd()override {
		sceneManager_.checkIsEnd();
	}
	// �I��
	virtual void end() override {
		EffekseerManager::GetInstance().End();

	}
private:
	SceneManager sceneManager_;
};