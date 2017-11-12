#include "Enemy_Rival.h"
#include"../../../World/IWorld.h"
#include"../../../ScoreManager/ScoreMap.h"
#include"../../../Math/MathHelperSupport.h"
#include"../../../Math/Random.h"
#include"../../../ScoreManager/ScoreManager.h"
#include"../../Player/Player.h"
#include"../../../Sound/TempoManager.h"

static const float attackResetDistance = 40.0f;
Enemy_Rival::Enemy_Rival(IWorld * world, const std::string & name, const Vector3 & position, int playerNumber, const IBodyPtr & body) :
	BaseEnemy(world, name, position, playerNumber, body) {

	roundPoint_ = world_->getCanChangedScoreMap().getRoundPoint();
	targetPos_ = world_->getCanChangedScoreMap().getNearestBonusPoint(position_);

	world_->findActors("Enemy", players_);

	//players���玩�g���폜
	players_.remove_if([&](std::weak_ptr<Actor>& ptr)->bool {
		return ptr.lock()->getCharacterNumber() == getCharacterNumber();
	});
	players_.push_front(world_->findActor("Player"));

}

void Enemy_Rival::onDraw() const
{
	BaseEnemy::onDraw();
	world_->setLateDraw([this] {
		switch (chooseAttackTargetMode_)
		{
		case Enemy_Rival::chooseAttackTargetMode::NotAttack:
			DebugDraw::DebugDrawFormatString(400, 300, GetColor(255, 255, 255), "NotAttack");
			break;
		case Enemy_Rival::chooseAttackTargetMode::AttackMove:
			DebugDraw::DebugDrawFormatString(400, 300, GetColor(255, 255, 255), "AttackMove");
			break;
		case Enemy_Rival::chooseAttackTargetMode::Attack:
			DebugDraw::DebugDrawFormatString(400, 300, GetColor(255, 255, 255), "Attack");
			break;
		case Enemy_Rival::chooseAttackTargetMode::Return:
			DebugDraw::DebugDrawFormatString(400, 300, GetColor(255, 255, 255), "Return");
			break;
		case Enemy_Rival::chooseAttackTargetMode::Step:
			DebugDraw::DebugDrawFormatString(400, 300, GetColor(255, 255, 255), "Step");
			break;
		case Enemy_Rival::chooseAttackTargetMode::StepMove:
			DebugDraw::DebugDrawFormatString(400, 300, GetColor(255, 255, 255), "StepMove");
			break;
		default:
			break;
		}
	});
}

