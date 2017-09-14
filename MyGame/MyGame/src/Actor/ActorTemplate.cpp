#include "ActorTemplate.h"

ActorTemplate::ActorTemplate(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr & body)
{
	//モデルを利用する場合modelHandle_を設定する
	//例) modelHandle_ = MODEL_ID::DUMMY_MODEL;
}

void ActorTemplate::onMessage(EventMessage message, void * param)
{
	//送られてきたMessageを処理する
	//messageがメッセージの種類、paramは送られてくる値、型に縛りはないため、渡す側、受け取り側で型判断する事
}

void ActorTemplate::onUpdate(float deltaTime)
{
	//更新処理はここで行う、position等の変更
}

void ActorTemplate::onDraw() const
{
	//描画部分の処理はここで行う、メンバ変数の値を変更する事は出来ず
}

void ActorTemplate::onCollide(Actor & other)
{
	//衝突時の処理はここで行う、otherに当たった対象が入る
}
