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
#include"../../Sound/TempoManager.h"
#include"../../Math/Easing.h"

//�e����΂���
static const float defBoundPower = 5.0f;
//���E�p�x
static const float viewAngle = 60.0f;
//�����o�����E�p�x
static const float moveAngle = 20.0f;
//��{�I�ȃ_�E���l
static const int defDownCount = 1;

//�j->���ŃA�j���[�V������ϊ�
static const std::map<BaseEnemy::Enemy_Animation, EnemyBullet::EnemyBullet_Animation> animConvList{
	{ BaseEnemy::Enemy_Animation::Move_Forward,EnemyBullet::EnemyBullet_Animation::Move_Forward },
	{ BaseEnemy::Enemy_Animation::Idle, EnemyBullet::EnemyBullet_Animation::Idle },
	{ BaseEnemy::Enemy_Animation::Spin,EnemyBullet::EnemyBullet_Animation::Spin },
	{ BaseEnemy::Enemy_Animation::Quarter,EnemyBullet::EnemyBullet_Animation::Quarter },
	{ BaseEnemy::Enemy_Animation::Turn,EnemyBullet::EnemyBullet_Animation::Turn },
	{ BaseEnemy::Enemy_Animation::Half,EnemyBullet::EnemyBullet_Animation::Half },
	{ BaseEnemy::Enemy_Animation::Down,EnemyBullet::EnemyBullet_Animation::Down },
	{ BaseEnemy::Enemy_Animation::WakeUp,EnemyBullet::EnemyBullet_Animation::WakeUp },
	{ BaseEnemy::Enemy_Animation::KnockBack,EnemyBullet::EnemyBullet_Animation::KnockBack },
	{ BaseEnemy::Enemy_Animation::Stan,EnemyBullet::EnemyBullet_Animation::Stan },
};

BaseEnemy::BaseEnemy(IWorld * world, const std::string & name, const Vector3 & position,int playerNumber, const IBodyPtr & body, MODEL_ID id, MODEL_ID bulletid):
	Enemy(world,name,position,body),bullet_(std::make_shared<EnemyBullet>(world,name,position,this, bulletid,body)), turnPower_(1.0f), playerNumber_(playerNumber), nextPosition_(position),
	downCount_(defDownCount), prevHitActorNumber_(0),centerPosition_(position)
{
	world_->addActor(ActorGroup::ENEMY_BULLET, bullet_);
	animation_.SetHandle(Model::GetInstance().GetHandle(id));
	bullet_->changeAnimation(EnemyBullet::EnemyBullet_Animation::Move_Forward);
	modelHandle_ = id;
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
	case BaseEnemy::Enemy_State::WakeUp: {
		updateWakeUp(deltaTime);
		break;
	}
	case BaseEnemy::Enemy_State::Fever: {
		updateFever(deltaTime);
		break;
	}
	default:
		break;
	}	
	//�A�j���[�V�������X�V
	animation_.Update(MathHelper::Sign(deltaTime));

	centerPosition_ += velocity_;
	velocity_ *= 0.5f;

	if (state_ != Enemy_State::Attack) {
		position_ = bulletDistance*rotation_ + centerPosition_;
		*bulletPosition_ = -bulletDistance*rotation_ + centerPosition_;
	}
	correctPosition();

	bulletUpdate(deltaTime);


}

void BaseEnemy::onDraw() const
{
	//����̒��S�ɕ`��ʒu�����킹��
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	animation_.Draw(Matrix(Matrix::Identity)*Matrix(rotation_).Translation(drawPosition));
}

