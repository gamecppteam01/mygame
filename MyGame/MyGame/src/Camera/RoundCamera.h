#pragma once
#include<vector>
#include<memory>
#include"../Math/Vector3.h"

class Actor;
class IWorld;
class RoundCamera {
private:
	enum class State {
		Focus,
		Move,
		Return
	};
public:
	RoundCamera(IWorld* world);

	void init();

	// 更新処理
	void onUpdate(float deltaTime);

	bool isEnd()const { return isEnd_; }
private:
	void Focus(float deltaTime);
	void Move(float deltaTime);
	void Return(float deltaTime);

	void changeState(State state);
private:
	IWorld* world_;
	std::vector<std::weak_ptr<Actor>> targetList_;

	int currentTarget_{ 0 };

	float moveTimer_{ 0.0f };
	
	State state_;

	Vector3 startPosition_;//移動開始時の位置
	Vector3 position_;
	Vector3 defaultPos_;//巡回開始時の位置
	Vector3 targetVector_;//視点決定用ベクトル

	Vector3 outVector_{ 0.0f,50.0f,-60.0f };
	bool isEnd_{ true };
};