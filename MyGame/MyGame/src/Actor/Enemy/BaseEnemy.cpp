#include "BaseEnemy.h"
#include"EnemyBullet.h"
#include"../ActorGroup.h"
#include"../../World/IWorld.h"
#include"../../Graphic/Model.h"
#include"../Player/Player.h"
#include"../Player/PlayerBullet.h"
#include"../../Graphic/DebugDraw.h"
#include"../../ScoreManager/ScoreManager.h"
#include"../../Math/Random.h"
#include"../../ScoreManager/ScoreMap.h"
#include"../../Field/Field.h"

//�j�Ə��̋���
static const Vector3 bulletDistance{ 0.0f,0.0f,8.0f };
//�e����΂���
static const float defBoundPower = 5.0f;
//���E�p�x
static const float viewAngle = 60.0f;
//�����o�����E�p�x
static const float moveAngle = 20.0f;
//��{�I�ȃ_�E���l
static const int defDownCount = 2;

BaseEnemy::BaseEnemy(IWorld * world, const std::string & name, const Vector3 & position,int playerNumber, const IBodyPtr & body):
	Enemy(world,name,position,body),bullet_(std::make_shared<EnemyBullet>(world,name,position,this,body)), turnPower_(1.0f), playerNumber_(playerNumber), nextPosition_(position),
	downCount_(defDownCount), prevHitActorNumber_(0)
{
	world_->addActor(ActorGroup::ENEMY_BULLET, bullet_);
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::ENEMY_MODEL));
	bullet_->changeAnimation(EnemyBullet::EnemyBullet_Animation::Move_Forward);
	modelHandle_ = MODEL_ID::ENEMY_MODEL;
	changeAnimation(Enemy_Animation::Move_Forward);

	bullet_->initialize();

	//���̈ړ��Ɖ�]�̑��쌠�𓾂�
	bulletPosition_ = bullet_->getPositionPtr();
	bulletRotation_ = bullet_->getRotationPtr();

	target_ = world_->findActor("Player");
	
}

void BaseEnemy::hitOther(const Vector3 & velocity)
{
	bound_ += velocity;
	//bulletVelocity_ += velocity;
	//velocity_ += velocity;
}

void BaseEnemy::onMessage(EventMessage message, void * param)
{
}

void BaseEnemy::onUpdate(float deltaTime){
	
	switch (state_)
	{
	case BaseEnemy::Enemy_State::Normal: {
		updateNormal(deltaTime);
		break; 
	}
	case BaseEnemy::Enemy_State::Step: {
		updateStep(deltaTime);
		break;
	}
	case BaseEnemy::Enemy_State::Track: {
		updateTrack(deltaTime);
		break;
	}
	case BaseEnemy::Enemy_State::Attack: {
		updateAttack(deltaTime);
		break;
	}
	case BaseEnemy::Enemy_State::Down: {
		updateDown(deltaTime);
		break;
	}
	default:
		break;
	}	
	//�A�j���[�V�������X�V
	animation_.Update(MathHelper::Sign(deltaTime));

	position_ += velocity_;
	velocity_ *= 0.5f;

	correctPosition();

	bulletUpdate(deltaTime);


}

void BaseEnemy::onDraw() const
{
	//����̒��S�ɕ`��ʒu�����킹��
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	animation_.Draw(Matrix::CreateRotationY(180.0f)*Matrix(rotation_).Translation(drawPosition));
	
}

