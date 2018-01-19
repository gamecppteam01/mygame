#include "ShowRankUI.h"
#include "../ScoreManager/ScoreManager.h"

class Player;
ShowRankUI::ShowRankUI(IWorld * world)
	 : world_(world)
{
	initialize();
}

void ShowRankUI::initialize()
{
	//id_ = SPRITE_ID::RANK_ONE_SPRITE;
	position_ = Vector3::Zero;

}

void ShowRankUI::update(float deltaTime)
{
	auto target_ = world_->findActor("Player");

	std::shared_ptr<Player> player = std::static_pointer_cast<Player>(target_);
	//score_ = &world_->getCanChangedScoreManager().getFirst();

	//position_ = score_->target_.lock()->position() + Vector3::Up * 3;

	position_ = player->getCenterPos() + Vector3(0.0f,25.0f,0.0f);
}

void ShowRankUI::draw() const
{
	DrawSprite3D(position_, 12.5f, SPRITE_ID::RANK_ONE_SPRITE);
}