void Enemy_Rival::JustStep() {
	nonTargetResetTimer_.Action();
	if (state_ == Enemy_State::Track) {
		justStepTrack();
		return;
	}
	if (!isCanStep())return;//�X�e�b�v�s�Ȃ疳��

	rhythmTimeCount_++;

	//�v���C���[���擾���Ă���
	auto player = world_->findActor("Player");

	//�ʏ펞��6���q��
	int rhythmTime = 6;
	if (rhythmTimeCount_ < rhythmTime) {
		//�U�����邩�����肷��
		chooseStepIsAttack();
		return;
	}
	rhythmTimeCount_ = 0;

	//�ړ���̃|�C���g����������
	Vector3 nextPos = world_->getCanChangedScoreMap().getNearestBonusPoint(position_);
	//��ʂ̏����擾����
	auto targetScore = world_->getScoreManager().getFirst();

	if (targetScore.target_.lock()->getCharacterNumber() == getCharacterNumber()) {
		toNextStepTrackMode(chooseAttackTargetMode::StepMove);
		change_State_and_Anim(Enemy_State::Track, Enemy_Animation::Move_Forward);

		//change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Move_Forward);
		return;
	}
	//��ʂ̃��[�g���オ���Ă�����
	if (targetScore.scoreRate_ > 1.0f) {
		attackStartDefaultPos_ = player->position();
		attackTargetDefaultPos_ = player->position();
		//��ʂ��U���Ώۂɂ���
		attackTarget_ = targetScore.target_;
		Enemy_Animation nextAnim;
		//�U���̎˒������Ȃ�
		if (Vector3::Distance(position_, attackTarget_.lock()->position()) <= attackDistance) {
			toNextStepTrackMode(chooseAttackTargetMode::AttackMove);
			nextAnim = Enemy_Animation::Move_Forward;
		}
		else {
			toNextStepTrackMode(chooseAttackTargetMode::Attack);
			nextAnim = Enemy_Animation::Idle;
		}
		change_State_and_Anim(Enemy_State::Track, Enemy_Animation::Move_Forward);
		return;
	}
	toNextStepTrackMode(chooseAttackTargetMode::StepMove);
	change_State_and_Anim(Enemy_State::Track, Enemy_Animation::Move_Forward);

	////�U���Ώۂ���ʂ̃L�����N�^�[�ɐݒ肷��
	//auto target = world_->getScoreManager().getFirst().target_;
	////�ړ��悩��͈͓��ɂ�����U�����[�h�ֈڍs
	//if (Vector3::Distance(target.lock()->position(), nextPos) <= attackDistance) {
	//	chooseStepAttackTopPlayer(target.lock(), nextPos);
	//	return;
	//}


	//int r = Random::GetInstance().Range(0, 9);
	//if (r < 3) {
	//	//�^�[��
	//	world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_TURN);
	//}
	//else {
	//	//�N�H�[�^�[
	//	world_->getCanChangedScoreManager().addScore(playerNumber_, SCORE_QUARTER);
	//
	//}
	//change_State_and_Anim(Enemy_State::Step, Enemy_Animation::Move_Forward);

}


void Enemy_Rival::updateNormal(float deltaTime)
{
	//3���ڂ͓����Ȃ�
	if (world_->getCanChangedTempoManager().getBeatCount() % 3 == 2)return;

	position_ += (targetPos_ - position_).Normalize()*movePower;

	//�|�C���g�ɋ߂Â����玟�̃|�C���g�Ɉړ�
	if (Vector3::Distance(position_, targetPos_) <= 10.0f)setNextPosition();

}