//�e�̕`��
void BaseEnemy::onShadowDraw() const{
	//����̒��S�ɕ`��ʒu�����킹��
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	animation_.Draw(Matrix(Matrix::Identity)*Matrix(rotation_).Translation(drawPosition));
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
		//�v���C���[�ƃv���C���[�e�͕K���A�Ԃł��邽�߁A�v���C���[+1�͒e
		int keysub;
		if (attackTarget_.expired())keysub = 2;
		else keysub=other.getCharacterNumber() == attackTarget_.lock()->getCharacterNumber();
		if (state_ == Enemy_State::Attack&&(keysub==0|| keysub==-1)) {
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
		if (pl->getPlayer()->getState() == Player::Player_State::Shoot)setBoundPower(4);
		else setBoundPower(3);
		//���g�����˕Ԃ�
		hitOther(-bound);
		//�v���C���[�ƃv���C���[�e�͕K���A�Ԃł��邽�߁A�v���C���[�e-1�̓v���C���[
		int keysub;
		if (attackTarget_.expired())keysub = 2;
		else keysub = other.getCharacterNumber() == attackTarget_.lock()->getCharacterNumber();
		if (state_ == Enemy_State::Attack && (keysub == 0 || keysub == 1)) {
			change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Move_Forward);
			return;
		}
		setCountDown();
	}
	else if (other.getName() == "ShootCenter") {
		Vector3 bound = mathBound(other);
		setBoundPower(4);
		//���g�����˕Ԃ�
		hitOther(-bound);
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
		int keysub;
		if (attackTarget_.expired())keysub = 2;
		else keysub = other.getCharacterNumber() == attackTarget_.lock()->getCharacterNumber();
		if (state_ == Enemy_State::Attack && (keysub == 0 || keysub == -1)) {
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
		int keysub;
		if (attackTarget_.expired())keysub = 2;
		else keysub = other.getCharacterNumber() == attackTarget_.lock()->getCharacterNumber();
		if (state_ == Enemy_State::Attack && (keysub == 0 || keysub == 1)) {
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
		change_State_and_Anim(Enemy_State::Down, Enemy_Animation::Down,false);
	}
}

Vector3 BaseEnemy::mathBound(Actor & other)
{
	Vector3 bound = other.position() - centerPosition_;
	bound = bound.Normalize();
	bound *= boundPower_;
	bound.y = 0.0f;

	return bound;
}
bool BaseEnemy::field(Vector3 & result)
{
	if (!world_->getField()->isInField(centerPosition_)) {
		centerPosition_ = world_->getField()->CorrectPosition(centerPosition_);
		position_ = bulletDistance*rotation_ + centerPosition_;
		*bulletPosition_ = -bulletDistance*rotation_ + centerPosition_;

	}

	Vector3 hit1;
	Vector3 hit2;
	if (world_->getField()->getMesh().collide_capsule(position_ + body_->points(0), position_ + body_->points(1), body_->radius(), *bulletPosition_ + body_->points(0), *bulletPosition_ + body_->points(1), bullet_->body_->radius(), (VECTOR*)&hit1, (VECTOR*)&hit2))
	{
		//�{�̂ƒe�̒��S��Ԃ�
		result = (hit1 + hit2)*0.5f + ((body_->points(0)));
		//result = hit1 + ((body_->points(0)));

		return true;
	}
	return false;
}

float BaseEnemy::mathSpeed(float current, float maxSpeed,float maxTime, float topTime)
{
	//2�����̎���
	float maxEaseTime = maxTime;
	//0.5�����擾�A�����𐨂��̒��_�Ƃ���
	float quarter = topTime;

	speedEaseTimer_ = min(speedEaseTimer_, maxEaseTime);
	float  timing = speedEaseTimer_ - quarter;
	float answer;

	//�`0.5�b
	if (timing < 0.0f) {
		answer = Easing::EaseInCubic(speedEaseTimer_, 0.0f, maxSpeed, quarter);
		//answer = 1.f - std::abs(timing)*4.f;
	}
	else {
		answer = Easing::EaseOutQuad(speedEaseTimer_ - quarter, maxSpeed, -maxSpeed, maxEaseTime - quarter);
		//answer = 1.f - std::abs(timing)*(3.0f-speedEaseTimer_);

	}
	return answer;
}

float BaseEnemy::mathSpeedUnderPower(float current, float maxSpeed, float maxTime, float topTime)
{
	float answer = mathSpeed(current, maxSpeed, maxTime, topTime);
	return MathHelper::Max((1.0f + answer), 0.0f);
}

void BaseEnemy::JustStep()
{
	//�^�[�Q�b�g�w��̃��Z�b�g�͂Ƃ肠�������
	nonTargetResetTimer_.Action();
	//�X�e�b�v�o����Ƃ������X�e�b�v����
	if (!isCanStep())return;
	ActorPtr act = getNearestActor();
	//�U���˒������Ȃ�
	if (Vector3::Distance(act->position(), centerPosition_)<= attackDistance&&prevHitActorNumber_!= act->getCharacterNumber()) {
		change_State_and_Anim(Enemy_State::Attack, stepAnim[1].first);
		return;
	}
	int key = Random::GetInstance().Range(0, 1);
	if (key == 1)key++;

	change_State_and_Anim(Enemy_State::Step, stepAnim[key].first,false);
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
	Vector3 toTarget = targetPos - centerPosition_;
	//�p�x�����߂�
	float forwardAngle = MathHelper::ACos(Vector3::Dot(rotation_.Forward().Normalize(), toTarget.Normalize()));
	float leftAngle = MathHelper::ACos(Vector3::Dot(rotation_.Left().Normalize(), toTarget.Normalize()));

	//�s���͈͓���������
	if (forwardAngle < moveAngle) {
		float moveSpeed = 0.5f;
		//�^�[�Q�b�g�����ɑO�i
		centerPosition_ += toTarget.Normalize()*moveSpeed;
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

	*bulletPosition_ = centerPosition_ + (-bulletDistance*rotation_);

	*bulletRotation_ = rotation_*Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f);

}

void BaseEnemy::addVelocity_NextPosition(float deltaTime)
{
	velocity_ += (nextPosition_ - centerPosition_).Normalize()*movePower;
}

void BaseEnemy::changeAnimation(Enemy_Animation animID,float animFrame, float animSpeed, bool isLoop)
{
	animation_.ChangeAnim((int)animID, animFrame,animSpeed,isLoop);
	bullet_->changeAnimation(animConvList.at(animID), animFrame, animSpeed, isLoop);
	
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
	case BaseEnemy::Enemy_State::WakeUp: {
		to_WakeUp();
		break;
	}
	case BaseEnemy::Enemy_State::Fever:
		to_Fever();
		break;
	default:
		break;
	}
	//�X�V����
	return true;
}

