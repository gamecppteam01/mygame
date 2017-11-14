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
	:JudgeBase(world, "SpotLight", position, std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f)){
	initialize();
}

//������
void Judgement_SpotLight::initialize(){
	modelHandle_ = MODEL_ID::PLAYER_MODEL;
}

//���b�Z�[�W����
void Judgement_SpotLight::onMessage(EventMessage message, void * param){
}

//�X�V
void Judgement_SpotLight::onUpdate(float deltaTime){
}

//�`��
void Judgement_SpotLight::onDraw() const{
	//����̒��S�ɕ`��ʒu�����킹��
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	//Model::GetInstance().Draw(MODEL_ID::EFFECT_LIGHT_MODEL, position_,1.0f,Vector3::Zero,Vector3(0.5f,1.0f,0.5f));
	//Model::GetInstance().Draw(modelHandle_, Matrix(rotation_).Translation(drawPosition));

	DebugDraw::DebugDrawFormatString(WINDOW_WIDTH/3, WINDOW_HEIGHT/3, GetColor(255, 255, 255), "�X�|�b�g���C�g");
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
