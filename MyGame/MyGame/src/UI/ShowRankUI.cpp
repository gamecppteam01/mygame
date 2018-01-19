#include "ShowRankUI.h"
#include "../ScoreManager/ScoreManager.h"
#include"../Graphic/Sprite.h"

class Player;
ShowRankUI::ShowRankUI(IWorld * world)
	 : world_(world)
{
	initialize();
}

void ShowRankUI::initialize()
{
	id_ = Sprite::GetInstance().GetHandle(SPRITE_ID::RANK_ONE_SPRITE);
	position_ = Vector3::Zero;

}

void ShowRankUI::update(float deltaTime)
{
	auto target_ = world_->findActor("Player");

	std::shared_ptr<Player> player = std::static_pointer_cast<Player>(target_);
	score_ = &world_->getCanChangedScoreManager().getFirst();
	position_ = score_->target_.lock()->position() + Vector3(-20.0f, 15.0f, 0.0f);

	//position_ = player->getCenterPos() + Vector3(-10.0f,20.0f,0.0f);
}

void ShowRankUI::draw() const
{
	if (pause_ == true) return;
	
	DrawBillboard3D(VGet(position_.x, position_.y, position_.z), 0.0f, 1.0f, 30.0f, 0.0f, id_, TRUE, 0);
}

void ShowRankUI::pause()
{
	pause_ = true;
}

void ShowRankUI::restart()
{
	pause_ = false;
}