void BaseEnemy::onCollide(Actor & other)
{
	if (other.getName() == "Player") {
		Vector3 bound = mathBound(other);
		//����𒵂˕Ԃ�

		auto pl = static_cast<Player*>(&other);
		pl->hitEnemy(name_, bound);
		if (pl->getState() == Player::Player_State::Shoot)setBoundPower(4);
		else setBoundPower(3);

		//���g�����˕Ԃ�
		hitOther(-bound);
		if (state_ == Enemy_State::Attack&&other.getCharacterNumber() == attackTarget_.lock()->getCharacterNumber()) {
			change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Move_Forward);
			return;
		}
		setCountDown();
	}
	else if (other.getName() == "PlayerBullet") {
		Vector3 bound = mathBound(other);
		//����𒵂˕Ԃ�
		auto pl = static_cast<PlayerBullet*>(&other);
		pl->hitEnemy(name_, bound);
		if(pl->getPlayer()->getState()==Player::Player_State::Shoot)setBoundPower(4);
		else setBoundPower(3);
		//���g�����˕Ԃ�
		hitOther(-bound);
		if (state_ == Enemy_State::Attack) {
			change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Move_Forward);
			return;
		}
		setCountDown();
	}
	else if (other.getName() == "Enemy") {
		//�������g�Ȃ画�肵�Ȃ�
		if (static_cast<BaseEnemy*>(&other)->getPlayerNumber() == playerNumber_) return;

		Vector3 bound = mathBound(other);
		//����𒵂˕Ԃ�
		static_cast<BaseEnemy*>(&other)->hitOther(bound);
		//���g�����˕Ԃ�
		hitOther(-bound);
		if (state_ == Enemy_State::Attack) {
			change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Move_Forward);
			return;
		}
		//setCountDown();
	}
	else if (other.getName() == "EnemyBullet") {
		if (static_cast<EnemyBullet*>(&other)->enemy_->playerNumber_ == playerNumber_)return;
		Vector3 bound = mathBound(other);
		//����𒵂˕Ԃ�
		static_cast<EnemyBullet*>(&other)->hitOther(bound);
		//���g�����˕Ԃ�
		hitOther(-bound);
		if (state_ == Enemy_State::Attack) {
			change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Move_Forward);
			return;
		}
		//setCountDown();
	}

}

void BaseEnemy::onCollideResult()
{
	bound_.y = 0.0f;
	Vector3 bound = bound_.Normalize()*boundPower_;
	bound.y = 0.0f;
	
	bulletVelocity_ += bound;
	velocity_ += bound;

	bound_ = Vector3::Zero;

	downTimer_.Action();
	//�_�E���l�����܂�����
	if (downCount_ <= 0) {
		change_State_and_Anim(Enemy_State::Down, Enemy_Animation::Down);
	}
}

Vector3 BaseEnemy::mathBound(Actor & other)
{
	Vector3 bound = other.position() - position_;
	bound = bound.Normalize();
	bound *= boundPower_;
	bound.y = 0.0f;

	return bound;
}
bool BaseEnemy::field(Vector3 & result)
{
	if (!world_->getField()->isInField(position_)) {
		position_ = world_->getField()->CorrectPosition(position_);
	}

	Vector3 hit1;
	Vector3 hit2;
	if (world_->getField()->getMesh().collide_capsule(position_ + body_->points(0), position_ + body_->points(1), body_->radius(), *bulletPosition_ + body_->points(0), *bulletPosition_ + body_->points(1), bullet_->body_->radius(), (VECTOR*)&hit1, (VECTOR*)&hit2))
	{
		result = hit1 + ((body_->points(0)));

		return true;
	}
	return false;
}

void BaseEnemy::JustStep()
{
	//�^�[�Q�b�g�w��̃��Z�b�g�͂Ƃ肠�������
	nonTargetResetTimer_.Action();
	//�X�e�b�v�o����Ƃ������X�e�b�v����
	if (!isCanStep())return;
	ActorPtr act = getNearestActor();
	//�U���˒������Ȃ�
	if (Vector3::Distance(act->position(), position_)<= attackDistance&&prevHitActorNumber_!= act->getCharacterNumber()) {
		change_State_and_Anim(Enemy_State::Attack, stepAnim[1].first);
		return;
	}
	int key = Random::GetInstance().Range(0, 1);
	if (key == 1)key++;

	change_State_and_Anim(Enemy_State::Step, stepAnim[key].first);
	world_->getCanChangedScoreManager().addScore(playerNumber_, stepAnim[key].second);
}

