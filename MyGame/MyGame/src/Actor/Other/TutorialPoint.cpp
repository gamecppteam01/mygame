#include "TutorialPoint.h"
#include"../Body/BoundingSphere.h"
#include"../Player/TutorialPlayer.h"
#include"../Player/PlayerBullet.h"
#include"../../Graphic/EffekseerManager.h"

TutorialPoint::TutorialPoint(const Vector3 & position):
	Actor(nullptr,"TutorialPoint",position,std::make_shared<BoundingSphere>(0.0f,5.0f))
{
	id_=EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::TUTORIALPOINT_EFFECT, position);
}

TutorialPoint::~TutorialPoint()
{

}

void TutorialPoint::onDraw() const
{
	//body_->transform(getPose())->draw();
}

void TutorialPoint::onCollide(Actor & other)
{
	if (other.getName() == "Player") {
		static_cast<TutorialPlayer*>(&other)->hitPoint();
		dead();
		EffekseerManager::GetInstance().StopEffect3D(id_);
	}
	if (other.getName() == "PlayerBullet") {
		static_cast<TutorialPlayer*>(static_cast<PlayerBullet*>(&other)->getCCPlayer())->hitPoint();
		dead();
		EffekseerManager::GetInstance().StopEffect3D(id_);
	}
}
