#include "Judgement_SpotLight.h"
#include"../../../World/IWorld.h"
#include"../../Body/BoundingCapsule.h"
#include"../../ActorGroup.h"
#include"../../../Graphic/Model.h"
#include"../../../Math/Math.h"
#include"../../../Graphic/DebugDraw.h"
#include"../../../Define.h"
#include<list>

//�R���X�g���N�^
Judgement_SpotLight::Judgement_SpotLight(IWorld * world, const Vector3 & position)
	:JudgeBase(world, "SpotLight", position){
}

//������
void Judgement_SpotLight::initialize(){
}

//���b�Z�[�W����
void Judgement_SpotLight::onMessage(EventMessage message, void * param){
}

//�X�V
void Judgement_SpotLight::onUpdate(float deltaTime){
}

//�`��
void Judgement_SpotLight::onDraw() const{
}

//�Փˏ���
void Judgement_SpotLight::onCollide(Actor & other){
}

//����
bool Judgement_SpotLight::Judgement(ActorPtr& target) {
	if (is_In_Distans(target) == true) {
		return true;
	}
	return false;
}

bool Judgement_SpotLight::Judgement(const Vector3 & target)
{
	Vector2 myPos = Vector2(position_.x, position_.z);
	Vector2 targetPos = Vector2(target.x, target.z);
	if (Vector2::Distance(myPos, targetPos) <= 50.0f) {
		return true;
	}
	return false;
}
