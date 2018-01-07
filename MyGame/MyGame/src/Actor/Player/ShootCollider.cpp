#include "ShootCollider.h"
#include"Player.h"
#include"../Body/BoundingSphere.h"

ShootCollider::ShootCollider(Player* player):
	Actor(nullptr,"ShootCenter",player->position(),std::make_shared<BoundingSphere>(Vector3::Zero,20.0f)),player_(player)
{

}

void ShootCollider::onUpdate(float deltaTime)
{
	float rad = 1.0f - std::abs(player_->getShootAngle() / 180.0f - 1.0f);
	rad *= 15.0f;
	rad += 20.0f;//デフォルトサイズ
	position_ = player_->position();
	body_ = std::make_shared<BoundingSphere>(Vector3::Zero, rad);
}

void ShootCollider::onDraw() const
{
	//body_->transform(getPose())->draw();
}

void ShootCollider::onCollide(Actor & other)
{

}
