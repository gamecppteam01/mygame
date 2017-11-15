#include "Player.h"
#include"../../Graphic/Model.h"
#include"../../World/IWorld.h"
#include"../../Input/InputChecker.h"
#include"../../Define.h"
#include"../../Field/Field.h"
#include"../../Graphic/DebugDraw.h"
#include"../../Math/Collision/CollisionMesh.h"
#include"../../Math/Collision/Collision.h"
#include"../../Conv/DXConverter.h"
#include"../../Graphic/Anime.h"
#include"../../Graphic/Sprite.h"
#include"../Body/BoundingCapsule.h"
#include"PlayerBullet.h"
#include"../ActorGroup.h"
#include"../../Camera/OverLookingCamera.h"
#include"../EffectActor/UniqueEffectActor/TrackingEffectActor.h"
#include"../../Effect/CircleEffect.h"
#include"../Dummy/BetweenPositionActor.h"
#include"../../Input/DualShock4Manager.h"
#include"../../Judge/JudgeDefine.h"
#include"../../ScoreManager/ScoreManager.h"
#include"../../Graphic/FontManager.h"
#include"../../Math/MathHelper.h"
#include"../../Sound/TempoManager.h"
#include"../../Graphic/EffekseerManager.h"


//move����idle�Ɉڍs����ۂ�input�m�F���J�E���g
static const int inputCheckCount = 4;
//�j�Ə��̋���
static const Vector3 bulletDistance{ 0.0f,0.0f,4.0f };
//��]�͂̊�{�W��
static const float defaultTurnPower = 1.0f;
//��������R���g���[���̌X���͈�
static const float ignoreSlope = 0.1f;
static const float boundPower = 15.0f;
static const float downTime = 7.0f;
//�ړ����x
static const float movePower = 0.5f;
//��낯����񕜂���܂ł̎���
static const float defStumbleResurrectTime = 0.5f;
//�X�e�b�v�񐔂ɂ���낯�̃`�F�b�N����
static const int defStepCount = 3;

//�X�s���̉�]�͈�
static const float spinPower = 6.0f;

Player::Player(IWorld* world, const std::string& name, const Vector3& position,int playerNumber) :
	Actor(world, name, position, std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f),
	Matrix::Identity, 20.0f, 3.0f)), upVelocity_(0.0f),velocity_(Vector3::Zero), gravity_(0.0f),animation_(),
	state_(Player_State::Idle), defaultPosition_(position), centerPosition_(position),
	bulletVelocity_(Vector3::Zero), turnPower_(1.0f), bound_(Vector3::Zero), playerNumber_(playerNumber),
	gyroCheck_()
{
	createBullet();
	world_->addActor(ActorGroup::PLAYER_BULLET, bullet_);

	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::PLAYER_MODEL));
	bullet_->changeAnimation(PlayerBullet::PlayerBullet_Animation::Move_Forward);
	initialize();

	//�e��X�V�֐���ݒ肷��
	playerUpdateFunc_[Player_State::Idle] = [this](float deltaTime) {idle_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Move] = [this](float deltaTime) {move_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Step] = [this](float deltaTime) {step_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Step_Success] = [this](float deltaTime) {stepSuccess_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Attack] = [this](float deltaTime) {attack_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Shoot] = [this](float deltaTime) {shoot_Update(deltaTime); };
	playerUpdateFunc_[Player_State::ShootEnd] = [this](float deltaTime) {shootend_Update(deltaTime); };
	playerUpdateFunc_[Player_State::KnockBack] = [this](float deltaTime) {knockback_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Down] = [this](float deltaTime) {down_Update(deltaTime); };
	playerUpdateFunc_[Player_State::Stumble] = [this](float deltaTime) {stumble_Update(deltaTime); };

	//�e���ԕύX�֐���ݒ肷��
	playerToNextModeFunc_[Player_State::Idle] = [this]() {to_IdleMode(); };
	playerToNextModeFunc_[Player_State::Move] = [this]() {to_MoveMode(); };
	playerToNextModeFunc_[Player_State::Step] = [this]() {to_StepMode(); };
	playerToNextModeFunc_[Player_State::Step_Success] = [this]() {to_StepSuccessMode(); };
	playerToNextModeFunc_[Player_State::Attack] = [this]() {to_AttackMode(); };
	playerToNextModeFunc_[Player_State::Shoot] = [this]() {to_ShootMode(); };
	playerToNextModeFunc_[Player_State::ShootEnd] = [this]() {to_ShootEndMode(); };
	playerToNextModeFunc_[Player_State::KnockBack] = [this]() {to_KnockBackMode(); };
	playerToNextModeFunc_[Player_State::Down] = [this]() {to_DownMode(); };
	playerToNextModeFunc_[Player_State::Stumble] = [this]() {to_StumbleMode(); };

	playerEndModeFunc_[Player_State::Idle] = [this]() {		end_IdleMode(); };
	playerEndModeFunc_[Player_State::Move] = [this]() {		end_MoveMode(); };
	playerEndModeFunc_[Player_State::Step] = [this]() {		end_StepMode(); };
	playerEndModeFunc_[Player_State::Step_Success] = [this]() {		end_StepSuccessMode(); };
	playerEndModeFunc_[Player_State::Attack] = [this]() {	end_AttackMode(); };
	playerEndModeFunc_[Player_State::Shoot] = [this]() {	end_ShootMode(); };
	playerEndModeFunc_[Player_State::ShootEnd] = [this]() {	end_ShootEndMode(); };
	playerEndModeFunc_[Player_State::KnockBack] = [this]() {end_KnockBackMode(); };
	playerEndModeFunc_[Player_State::Down] = [this]() {		end_DownMode(); };
	playerEndModeFunc_[Player_State::Stumble] = [this]() {		end_StumbleMode(); };
	
}

