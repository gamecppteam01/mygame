#include "TutorialPoint.h"
#include"../Body/BoundingSphere.h"
#include"../Player/TutorialPlayer.h"
#include"../Player/PlayerBullet.h"

TutorialPoint::TutorialPoint(const Vector3 & position):
	Actor(nullptr,"TutorialPoint",position,std::make_shared<BoundingSphere>(0.0f,10.0f))
{
}

TutorialPoint::~TutorialPoint()
{
}

void TutorialPoint::onDraw() const
{
	body_->transform(getPose())->draw();
}

void TutorialPoint::onCollide(Actor & other)
{
	if (other.getName() == "Player") {
		static_cast<TutorialPlayer*>(&other)->hitPoint();
		dead();
	}
	if (other.getName() == "PlayerBullet") {
		static_cast<TutorialPlayer*>(static_cast<PlayerBullet*>(&other)->getCCPlayer())->hitPoint();
		dead();
	}
}
