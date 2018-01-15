#pragma once
#include<list>
#include<vector>

enum class Player_Animation;

//�J�ڂ��L�����𔻕�
class CheckStepTask {
public:
	CheckStepTask();
	~CheckStepTask();
	void initialize();
	void setInputLimit(std::list<Player_Animation> animation);
	void setInputRelease(std::list<Player_Animation> animation);
	//true�Ȃ�L��
	bool operator ()(const Player_Animation& anim);

	bool isEndCheck();//������S������������
	bool isLast();//��������1��
private:
	int currentCheckKey_;
	std::vector<std::list<Player_Animation>> lockList_;
	std::vector<std::list<Player_Animation>> releaseList_;
};