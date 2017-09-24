#include "EnemyTemplate.h"
#include"../../Graphic/Model.h"

EnemyTemplate::EnemyTemplate(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr & body):
	Enemy(world,name,position,body)
{
	//キャラクターによって使いたいモデルのIDを指定する事
	modelHandle_ = MODEL_ID::ENEMY_MODEL;
}

void EnemyTemplate::onMessage(EventMessage message, void * param)
{
}

void EnemyTemplate::onUpdate(float deltaTime)
{
	//各種更新を行う、下の更新文は各クラスの仕様に応じて利用、変更する事

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
	//描画処理を行う(下描画処理は一例)
	
	animation_.Draw();
	//描画位置を判定と合わせる
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	Model::GetInstance().Draw(modelHandle_, Matrix(rotation_).Translation(drawPosition));

	body_->draw(position_);
}

void EnemyTemplate::onCollide(Actor & other)
{
	//衝突時の処理を行う
}
