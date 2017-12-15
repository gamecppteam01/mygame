#pragma once
#include<list>
#include<vector>

enum class Player_Animation;

//‘JˆÚ‚ª—LŒø‚©‚ð”»•Ê
class CheckStepTask {
public:
	CheckStepTask();
	~CheckStepTask();
	void initialize();
	void setInputLimit(std::list<Player_Animation> animation);
	void setInputRelease(std::list<Player_Animation> animation);
	//true‚È‚ç—LŒø
	bool operator ()(const Player_Animation& anim);

private:
	int currentCheckKey_;
	std::vector<std::list<Player_Animation>> lockList_;
	std::vector<std::list<Player_Animation>> releaseList_;
};