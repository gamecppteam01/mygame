#pragma once
#include<list>
#include<vector>

enum class Player_Animation;

//遷移が有効かを判別
class CheckStepTask {
public:
	CheckStepTask();
	~CheckStepTask();
	void initialize();
	void setInputLimit(std::list<Player_Animation> animation);
	void setInputRelease(std::list<Player_Animation> animation);
	//trueなら有効
	bool operator ()(const Player_Animation& anim);

	bool isEndCheck();//条件を全部満たしたか
	bool isLast();//条件が後1個か

	std::list<Player_Animation> getLockList_()const;//制限リスト取得
private:
	int currentCheckKey_;
	std::vector<std::list<Player_Animation>> lockList_;
	std::vector<std::list<Player_Animation>> releaseList_;
};