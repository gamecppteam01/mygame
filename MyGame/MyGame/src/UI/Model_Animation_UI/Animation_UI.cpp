#include "Animation_UI.h"
#include "../../Graphic/Model.h"

//コンストラクタ
Animation_UI::Animation_UI(MODEL_ID id, const Vector3 & position)
:position_(position),rotation_(Matrix::Identity * Matrix::CreateRotationY(90)),centerPosition_(position){
	animation_.SetHandle(Model::GetInstance().GetHandle(id));
	animation_.ChangeAnim(0);

	pair_ = std::make_unique<Animaton_UI_Pair>(id, position);
}

//更新
void Animation_UI::Update(float deltaTime){

	rotation_ *= Matrix::CreateRotationY(1);
	position_ = pairDistance*rotation_ + centerPosition_;

	Vector3 pos = centerPosition_ + (-pairDistance*rotation_);
	pair_->setPosition(pos);
	pair_->setRotation(rotation_ *  Matrix::CreateRotationY(180));
	//アニメーション更新
	animation_.Update(MathHelper::Sign(deltaTime) * 0.5f);
	pair_->Update(deltaTime);
}

//描画
void Animation_UI::Draw(){
	animation_.Draw(Matrix(Matrix::Identity)* Matrix(rotation_).Translation(position_));
	pair_->Draw();
}

void Animation_UI::ChangeModel(MODEL_ID & id, MODEL_ID& id2) {
	animation_.SetHandle(Model::GetInstance().GetHandle(id));
	pair_->ChangeModel(id2);
}

void Animation_UI::ChangeStep(int step) {
	animation_.ChangeAnim(step);
	pair_->ChangeStep(step);
}

void Animation_UI::setPosition(Vector3 & position){
	position_ = position;
	pair_->setPosition(position);
}