void BaseEnemy::setBoundPower(float powerRate)
{
	boundPower_ = defBoundPower*powerRate;
}

void BaseEnemy::searchTarget(float deltaTime)
{
	//�^�[�Q�b�g�����݂��Ȃ���΍��G����
	if (target_ == nullptr)return;
	//�^�[�Q�b�g�̈ʒu������
	Vector3 targetPos = target_->position();
	//�^�[�Q�b�g�����̃x�N�g��
	Vector3 toTarget = targetPos - position_;
	//�p�x�����߂�
	float forwardAngle = MathHelper::ACos(Vector3::Dot(rotation_.Forward().Normalize(), toTarget.Normalize()));
	float leftAngle = MathHelper::ACos(Vector3::Dot(rotation_.Left().Normalize(), toTarget.Normalize()));

	//�s���͈͓���������
	if (forwardAngle < moveAngle) {
		float moveSpeed = 0.5f;
		//�^�[�Q�b�g�����ɑO�i
		position_ += toTarget.Normalize()*moveSpeed;
	}
	//���E�͈͓���������
	if (forwardAngle < viewAngle) {
		//���g����]������
		float rotateAngle = 3.0f;
		//���Ȃ�E��
		if (leftAngle > 90.0f) rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -rotateAngle);
		//�E�Ȃ獶��
		else if(leftAngle < 90.0f) rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), rotateAngle);
		
	}
}

void BaseEnemy::bulletUpdate(float deltaTime)
{
	*bulletPosition_ = position_ + (bulletDistance*rotation_);

	*bulletRotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -20.0f*turnPower_);

}

void BaseEnemy::addVelocity_NextPosition(float deltaTime)
{
	velocity_ += (nextPosition_ - position_).Normalize()*movePower;
}

void BaseEnemy::changeAnimation(Enemy_Animation animID,float animFrame, float animSpeed, bool isLoop)
{
	animation_.ChangeAnim((int)animID, animFrame,animSpeed,isLoop);
}

bool BaseEnemy::change_State(Enemy_State state,BaseEnemy::Enemy_Animation anim)
{
	//��Ԃ��ς��Ȃ��Ȃ玸�s
	if (state_ == state)return false;

	//��Ԃ̏I���������s��
	switch (state_)
	{
	case BaseEnemy::Enemy_State::Normal:
		break;
	case BaseEnemy::Enemy_State::Step:
		break;
	default:
		break;
	}
	//��Ԃ��X�V
	state_ = state;

	//��ԕύX���s��
	switch (state_)
	{
	case BaseEnemy::Enemy_State::Normal:{
		to_Normal();
		break;
	}
	case BaseEnemy::Enemy_State::Step:{
		to_Step(anim);
		break;
	}
	case BaseEnemy::Enemy_State::Track:{
		to_Track();
		break;
	}
	case BaseEnemy::Enemy_State::Attack: {
		to_Attack(anim);
		break;
	}
	case BaseEnemy::Enemy_State::Down: {
		to_Down();
		break;
	}
	default:
		break;
	}
	//�X�V����
	return true;
}

bool BaseEnemy::change_State_and_Anim(Enemy_State state, Enemy_Animation animID)
{
	if (!change_State(state,animID))return false;
	changeAnimation(animID);

	return true;
}

void BaseEnemy::to_Normal()
{
}

void BaseEnemy::to_Step(BaseEnemy::Enemy_Animation anim)
{
	world_->getScoreManager().addScore(playerNumber_, SCORE_QUARTER);

	//�Ή������A�j���[�V�����̏I�����Ԃ��擾����
	stepTime_ = animation_.GetAnimMaxTime((int)anim);

}

