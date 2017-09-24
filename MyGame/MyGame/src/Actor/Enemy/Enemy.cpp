#include "Enemy.h"
#include"../../Graphic/Model.h"
#include"../../World/IWorld.h"
#include"../../Define.h"
#include"../../Field/Field.h"
#include"../../Graphic/DebugDraw.h"
#include"../../Math/Collision/CollisionMesh.h"
#include"../../Math/Collision/Collision.h"
#include"../../Conv/DXConverter.h"
#include"../../Graphic/Anime.h"

Enemy::Enemy(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr & body):
	Actor(world, name, position, body), gravity_(0.0f), animation_()
{
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::ENEMY_MODEL));
}

void Enemy::onMessage(EventMessage message, void * param)
{
}

void Enemy::onUpdate(float deltaTime)
{
	animation_.ChangeAnim(1);
	animation_.Update(MathHelper::Sign(deltaTime));

		Vector3 result;
		if (field(result)) {
			gravity_ = 0.0f;
			position_ = result;
		}

}

void Enemy::onDraw() const
{
	animation_.Draw();
	Model::GetInstance().Draw(modelHandle_, Matrix(rotation_).Translation(position_));

}

void Enemy::onCollide(Actor & other)
{
}
