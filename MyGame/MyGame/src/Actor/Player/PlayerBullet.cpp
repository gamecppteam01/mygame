#include "PlayerBullet.h"
#include"../../Graphic/Model.h"
#include"../Body/BoundingCapsule.h"
#include"Player.h"
#include"../../Sound/Sound.h"
PlayerBullet::PlayerBullet(IWorld* world,const Vector3 & position, Player* player):
	Actor(world,"PlayerBullet",position, std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f),Matrix::Identity, 20.0f, 3.0f)),
	player_(player)
{
	modelHandle_ = MODEL_ID::PLAYER_BULLET_MODEL;
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::PLAYER_BULLET_MODEL));
}

void PlayerBullet::initialize()
{
}

void PlayerBullet::hitEnemy(const std::string& hitName,const Vector3& velocity)
{
	player_->hitEnemy(hitName, velocity);
}

const Player* PlayerBullet::getPlayer() const
{
	return player_;
}

Vector3 & PlayerBullet::position()
{
	return player_->position();
}

void PlayerBullet::onMessage(EventMessage message, void * param)
{
}

void PlayerBullet::onUpdate(float deltaTime)
{
	animation_.Update(MathHelper::Sign(deltaTime));
}

void PlayerBullet::onDraw() const
{
	//”»’è‚Ì’†S‚É•`‰æˆÊ’u‚ð‡‚í‚¹‚é
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	animation_.Draw(Matrix(rotation_).Translation(drawPosition));

	//body_->draw(position_);

}

void PlayerBullet::onCollide(Actor & other)
{
	if ((other.getName() == "Enemy" || other.getName() == "EnemyBullet")) {
		Sound::GetInstance().PlaySE(SE_ID::HIT_SE);
	}


}

Vector3 * PlayerBullet::getPositionPtr()
{
	return &position_;
}

Matrix * PlayerBullet::getRotationPtr()
{
	return &rotation_;
}

void PlayerBullet::changeAnimation(PlayerBullet_Animation animID, float animFrame, float animSpeed, bool isLoop,float blend)
{
	animation_.ChangeAnim((int)animID,animFrame,animSpeed,isLoop,blend);

}
