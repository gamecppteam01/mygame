#pragma once
#include<vector>
#include<memory>
#include<functional>
#include"../Math/Vector3.h"

class Actor;
class IWorld;
class RoundCamera {
public:
	enum class State {
		Start,
		Focus,
		Move,
		Return,
		End
	};
public:
	RoundCamera(IWorld* world);

	void init();

	// 更新処理
	void onUpdate(float deltaTime);

	bool isEnd()const { return isEnd_; }

	State currentState()const { return state_; }

	Vector3 getCurrentTargetPos()const;
private:
	void Start(float deltaTime);
	void Focus(float deltaTime);
	void Move(float deltaTime);
	void Return(float deltaTime);
	void End(float deltaTime);

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

	Vector3 firstPos_;//1個目の場所
	Vector3 outVector_{ 0.0f,50.0f,-60.0f };
	bool isEnd_{ true };

	std::function<void()> func_{};
};