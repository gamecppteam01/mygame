#include "Animation_UI_pair.h"
#include "../../Graphic/Model.h"

//コンストラクタ
Animaton_UI_Pair::Animaton_UI_Pair(MODEL_ID id, const Vector3& position)
:position_(position),rotation_(Matrix::Identity * Matrix::CreateRotationY(270)){
	animation_.SetHandle(Model::GetInstance().GetHandle(id));
	animation_.ChangeAnim(0);
}

//更新
void Animaton_UI_Pair::Update(float deltaTime){
	//アニメーション更新
	animation_.Update(MathHelper::Sign(deltaTime) * 0.5f);
}

//描画
void Animaton_UI_Pair::Draw() const{
	animation_.Draw(Matrix(Matrix::Identity)* Matrix(rotation_).Translation(position_));
}

void Animaton_UI_Pair::setPosition(Vector3 & position){
	position_ = position;
}

void Animaton_UI_Pair::setRotation(Matrix & rotation){
	rotation_ = rotation;
}

void Animaton_UI_Pair::ChangeModel(MODEL_ID & id){
	animation_.SetHandle(Model::GetInstance().GetHandle(id));
}

void Animaton_UI_Pair::ChangeStep(int step){
	animation_.ChangeAnim(step);
}