bool BaseEnemy::change_State_and_Anim(Enemy_State state, Enemy_Animation animID, bool isLoop)
{
	if (!change_State(state,animID))return false;
	changeAnimation(animID,0.0f,1.0f,isLoop);

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
	nextPosition_ = world_->getCanChangedScoreMap().getNextPoint(centerPosition_)+Vector3(Random::GetInstance().Range(-20.0f,20.0f),0.0f, Random::GetInstance().Range(-20.0f, 20.0f));
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

void BaseEnemy::to_WakeUp(){
	wakwUpTime_ = 0.0f;
}

void BaseEnemy::to_Fever(){
}

void BaseEnemy::updateNormal(float deltaTime)
{
	//float maxEaseTime = world_->getCanChangedTempoManager().getOneBeatTime()*2.0f;
	//speedEaseTimer_ += deltaTime;
	//float time = speedEaseTimer_ / maxEaseTime;
	//float ease = Easing::EaseInOutCirc(speedEaseTimer_, 0.0f, 1.0f, maxEaseTime);
	//float normal = Easing::Linear(speedEaseTimer_, 0.0f, 1.0f, maxEaseTime);
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
	if (Vector2::Distance(Vector2(centerPosition_.x, centerPosition_.z), Vector2(nextPosition_.x, nextPosition_.z)) <= 10.0f) {
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

	centerPosition_ += (attackTarget_.lock()->position() - centerPosition_).Normalize() *attackPower;

	//���������]
	Vector3 baseRotatePos = bulletDistance;
	position_ = centerPosition_ + (baseRotatePos *rotation_* Matrix::CreateRotationY(-stepTime_*5.0f));
	//��]���X�V
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -20.0f*turnPower_);

	Vector3 rotatePos = -bulletDistance;
	*bulletPosition_ = centerPosition_ + (rotatePos *rotation_* Matrix::CreateRotationY(-stepTime_*5.0f));

}
void BaseEnemy::updateDown(float deltaTime)
{
	downTime_ += deltaTime;

	if (downTime_ >= downTime) {
		change_State_and_Anim(Enemy_State::WakeUp, Enemy_Animation::WakeUp, false);
	}

}
void BaseEnemy::updateWakeUp(float deltaTime){
	wakwUpTime_ += deltaTime;

	if (wakwUpTime_ >= animation_.GetAnimMaxTime())
		change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Move_Forward,true);
}

void BaseEnemy::updateFever(float deltaTime){
}

bool BaseEnemy::isCanStep() const
{
	return state_ == Enemy_State::Normal;
}
void BaseEnemy::correctPosition()
{
	Vector3 result;
	if (field(result)) {
		centerPosition_ = result;
	}
	Vector3 start = centerPosition_ + body_->points(1);
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
		if (Vector3::Distance(centerPosition_, attackTarget->position()) > Vector3::Distance(centerPosition_, e->position())) {
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
