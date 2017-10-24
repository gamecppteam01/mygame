#include "ScoreMap.h"
#include"../World/IWorld.h"
#include"../Actor/Judge_NPC/Judge_NPC.h"
#include"../Judge/JudgeFunction.h"
#include<list>

ScoreMap::ScoreMap(IWorld * world):world_(world)
{
}

ScoreMap::~ScoreMap()
{
	judges_.clear();
}

void ScoreMap::initialize()
{
	points_.loopElement([](ScorePoint& s) {s.rate_ = 1.0f; });

	judges_.clear();
	std::list<ActorPtr> judges;
	world_->findActors("Judge", judges);
	for (auto& j : judges) {
		judges_.push_back(std::static_pointer_cast<Judge_NPC>(j));
	}
}

void ScoreMap::update(float deltaTime)
{

}

void ScoreMap::searchScoreRate()
{
	points_.loopElement([this](ScorePoint& s) {
		float nextRate = 1.0f;
		for (auto& j : judges_) {
			if (JudgeFunction::isInView(j->position(), s.position_, j->rotation(), j->getAngle())) {
				nextRate += 0.2f;
			}
		}
		s.rate_ = nextRate;
	}
	);
}