void Enemy_Rival::updateTrack(float deltaTime)
{
	switch (chooseAttackTargetMode_)
	{
	case Enemy_Rival::chooseAttackTargetMode::NotAttack: {
		//������I������
		if (change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Move_Forward))updateNormal(deltaTime);
		return;
		break; 
	}
	case Enemy_Rival::chooseAttackTargetMode::AttackMove: {
		//3���ڂ͓����Ȃ�
		if (world_->getCanChangedTempoManager().getBeatCount() % 3 == 2)return;
		
		//�U���ʒu�Ɉړ�����
		position_ += (targetPos_ - position_).Normalize()*movePower;
		//�U���ʒu�ɓ��B������
		if (Vector3::Distance(position_, targetPos_) <= 10.0f) {
			toNextStepTrackMode(chooseAttackTargetMode::Attack);
		}
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::Attack: {
		stepTime_ -= deltaTime;
		//�X�e�b�v���I��������ҋ@��Ԃɖ߂�
		if (stepTime_ <= 0.0f) {
			//�G���͈͊O�ɂ�������
			if (Vector3::Distance(attackTarget_.lock()->position(), attackTargetDefaultPos_) >= 40.0f) {
				toNextStepTrackMode(chooseAttackTargetMode::Return);
			}
			else {
				toNextStepTrackMode(chooseAttackTargetMode::AttackMove);
			}
			return;
		}
		position_ += (attackTarget_.lock()->position() - position_).Normalize() *attackPower;
		break;
	}
	//�X�R�A�擾�ʒu�ɖ߂�												  
	case Enemy_Rival::chooseAttackTargetMode::Return: {
		//3���ڂ͓����Ȃ�
		if (world_->getCanChangedTempoManager().getBeatCount() % 3 == 2)return;
		position_ += (attackStartDefaultPos_ - position_).Normalize()*movePower;
		//�X�e�b�v�ʒu�ֈړ�����
		if (Vector3::Distance(position_, attackStartDefaultPos_) <= 10.0f)toNextStepTrackMode(chooseAttackTargetMode::StepMove);
		break; 
	}
	case Enemy_Rival::chooseAttackTargetMode::Step:{
		stepTime_ -= deltaTime;
		//���Ԃ�������
		if (stepTime_ > 0.0f) return;
		//�ʏ�A�j���ɖ߂�
		defAnimSetTimer_.Action();
		//�X�e�b�v���S���I�������
		if (stepQueue_.empty()) {
			//�ʏ�̏���ɖ߂�
			toNextStepTrackMode(chooseAttackTargetMode::NotAttack);
			return;
		}
		
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::StepMove:{
		//�X�e�b�v�J�n�ʒu�Ɉړ�����
		position_ += (targetPos_ - position_).Normalize()*movePower;
		//�ړI�n�ɓ��B������X�e�b�v���J�n����
		if (Vector3::Distance(position_, targetPos_) <= 10.0f) {
			toNextStepTrackMode(chooseAttackTargetMode::Step);
		}
		break;
	}
	default: {
		if (change_State_and_Anim(Enemy_State::Normal, Enemy_Animation::Move_Forward))updateNormal(deltaTime);
		break;
	}
	}
}

void Enemy_Rival::to_Normal()
{
	targetPos_ = world_->getCanChangedScoreMap().getNearestBonusPoint(position_);
	//setNextPosition();
}

void Enemy_Rival::to_Track()
{
}

void Enemy_Rival::to_Attack(BaseEnemy::Enemy_Animation anim)
{
	stepTime_ = 1.5f;

}

int Enemy_Rival::getNearestPoint(const Vector3 & position)
{
	int result = 0;
	for (int i = 0; i < roundPoint_.size(); i++) {
		//�Ώۃ|�C���g�����݂̃|�C���g���߂����
		if (Vector3::Distance(position, roundPoint_[result]) > Vector3::Distance(position, roundPoint_[i])) {
			//�|�C���g���X�V
			result = i;
		}
	}
	return result;
}

void Enemy_Rival::justStepTrack()
{

	switch (chooseAttackTargetMode_)
	{
	case Enemy_Rival::chooseAttackTargetMode::NotAttack: {
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::AttackMove: {
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::Attack: {
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::Return: {
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::Step: {
		if (stepQueue_.empty())return;

		//1�A�j���[�V���������o��
		int nextStep = stepQueue_.front();
		stepQueue_.pop();
		defAnimSetTimer_.Initialize();
		defAnimSetTimer_.Add([this] {changeAnimation(Enemy_Animation::Move_Forward); });
		changeAnimation(stepAnim[nextStep].first,0.0f,1.0f,false);
		world_->getCanChangedScoreManager().addScore(playerNumber_, stepAnim[nextStep].second);
		//�Ή������A�j���[�V�����̏I�����Ԃ��擾����
		stepTime_ = animation_.GetAnimMaxTime((int)stepAnim[nextStep].first);
		
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::StepMove: {
		break; 
	}
	default: {
		break; 
	}
	}
}

void Enemy_Rival::toNextStepTrackMode(chooseAttackTargetMode nextMode)
{
	chooseAttackTargetMode_ = nextMode;
	switch (chooseAttackTargetMode_)
	{
	case Enemy_Rival::chooseAttackTargetMode::NotAttack: {
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::AttackMove: {
		targetPos_ = attackTarget_.lock()->position();
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::Attack: {
		stepTime_ = 1.5f;
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::Return: {
		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::Step: {
		//�s���X�e�b�v��ݒ�
		stepQueue_.push(0);//�N�H�[�^�[
		stepQueue_.push(2);//�^�[��
		stepQueue_.push(0);//�N�H�[�^�[

		break;
	}
	case Enemy_Rival::chooseAttackTargetMode::StepMove: {
		//�s������ł��߂�����|�C���g�Ɍ���
		targetPos_ = world_->getCanChangedScoreMap().getNearestBonusPoint(position_);
		break;
	}
	default: {
		break;
	}
	}

}

void Enemy_Rival::chooseStepAttackTarget(const ActorPtr & player)
{
	Vector3 playerPos = player->position();
	if (Vector3::Distance(player->position(), attackTargetDefaultPos_) >= attackResetDistance) {
		change_State_and_Anim(Enemy_State::Track, Enemy_Animation::Move_Forward);
		toNextStepTrackMode(chooseAttackTargetMode::NotAttack);
	}
	else {
		if (Vector3::Distance(position_, playerPos) <= attackDistance) {
			//�v���C���[�ɍU������
			change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Turn);
			attackTarget_ = player;

		}
		//�͈͊O�Ȃ�
		else {
			//�v���C���[�̂Ƃ��ɋ߂Â�
			attackTarget_ = player;
			targetPos_ = player->position();
			change_State_and_Anim(Enemy_State::Track, Enemy_Animation::Move_Forward);
		}

	}

}

void Enemy_Rival::chooseStepAttackTopPlayer(const ActorPtr & player,const Vector3 basePos)
{
	Vector3 playerPos = player->position();
	//�U���Ώۂ��Œ肵�ď����ʒu���o���Ă���
	attackTargetDefaultPos_ = playerPos;
	attackStartDefaultPos_ = basePos;
	//�v���C���[���U���͈͓��Ȃ�
	if (Vector3::Distance(position_, playerPos) <= attackDistance) {
		toNextStepTrackMode(chooseAttackTargetMode::Attack);
		//�v���C���[�ɍU������
		change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Turn);
		attackTarget_ = player;

	}
	//�͈͊O�Ȃ�
	else {
		//�v���C���[�̂Ƃ��ɋ߂Â�
		targetPos_ = player->position();
		change_State_and_Anim(Enemy_State::Track, Enemy_Animation::Move_Forward);
	}

}

bool Enemy_Rival::chooseStepIsAttack()
{
	//�ړ�������肷��
	targetPos_ = world_->getCanChangedScoreMap().getNearestBonusPoint(position_);

	bool isAttack = false;
	float nearest = Vector3::Distance(position_, players_.front().lock()->position());
	for (const auto& p : players_) {
		//�͈͓��ɑI�肪���Ȃ���Ύ���
		if (MathHelperSupport::MathDistance_Segment_Point(position_, targetPos_, p.lock()->position()) > attackDistance)continue;
		float dist = Vector3::Distance(position_, p.lock()->position());
		if (dist <= nearest&&prevHitActorNumber_ != p.lock()->getCharacterNumber()) {
			nearest = dist;
			attackTarget_ = p;
			prevHitActorNumber_ = attackTarget_.lock()->getCharacterNumber();
			isAttack = true;
		}
	}
	if (isAttack) {
		change_State_and_Anim(Enemy_State::Attack, stepAnim[1].first);
	}
	return isAttack;

}

void Enemy_Rival::setNextPosition()
{
	//�^�[�Q�b�g�J�E���g��-1����
	nextPoint_ = (nextPoint_ + roundPoint_.size() - 1) % roundPoint_.size();

	//float rate = 1.0f;
	//Vector3 nextPosition = world_->getCanChangedScoreMap().getNextPoint(position_, &rate);
	//if (rate >= 1.05f) {
	//	isGoBonus_ = true;
	//	nextPosition_ = nextPosition + Vector3(Random::GetInstance().Range(-20.f, 20.f), 0.0f, Random::GetInstance().Range(-20.f, 20.f));
	//	return;
	//}
	nextPosition_ = roundPoint_[nextPoint_];

}
void Enemy_Rival::setCountDown()
{
	//�_�E�����ĂȂ���΃_�E���l�~�ς�L����
	if (state_ == Enemy_State::Down||(state_==Enemy_State::Track&&chooseAttackTargetMode_==chooseAttackTargetMode::Attack))return;
	downTimer_.Initialize();
	downTimer_.Add([this] {downCount_--; });
}