void Player::addVelocity(const Vector3 & velocity)
{
	velocity_ += velocity;
}

void Player::hitEnemy(const std::string& hitName, const Vector3& velocity)
{
	bound_ += velocity;

	//�U����ԂȂ�Ђ�܂Ȃ�
	if (isAttack()) {
		if(state_==Player_State::Attack)change_State_and_Anim(Player_State::Idle, Player_Animation::Idle);
		return;
	}
	stumbleDirection_= mathStumbleDirection(Vector2(-velocity.x, -velocity.z));

	//stumbleDirection_ = -velocity;
	change_State_and_Anim(Player_State::Stumble, Player_Animation::KnockBack);
}

float Player::getPlayerScoreRate() const
{
	return world_->getScoreManager().GetCharacterScoreRate(playerNumber_);
}

void Player::createBullet()
{
	bullet_ = std::make_shared<PlayerBullet>(world_, position_, this);
}

void Player::initialize()
{
	position_ = centerPosition_ + bulletDistance;
	gravity_ = 0.0f;
	state_ = Player_State::Idle;
	modelHandle_ = MODEL_ID::PLAYER_MODEL;
	changeAnimation(Player_Animation::Idle);

	turnPower_ = 1.0f;
	bullet_->initialize();

	//���̈ړ��Ɖ�]�̑��쌠�𓾂�
	bulletPosition_ = bullet_->getPositionPtr();
	bulletRotation_ = bullet_->getRotationPtr();

	*bulletPosition_ = centerPosition_ - bulletDistance;

	gyroCheck_.initialize();
}

void Player::onMessage(EventMessage message, void * param)
{
}

void Player::onUpdate(float deltaTime)
{
	playerUpdateFunc_[state_](deltaTime);
	animation_.Update(MathHelper::Sign(deltaTime));

	//���t���[���̍X�V��K�p
	centerPosition_ += velocity_;

	if (state_ != Player_State::Shoot&&state_!=Player_State::Attack) {
		position_ = bulletDistance*rotation_ + centerPosition_;
		*bulletPosition_ = -bulletDistance*rotation_ + centerPosition_;
	}
	velocity_ -= velocity_*0.5f;
	correctPosition();

	//�����X�V����
	if(isCanTracking())bulletUpdate(deltaTime);

	//float tempo = std::abs(world_->getCanChangedTempoManager().getTempoCount() - 0.5f);
	//float pow = 2.0f;
	//effectSize_ = 1.0f-(std::powf(tempo, pow)*2.0f*pow);


	float tempo = world_->getCanChangedTempoManager().getTempoCount();
	float beat = (world_->getCanChangedTempoManager().getBeatCount() % 3);
	effectSize_[0] = 3.0f - (tempo+beat);
	effectSize_[0] = effectSize_[0] / 3.f;

}

