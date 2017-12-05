#include "Judgement_SpotLight.h"
#include"../../../World/IWorld.h"
#include"../../Body/BoundingCapsule.h"
#include"../../ActorGroup.h"
#include"../../../Graphic/Model.h"
#include"../../../Math/Math.h"
#include"../../../Graphic/DebugDraw.h"
#include"../../../Define.h"
#include<list>

//コンストラクタ
Judgement_SpotLight::Judgement_SpotLight(IWorld * world, const Vector3 & position)
	:JudgeBase(world, "SpotLight", position){
}

//初期化
void Judgement_SpotLight::initialize(){
}

//メッセージ処理
void Judgement_SpotLight::onMessage(EventMessage message, void * param){
}

//更新
void Judgement_SpotLight::onUpdate(float deltaTime){
}

//描画
void Judgement_SpotLight::onDraw() const{
}

//衝突処理
void Judgement_SpotLight::onCollide(Actor & other){
}

//判定
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
