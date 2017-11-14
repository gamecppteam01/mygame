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
	:JudgeBase(world, "SpotLight", position, std::make_shared<BoundingCapsule>(Vector3(0.0f, 0.0f, 0.0f), Matrix::Identity, 20.0f, 3.0f)){
	initialize();
}

//初期化
void Judgement_SpotLight::initialize(){
	modelHandle_ = MODEL_ID::PLAYER_MODEL;
}

//メッセージ処理
void Judgement_SpotLight::onMessage(EventMessage message, void * param){
}

//更新
void Judgement_SpotLight::onUpdate(float deltaTime){
}

//描画
void Judgement_SpotLight::onDraw() const{
	//判定の中心に描画位置を合わせる
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	//Model::GetInstance().Draw(MODEL_ID::EFFECT_LIGHT_MODEL, position_,1.0f,Vector3::Zero,Vector3(0.5f,1.0f,0.5f));
	//Model::GetInstance().Draw(modelHandle_, Matrix(rotation_).Translation(drawPosition));

	DebugDraw::DebugDrawFormatString(WINDOW_WIDTH/3, WINDOW_HEIGHT/3, GetColor(255, 255, 255), "スポットライト");
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