void Player::onDraw() const
{
	//����̒��S�ɕ`��ʒu�����킹��
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	animation_.Draw(Matrix(rotation_).Translation(drawPosition));

	DrawFormatStringToHandle(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, GetColor(255, 255, 255), FontManager::GetInstance().GetFontHandle(FONT_ID::JAPANESE_FONT), std::to_string(nextStep_).c_str());

	if (world_->getScoreManager().GetCharacterScoreRate(playerNumber_) > 1.0f) {
		DebugDraw::DebugDrawFormatString(300, 300, GetColor(255, 255, 255), "�X�R�A����");
	}

	world_->setLateDraw([this] {
		Vector2 origin = Vector2(0.5f, 0.5f);
		float beat = (world_->getCanChangedTempoManager().getBeatCount() % 3);
		if (isJustTiming()) {
			SetDrawBright(200, 30, 100);
		}
		float size = 1.0f;
		float tempo = world_->getCanChangedTempoManager().getTempoCount();
		if (tempo <= 0.3f) {
			size = 1.0f+ (0.3f - tempo);
		}
		Model::GetInstance().Draw2D(MODEL_ID::JUST_CIRCLE_MODEL, centerPosition_, 0, 24.0f*size , origin, 0.0f, 1.0f);
		Model::GetInstance().Draw2D(MODEL_ID::EFFECT_CIRCLE_MODEL, centerPosition_, 0, 22.0f*size, origin, 0.0f, 0.7f);
		Model::GetInstance().Draw2D(MODEL_ID::EFFECT_CIRCLE_MODEL, centerPosition_, 0, 10.0f*size, origin, 0.0f, 0.7f);
		SetDrawBright(0, 255, 255);
		Model::GetInstance().Draw2D(MODEL_ID::EFFECT_CIRCLE_MODEL, centerPosition_, 0, effectSize_[0] * 32.0f*size, origin, 0.0f, 1.0f);
		SetDrawBright(255, 255, 255);
		//3�A�W���X�g�T�[�N��
		/*
		//if (world_->getCanChangedTempoManager().getBeatCount() % 3 == 0)SetDrawBright(200, 0, 0);
		SetDrawBright(200, 0, 0);
		Vector2 origin = Vector2(0.5f, 0.5f);
		Model::GetInstance().Draw2D(MODEL_ID::EFFECT_CIRCLE_MODEL, position_, 0, effectSize_[0]*64.0f, origin, 0.0f, 1.0f);
		SetDrawBright(255, 255, 255);
		//if (world_->getCanChangedTempoManager().getBeatCount() % 3 == 2)SetDrawBright(200, 0, 0);
		Model::GetInstance().Draw2D(MODEL_ID::EFFECT_CIRCLE_MODEL, position_, 0, effectSize_[1]*64.0f, origin, 0.0f, 1.0f);
		//SetDrawBright(255, 255, 255);
		//if (world_->getCanChangedTempoManager().getBeatCount() % 3 == 1)SetDrawBright(200, 0, 0);
		Model::GetInstance().Draw2D(MODEL_ID::EFFECT_CIRCLE_MODEL, position_, 0, effectSize_[2]*64.0f, origin, 0.0f, 1.0f);
		SetDrawBright(255, 255, 255); 
		*/
	}
	);
}

void Player::onCollide(Actor & other)
{
	if ((other.getName() == "Enemy" || other.getName() == "EnemyBullet") && isCanStamble()) {

	}

}
void Player::onCollideResult()
{
	bound_.y = 0.0f;
	Vector3 bound = bound_.Normalize()*boundPower;
	bound.y = 0.0f;
	bulletVelocity_ += bound;
	//�V���[�g���łȂ���΃v���C���[���g�����˂���
	if (state_ != Player_State::Shoot)velocity_ += bound;

	bound_ = Vector3::Zero;

	if (state_ == Player_State::Shoot)return;

	position_ = bulletDistance*rotation_ + centerPosition_;
	*bulletPosition_ = -bulletDistance*rotation_ + centerPosition_;
}

