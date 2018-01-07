#include "CheckStepTask.h"
#include"Player_Animation.h"
#include<algorithm>

CheckStepTask::CheckStepTask():currentCheckKey_(0)
{
}

CheckStepTask::~CheckStepTask()
{
	lockList_.clear();
	releaseList_.clear();
}

void CheckStepTask::initialize()
{
	lockList_.clear();
	releaseList_.clear();
	currentCheckKey_ = 0;
}

void CheckStepTask::setInputLimit(std::list<Player_Animation> animation)
{
	lockList_.emplace_back();
	lockList_.back().assign(animation.begin(), animation.end());

}

void CheckStepTask::setInputRelease(std::list<Player_Animation> animation)
{
	releaseList_.emplace_back();
	releaseList_.back().assign(animation.begin(), animation.end());
}

bool CheckStepTask::operator()(const Player_Animation & anim)
{
	if (lockList_.size() <= currentCheckKey_)return true;
	if (!releaseList_.empty()) {
		auto releaseitr = std::find(releaseList_[currentCheckKey_].begin(), releaseList_[currentCheckKey_].end(), anim);
		//‰ðœðŒ‚ð–ž‚½‚µ‚½‚ç
		if (releaseitr != releaseList_.at(currentCheckKey_).end()) {
			currentCheckKey_++;
			return true;
		}
	}
	auto lockitr = std::find(lockList_[currentCheckKey_].begin(), lockList_[currentCheckKey_].end(), anim);
	return lockitr == lockList_.at(currentCheckKey_).end();
}

bool CheckStepTask::isEndCheck()
{
	return lockList_.size() <= currentCheckKey_;
}