void BaseEnemy::to_Track()
{
	nextPosition_ = world_->getCanChangedScoreMap().getNextPoint(position_)+Vector3(Random::GetInstance().Range(-20.0f,20.0f),0.0f, Random::GetInstance().Range(-20.0f, 20.0f));
}

void BaseEnemy::to_Attack(BaseEnemy::Enemy_Animation anim)
{
	//3��X�e�b�v������U���Ώۂ����Z�b�g
	nonTargetResetTimer_.Initialize();
	nonTargetResetTimer_.AddEmpty(3);
	nonTargetResetTimer_.Add([&] {prevHitActorNumber_ = -1; });
	attackTarget_ = getNearestActor();
	prevHitActorNumber_ = attackTarget_.lock()->getCharacterNumber();
	//stepTime_ = animation_.GetAnimMaxTime((int)anim);
	stepTime_ = 1.5f;
}

void BaseEnemy::to_Down()
{
	//�_�E���l�����ɖ߂���
	downCount_ = defDownCount;
	downTime_ = 0.0f;
}

void BaseEnemy::updateNormal(float deltaTime)
{
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);

	//searchTarget(deltaTime);
	gravity_ -= 0.05f;

	Vector3 jumpVector = Vector3(0.0f, gravity_, 0.0f);
	velocity_ += jumpVector;

}

void BaseEnemy::updateStep(float deltaTime)
{
	stepTime_ -= deltaTime;
	//�X�e�b�v���I��������ҋ@��Ԃɖ߂�
	if (stepTime_ <= 0.0f) {
		if (change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Move_Forward))updateNormal(deltaTime);
		return;
	}


}

void BaseEnemy::updateTrack(float deltaTime)
{
	if (Vector2::Distance(Vector2(position_.x, position_.z), Vector2(nextPosition_.x, nextPosition_.z)) <= 10.0f) {
		if (change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Move_Forward))updateNormal(deltaTime);
		return;
	}
	addVelocity_NextPosition(deltaTime);

}
void BaseEnemy::updateAttack(float deltaTime)
{
	stepTime_ -= deltaTime;
	//�X�e�b�v���I��������ҋ@��Ԃɖ߂�
	if (stepTime_ <= 0.0f) {
		if (change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Move_Forward))updateNormal(deltaTime);
		return;
	}

	position_ += (attackTarget_.lock()->position() - position_).Normalize() *attackPower;

}
void BaseEnemy::updateDown(float deltaTime)
{
	downTime_ += deltaTime;

	if (downTime_ >= downTime) {
		if (change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Idle))updateDown(deltaTime);
	}

}
bool BaseEnemy::isCanStep() const
{
	return state_ == Enemy_State::Normal;
}
void BaseEnemy::correctPosition()
{
	Vector3 result;
	if (field(result)) {
		position_ = result;
	}
	Vector3 start = position_ + body_->points(1);
	Vector3 end = start + Vector3::Down*(body_->radius() + 1.0f);
	if (world_->getField()->getMesh().collide_line(start, end)) {
		gravity_ = 0.0f;
	}

}

ActorPtr BaseEnemy::getNearestActor()
{
	ActorPtr attackTarget=nullptr;
	std::list<ActorPtr> others;
	world_->findActors("Enemy", others);

	others.remove_if([this] (const ActorPtr& ap){
		return std::static_pointer_cast<BaseEnemy>(ap)->getPlayerNumber() == getPlayerNumber();
	});
	
	auto player = world_->findActor("Player");
	others.push_back(player);

	attackTarget = others.front();
	for (auto& e : others) {
		if (Vector3::Distance(position_, attackTarget->position()) > Vector3::Distance(position_, e->position())) {
			attackTarget = e;
		}
	}
	return attackTarget;
}

void BaseEnemy::setCountDown()
{
	//�_�E�����ĂȂ���΃_�E���l�~�ς�L����
	if (state_ == Enemy_State::Down)return;
	downTimer_.Initialize();
	downTimer_.Add([this] {downCount_--; });
}
