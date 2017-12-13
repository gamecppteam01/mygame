#include "CheckStepTask.h"
#include"Player_Animation.h"
#include<algorithm>

CheckStepTask::CheckStepTask()
{
}

CheckStepTask::~CheckStepTask()
{
}

void CheckStepTask::setInputLimit(Player_Animation animation)
{
	lockList_.push_back(animation);

}

void CheckStepTask::operator()(const Player_Animation & anim)
{
	//std::find(lockList_.begin(), lockList_.end(), [anim](Player_Animation& animation) {return animation == anim; }
}
