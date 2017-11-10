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

void Enemy_Rival::JustStep() {
	nonTargetResetTimer_.Action();
	if (!isCanStep())return;//�X�e�b�v�s�Ȃ疳��

	rhythmTimeCount_++;

	//�v���C���[���擾���Ă���
	auto player = world_->findActor("Player");

	//�U���Ώۂ̏ꍇ
	if (chooseAttackTargetMode_ ==chooseAttackTargetMode::Attack) {
		chooseStepAttackTarget(player);
		return;
	}
	//�v���C���[��1�ʂ�������
	if (world_->getScoreManager().GetCharacterScore((std::static_pointer_cast<Player>(player))->getPlayerNumber()) == world_->getScoreManager().getMaxScore()) {
		chooseStepAttackTopPlayer(player);
		return;
	}

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
		return;
	}
	//�ʏ펞��6���q��
	int rhythmTime = 6;
	if (rhythmTimeCount_ < rhythmTime)return;
	rhythmTimeCount_ = 0;


	int r = Random::GetInstance().Range(0, 9);
	if (r < 3) {
		//�^�[��
		world_->getCanChangedScoreManager().addScore(playerNumber_, 200);
	}
	else {
		//�N�H�[�^�[
		world_->getCanChangedScoreManager().addScore(playerNumber_, 100);

	}
	change_State_and_Anim(Enemy_State::Step, Enemy_Animation::Move_Forward);

}


void Enemy_Rival::updateNormal(float deltaTime)
{
	//3���ڂ͓����Ȃ�
	if (world_->getCanChangedTempoManager().getBeatCount() % 3 == 2)return;

	position_ += (targetPos_ - position_).Normalize()*movePower;


}

void Enemy_Rival::updateTrack(float deltaTime)
{
	
}

void Enemy_Rival::to_Normal()
{
	targetPos_ = world_->getCanChangedScoreMap().getNearestBonusPoint(position_);

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

void Enemy_Rival::chooseStepAttackTarget(const ActorPtr & player)
{
	Vector3 playerPos = player->position();
	if (Vector3::Distance(player->position(), attackTargetDefaultPos_) >= attackResetDistance) {
		change_State_and_Anim(Enemy_State::Track, Enemy_Animation::Move_Forward);
		chooseAttackTargetMode_ = chooseAttackTargetMode::NotAttack;
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
			targetPos_ = player->position();
		}

	}

}

void Enemy_Rival::chooseStepAttackTopPlayer(const ActorPtr & player)
{
	Vector3 playerPos = player->position();
	//�U���Ώۂ��Œ肵�ď����ʒu���o���Ă���
	attackTargetDefaultPos_ = playerPos;
	attackStartDefaultPos_ = position_;
	chooseAttackTargetMode_ = chooseAttackTargetMode::Attack;
	//�v���C���[���U���͈͓��Ȃ�
	if (Vector3::Distance(position_, playerPos) <= attackDistance) {
		//�v���C���[�ɍU������
		change_State_and_Anim(Enemy_State::Attack, Enemy_Animation::Turn);
		attackTarget_ = player;

	}
	//�͈͊O�Ȃ�
	else {
		//�v���C���[�̂Ƃ��ɋ߂Â�
		targetPos_ = player->position();
	}

}
