#pragma once
#include<vector>
#include<memory>
#include<functional>
#include"../Math/Vector3.h"
#include"../Game/ID.h"

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

	void onDraw()const;
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

	float cutInTime_{ 0.0f };//カットイン用のタイマー

	float moveTimer_{ 0.0f };
	
	float cheerVolume_{ 0.0f };//歓声の音量
	
	State state_;

	Vector3 startPosition_;//移動開始時の位置
	Vector3 position_;
	Vector3 defaultPos_;//巡回開始時の位置
	Vector3 targetVector_;//視点決定用ベクトル

	Vector3 firstPos_;//1個目の場所
	Vector3 outVector_{ 0.0f,50.0f,-60.0f };
	bool isEnd_{ true };

	std::function<void()> func_{};

	std::vector<SPRITE_ID> cutin_ids_{
		SPRITE_ID::CUTIN_INTRODUCT_SPRITE,
		SPRITE_ID::CUTIN_LESSON1_SPRITE,
		SPRITE_ID::CUTIN_LESSON2_SPRITE,
		SPRITE_ID::CUTIN_LESSON3_SPRITE
	};
};