void Player::JustStep()
{
	//�X�e�b�v������������
	stepCount_++;
	//�p���̃`�F�b�N���K�v�Ȃ�
	if (!isRequiredCheckPosture())return;
	if (stepCount_ >= defStepCount) {
		stepCount_ = 0;
		//�o�����X�����Ă邩���`�F�b�N
		//if (DualShock4Manager::GetInstance().GetAngle3D().z <= 45.0f) {
		//	downTime_ = 2.0f;
		//	change_State_and_Anim(Player_State::Down, Player_Animation::Down, 0.0f, 1.0f, false);
		//}
	}
}

void Player::CreateJustEffect()
{
	//createCircleEffect();
}

bool Player::field(Vector3 & result)
{
	if (!world_->getField()->isInField(centerPosition_)) {
		centerPosition_ = world_->getField()->CorrectPosition(centerPosition_);
		if (state_ != Player_State::Shoot) {
			position_ = bulletDistance*rotation_ + centerPosition_;
			*bulletPosition_ = -bulletDistance*rotation_ + centerPosition_;
		}
	}
	Vector3 hit1;
	Vector3 hit2;
	//���S�����̂܂�center�ɓ���悤
	if (world_->getField()->getMesh().collide_capsule(position_ + body_->points(0), position_ + body_->points(1), body_->radius(), *bulletPosition_ + body_->points(0), *bulletPosition_ + body_->points(1), bullet_->body_->radius(), (VECTOR*)&hit1, (VECTOR*)&hit2))
	{
		//�{�̂ƒe�̒��S��Ԃ�
		result = (hit1+hit2)*0.5f + ((body_->points(0)));

		return true;
	}
	return false;
}

void Player::gravityUpdate(float deltaTime)
{
	gravity_ -= 0.05f;

	Vector3 jumpVector = Vector3(0.0f, upVelocity_ + gravity_, 0.0f);
	velocity_ += jumpVector;

}

void Player::correctPosition()
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

bool Player::change_State_and_Anim(Player_State state, Player_Animation animID, float animFrame,float animSpeed,bool isLoop)
{
	if (!change_State(state))return false;
	changeAnimation(animID,animFrame, animSpeed,isLoop);

	return true;
}

bool Player::change_State(Player_State state)
{
	//��Ԃ��ς��Ȃ��Ȃ玸�s
	if (state_ == state)return false;

	//��Ԃ̏I���������s��
	playerEndModeFunc_[state_]();
	//��Ԃ��X�V
	state_ = state;
	//��ԕύX���s��
	playerToNextModeFunc_[state_]();
	//�X�V����
	return true;
}

void Player::idle_Update(float deltaTime)
{
	Vector2 move = DualShock4Manager::GetInstance().GetAngle();
	//Vector2 move = getSticktoMove();
	if (std::abs(move.x) > ignoreSlope || std::abs(move.y) > ignoreSlope) {
		if (change_State_and_Anim(Player_State::Move, Player_Animation::Move_Forward))playerUpdateFunc_[state_](deltaTime);
		return;
	}
	if (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::R1)) {
		if (change_State_and_Anim(Player_State::Shoot, Player_Animation::Shoot))playerUpdateFunc_[state_](deltaTime);
		return;
	}
	if (isChangeStep()) {
		if (change_State_and_Anim(Player_State::Step, Player_Animation::Step_Left))playerUpdateFunc_[state_](deltaTime);
		return;
	}
	upVelocity_ -= upVelocity_*0.5f;

	gravityUpdate(deltaTime);

}

void Player::move_Update(float deltaTime)
{
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);

	Vector3 framevelocity{ 0.0f,0.0f,0.0f };
	Vector2 move = DualShock4Manager::GetInstance().GetAngle();
	//Vector2 move = getSticktoMove();
	if (std::abs(move.x) < ignoreSlope && std::abs(move.y) < ignoreSlope) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle))playerUpdateFunc_[state_](deltaTime);
		return;
	}
	framevelocity.x += move.x*movePower;
	framevelocity.z += move.y*movePower;

	if (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::R1)) {
		if (change_State_and_Anim(Player_State::Shoot, Player_Animation::Shoot))playerUpdateFunc_[state_](deltaTime);
		return;
	}

	if (isChangeStep()) {
		if (change_State_and_Anim(Player_State::Step, Player_Animation::Step_Left))playerUpdateFunc_[state_](deltaTime);
		return;
	}

	upVelocity_ -= upVelocity_*0.5f;

	velocity_ += framevelocity;

	gravityUpdate(deltaTime);

}

