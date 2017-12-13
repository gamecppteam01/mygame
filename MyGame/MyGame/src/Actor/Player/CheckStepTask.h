#pragma once
#include<list>

enum class Player_Animation;

class CheckStepTask {
public:
	CheckStepTask();
	~CheckStepTask();
	void setInputLimit(Player_Animation animation);
	void operator ()(const Player_Animation& anim);

private:
	std::list<Player_Animation> lockList_;
};