#include "ActorTemplate.h"

ActorTemplate::ActorTemplate(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr & body)
{
	//���f���𗘗p����ꍇmodelHandle_��ݒ肷��
	//��) modelHandle_ = MODEL_ID::DUMMY_MODEL;
}

void ActorTemplate::onMessage(EventMessage message, void * param)
{
	//�����Ă���Message����������
	//message�����b�Z�[�W�̎�ށAparam�͑����Ă���l�A�^�ɔ���͂Ȃ����߁A�n�����A�󂯎�葤�Ō^���f���鎖
}

void ActorTemplate::onUpdate(float deltaTime)
{
	//�X�V�����͂����ōs���Aposition���̕ύX
}

void ActorTemplate::onDraw() const
{
	//�`�敔���̏����͂����ōs���A�����o�ϐ��̒l��ύX���鎖�͏o����
}

void ActorTemplate::onCollide(Actor & other)
{
	//�Փˎ��̏����͂����ōs���Aother�ɓ��������Ώۂ�����
}