void Player::step_Update(float deltaTime)
{
	if (!isChangeStep()) {
		if (nextStep_ != 0) {
			//�_���X���������Ă���Ή������A�j���[�V�������Đ�(���s�����̊֌W�ł����ł�State�̕ύX�̂ݍs���A�����Ŏ��s�����to_StepSuccess�ɂăA�j���[�V�������X�V����)
			if (change_State(Player_State::Step_Success))playerUpdateFunc_[state_](deltaTime);
			return;
		}
		else {
			if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle))playerUpdateFunc_[state_](deltaTime);
			return;
		}
	}

	gyroCheck_.update();
	Vector2 rotate = gyroCheck_.getRotate();
	if (abs(rotate.y) >= 270.0f) {
		//1��]����
		successStep_ = 3;
	}
	else if (rotate.y >= 160.0f)successStep_ = 2;
	else if (rotate.y >= 90.0f&&successStep_ != 2)successStep_ = 1;

	if (std::abs(gyroCheck_.getAngle()) >= 300.0f) {
		successStep_ = 4;
		nextStep_ = successStep_;
		gyroCheck_.initAngle();
	}
	if (DualShock4Manager::GetInstance().GetAngle3D().z > 45.0f&&DualShock4Manager::GetInstance().GetAngle3D().z <= 100.0f) {
		gyroCheck_.initRotate();
		nextStep_ = successStep_;
	}

}

void Player::stepSuccess_Update(float deltaTime)
{
	timeCount_ -= deltaTime;
	//�X�e�b�v���I��������ҋ@��Ԃɖ߂�
	if (timeCount_ <= 0.0f) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle))playerUpdateFunc_[state_](deltaTime);
		return;
	}
}

void Player::attack_Update(float deltaTime)
{
	timeCount_ -= deltaTime;
	//�X�e�b�v���I��������ҋ@��Ԃɖ߂�
	if (timeCount_ <= 0.0f) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle))playerUpdateFunc_[state_](deltaTime);
		return;
	}
	stepAttack(deltaTime);

	shootAngle_ += 5.0f;

	Vector3 baseRotatePos = bulletDistance;
	position_ = centerPosition_ + (baseRotatePos *rotation_* Matrix::CreateRotationY(-shootAngle_));
	//��]���X�V
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -20.0f*turnPower_);

	Vector3 rotatePos = -bulletDistance;
	*bulletPosition_ = centerPosition_ + (rotatePos *rotation_* Matrix::CreateRotationY(-shootAngle_));


}

void Player::shoot_Update(float deltaTime)
{
	shootAngle_ += 5.0f;
	Vector3 baseRotatePos = bulletDistance + bulletDistance*(1 - (MathHelper::Abs(180.f - shootAngle_) / 180.0f)) * spinPower;
	position_ = centerPosition_ + (baseRotatePos *rotation_* Matrix::CreateRotationY(-shootAngle_));
	//��]���X�V
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -20.0f*turnPower_);

	Vector3 rotatePos = -bulletDistance + -bulletDistance*(1-(MathHelper::Abs(180.f - shootAngle_) / 180.0f))*spinPower;
	*bulletPosition_ = centerPosition_ + (rotatePos *rotation_* Matrix::CreateRotationY(-shootAngle_));
	//��]���X�V
	*bulletRotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -20.0f*turnPower_);

	if (shootAngle_ >= 360.0f) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Move_Forward))playerUpdateFunc_[state_](deltaTime);
		return;

	}
}

void Player::shootend_Update(float deltaTime)
{
	if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle))playerUpdateFunc_[state_](deltaTime);
}

void Player::knockback_Update(float deltaTime)
{
}

