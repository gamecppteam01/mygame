#include "EnemyTemplate.h"
#include"../../Graphic/Model.h"

EnemyTemplate::EnemyTemplate(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr & body):
	Enemy(world,name,position,body)
{
	//�L�����N�^�[�ɂ���Ďg���������f����ID���w�肷�鎖
	modelHandle_ = MODEL_ID::ENEMY_MODEL;
}

void EnemyTemplate::onMessage(EventMessage message, void * param)
{
}

void EnemyTemplate::onUpdate(float deltaTime)
{
	//�e��X�V���s���A���̍X�V���͊e�N���X�̎d�l�ɉ����ė��p�A�ύX���鎖

	animation_.ChangeAnim(1);
	animation_.Update(MathHelper::Sign(deltaTime));

	Vector3 result;
	if (field(result)) {
		gravity_ = 0.0f;
		position_ = result;
	}

}

void EnemyTemplate::onDraw() const
{
	//�`�揈�����s��(���`�揈���͈��)
	
	animation_.Draw();
	//�`��ʒu�𔻒�ƍ��킹��
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	Model::GetInstance().Draw(modelHandle_, Matrix(rotation_).Translation(drawPosition));

	body_->draw(position_);
}

void EnemyTemplate::onCollide(Actor & other)
{
	//�Փˎ��̏������s��
}
