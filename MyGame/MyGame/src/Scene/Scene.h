#pragma once
#include"SceneType.h"

//�V�[���e���v���[�g
class Scene {
public:
	virtual ~Scene() {}

	virtual void start() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw()const = 0;
	//isEnd��true�ɂȂ�����̏���
	virtual void end() = 0;

	virtual bool isEnd() const{ return isEnd_; }

	virtual SceneType nextScene()const { return next_; }

	//���ʂ̏�����
	void baseInit() {
		isEnd_ = false;
	}

protected:
	bool isEnd_{ false };
	SceneType next_{ SceneType::SCENE_GAMEPLAY };
};