void Player::down_Update(float deltaTime)
{
	timeCount_ += deltaTime;

	if (timeCount_ >= downTime_) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle))playerUpdateFunc_[state_](deltaTime);
	}
}

void Player::turn_Update(float deltaTime)
{
	if (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::R1)) {
		rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), 5.0f);
	}

}

void Player::stumble_Update(float deltaTime)
{
	timeCount_ += deltaTime;
	//��낯���Ԃ��_�E�����Ԃɓ��B������]�|
	if (timeCount_ >= fallTime) {
		//�]�|����������
		downTime_ = downTime;//�_�E�����Ԑݒ�
		if (change_State_and_Anim(Player_State::Down, Player_Animation::Down,0.f,1.f,false))playerUpdateFunc_[state_](deltaTime);

	}

	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -5.0f);

	Vector3 framevelocity{ 0.0f,0.0f,0.0f };
	Vector2 move = DualShock4Manager::GetInstance().GetAngle();
	//Vector2 move = getSticktoMove();
	//��낯�C����������������
	if (Vector3::Angle(Vector3(stumbleDirection_.x,0.0f,stumbleDirection_.y),Vector3(move.x,0.0f,move.y))<=20.0f&&move.Length()>=0.2f) {
		stumbleRegistTimer_ += deltaTime;
		if (stumbleRegistTimer_ >= defStumbleResurrectTime) {
			if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle))playerUpdateFunc_[state_](deltaTime);
			return;
		}
	}
	else {
		stumbleRegistTimer_ = 0.0f;
	}
	framevelocity.x += move.x*movePower;
	framevelocity.z += move.y*movePower;

	upVelocity_ -= upVelocity_*0.5f;

	velocity_ += framevelocity;

	gravityUpdate(deltaTime);

}

void Player::to_IdleMode()
{

}

void Player::to_MoveMode()
{

}
void Player::to_StepMode()
{
	//�W���X�g����^�C�~���O�Ȃ�X�R�A���Z�t���O��L���ɂ���
	isJustStep_ = isJustTiming();

	gyroCheck_.initialize();
	successStep_ = 0;
	nextStep_ = 0;
}

void Player::to_StepSuccessMode()
{
	int key=EffekseerManager::GetInstance().PlayEffect3D(EFFECT_ID::STEP_SUCCESS_EFFECT, centerPosition_, Vector3::Zero, Vector3::One*10.0f);
	EffekseerManager::GetInstance().SetPositionTrackTarget(EFFECT_ID::STEP_SUCCESS_EFFECT,key, &position_);
	//�X�R�A���Z���Ăяo��(�X�e�b�v�J�n���_�ŃW���X�g����ɍ����Ă��Ȃ���������Z����Ȃ�)
	if (isJustStep_) {
		world_->getCanChangedScoreManager().addScore(playerNumber_, stepAnimScoreList_.at(nextStep_).second);
	}

	changeAnimation(stepAnimScoreList_.at(nextStep_).first);

	//�Ή������A�j���[�V�����̏I�����Ԃ��擾����
	timeCount_ = animation_.GetAnimMaxTime((int)stepAnimScoreList_.at(nextStep_).first);

	if (nextStep_ == 2) {
		change_State_and_Anim(Player_State::Attack, stepAnimScoreList_.at(nextStep_).first);
		return;
	}
	if (nextStep_ == 4) {
		change_State_and_Anim(Player_State::Shoot, stepAnimScoreList_.at(nextStep_).first);
		return;
	}

}

void Player::to_AttackMode()
{
	shootAngle_ = 0.0f;
	
	changeAnimation(stepAnimScoreList_.at(nextStep_).first);

	//�Ή������A�j���[�V�����̏I�����Ԃ��擾����
	timeCount_ = animation_.GetAnimMaxTime((int)stepAnimScoreList_.at(nextStep_).first);

	std::list<ActorPtr> enemys;
	world_->findActors("Enemy", enemys);

	attackTarget_ = enemys.front();
	for (auto& e : enemys) {
		if (Vector3::Distance(centerPosition_, attackTarget_->position()) > Vector3::Distance(centerPosition_, e->position())) {
			attackTarget_ = e;
		}
	}

}

