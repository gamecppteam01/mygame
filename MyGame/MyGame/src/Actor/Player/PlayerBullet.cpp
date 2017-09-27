#include "PlayerBullet.h"
#include"../../Graphic/Model.h"
#include"../Body/BoundingCapsule.h"

PlayerBullet::PlayerBullet(IWorld* world,const Vector3 & position):
	Actor(world,"PlayerBullet",position, std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f),Matrix::Identity, 20.0f, 3.0f))
{
	modelHandle_ = MODEL_ID::PLAYER_MODEL;
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::PLAYER_MODEL));
}

void PlayerBullet::initialize()
{
}

void PlayerBullet::onMessage(EventMessage message, void * param)
{
}

void PlayerBullet::onUpdate(float deltaTime)
{
}

void PlayerBullet::onDraw() const
{
	animation_.Draw();
	//”»’è‚Ì’†S‚É•`‰æˆÊ’u‚ð‡‚í‚¹‚é
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	Model::GetInstance().Draw(modelHandle_, Matrix(rotation_).Translation(drawPosition));
	
	//body_->draw(position_);

}

void PlayerBullet::onCollide(Actor & other)
{
}

Vector3 * PlayerBullet::getPositionPtr()
{
	return &position_;
}

Matrix * PlayerBullet::getRotationPtr()
{
	return &rotation_;
}

void PlayerBullet::changeAnimation(PlayerBullet_Animation animID, float animSpeed)
{
	animation_.ChangeAnim((int)animID);

}