void Player::to_ShootMode()
{
	shootAngle_ = 0.0f;
	Vector3 shootVector = *bulletPosition_ - position_;
	shootVector = shootVector.Normalize();
	bulletVelocity_ = shootVector*(turnPower_*defaultTurnPower);
}

void Player::to_ShootEndMode()
{

}

void Player::to_KnockBackMode()
{

}

void Player::to_DownMode()
{
	timeCount_ = 0.0f;
}

void Player::to_TurnMode()
{
}

void Player::to_StumbleMode()
{
	timeCount_ = 0.0f;
	stumbleRegistTimer_ = 0.0f;
}

void Player::end_IdleMode()
{
}

void Player::end_MoveMode()
{
}

void Player::end_StepMode()
{
}

void Player::end_StepSuccessMode()
{
}

void Player::end_AttackMode()
{
}

void Player::end_ShootMode()
{
}

void Player::end_ShootEndMode()
{
}

void Player::end_KnockBackMode()
{
}

void Player::end_DownMode()
{
}

void Player::end_TurnMode()
{
}

void Player::end_StumbleMode()
{
}

void Player::stepAttack(float deltaTime)
{
	centerPosition_ += (attackTarget_->position() - centerPosition_).Normalize() *2.f;
}

void Player::changeAnimation(Player_Animation animID,float animFrame, float animSpeed,bool isLoop) {
	animation_.ChangeAnim((int)animID, animFrame, animSpeed, isLoop);
}

bool Player::isChangeStep() const
{
	return  {
		(
		InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::A) ||
		InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::B) ||
		InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::X) ||
		InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::Y)
		)
		&&
		InputChecker::GetInstance().GetPovAngle() != -1
	};
}
bool Player::isCanStamble() const
{
	if (state_ == Player_State::Idle || state_ == Player_State::Move || state_ == Player_State::Step)return true;
	if (state_ == Player_State::Step_Success && (nextStep_ != 2 && nextStep_ != 4))return true;
	return false;
}

bool Player::isAttack()
{
	return state_==Player_State::Attack || state_==Player_State::Shoot;
}

bool Player::isRequiredCheckPosture() const
{
	return state_==Player_State::Idle||state_==Player_State::Move;
}

bool Player::isCanTracking() const
{
	//���ˎ��ȊO�͒Ǐ]����
	return state_!=Player_State::Shoot;
}

void Player::bulletUpdate(float deltaTime)
{
	*bulletPosition_ = centerPosition_ + (-bulletDistance*rotation_);
	
	*bulletRotation_ = rotation_*Matrix::CreateFromAxisAngle(rotation_.Up(),180.0f);
	//*bulletRotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), -20.0f*turnPower_);

}

void Player::createCircleEffect()
{
	std::shared_ptr<CircleEffect> circleEffect = std::make_shared<CircleEffect>(40.0f, justEffectStartTime);
	world_->addActor(ActorGroup::EFFECT, std::make_shared<TrackingEffectActor>(world_,"CircleEffect", centerPosition_, circleEffect,shared_from_this()));
}

Vector2 Player::getSticktoMove()
{
	Vector2 result = InputChecker::GetInstance().Stick();
	result.y = -result.y;
	return result;

}

Vector2 Player::mathStumbleDirection(const Vector2 & stumbleDirection)
{
	
	Vector2 result = Vector2::Zero;

	Vector2 base = Vector2::One;
	Vector2 target = stumbleDirection;

	base = base.Normalize();
	target = target.Normalize();

	float cross = Vector2::Cross(base, target);
	float dot = Vector2::Dot(base, target);
	dot = MathHelper::ACos(dot);
	

	//�E��+
	if (cross >= 0) {
		dot *= -1;
	}
	if (dot >= 0 && dot <= 90) {
		result = Vector2::Left;
	}
	if (dot >= 90 && dot <= 180) {
		result = Vector2::Up;
	}
	if (dot <= 0 && dot >= -90) {
		result = Vector2::Down;
	}
	if (dot <= -90 && dot >= -180) {
		result = Vector2::Right;
	}
	return result;
}

bool Player::isJustTiming() const
{
	//return world_->getCanChangedTempoManager().getBeatCount() % 3 == 0;
	return (world_->getCanChangedTempoManager().getBeatCount() % 3) != 0;
}
