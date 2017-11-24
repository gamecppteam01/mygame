#include "Actor.h"
#include <algorithm>

#include "Body/Base/DummyBody.h"
#include "Body/Base/HitInfo.h"
#include "../World/IWorld.h"
#include"../Field/Field.h"

#include "../Define.h"

// コンストラクタ
Actor::Actor(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body) :
	world_(world),
	name_(name),
	position_(position),
	rotation_(Matrix::Identity),
	body_(body),
	dead_(false),
	modelHandle_(MODEL_ID::DUMMY_MODEL),
	motionID_(-1),
	motionSpeed_(1.0f),
	hitNum_(0),
	previousPosition_(Vector3::Zero),
	currentPosition_(Vector3::Zero) {
}

// コンストラクタ
Actor::Actor(const std::string& name) :
	world_(nullptr),
	name_(name),
	position_(Vector3::Zero),
	rotation_(Matrix::Identity),
	body_(std::make_shared<DummyBody>()),
	dead_(false),
	modelHandle_(MODEL_ID::DUMMY_MODEL),
	motionID_(-1),
	motionSpeed_(1.0f),
	hitNum_(0),
	previousPosition_(Vector3::Zero),
	currentPosition_(Vector3::Zero) {
}


void Actor::initialize()
{
}

// 更新
void Actor::update(float deltaTime) {
	onUpdate(deltaTime);
	eachChildren([&](Actor& child) { child.update(deltaTime); });

	previousPosition_ = position_;
}

// 描画
void Actor::draw() const {
	onDraw();
	eachChildren([&](const Actor& child) { child.draw(); });
}


// 衝突判定
void Actor::collide(Actor& other) {
	if (isCollide(other)) {
		onCollide(other);
		other.onCollide(*this);
	}
	eachChildren([&](Actor& child) { child.collide(other); });
}

void Actor::collideResult()
{
	onCollideResult();
	eachChildren([&](Actor& child) { child.collideResult(); });
}


// 死亡しているか？
bool Actor::isDead() const {
	return dead_;
}

// 死亡する
void Actor::dead() {
	dead_ = true;
}

// 名前を返す
const std::string& Actor::getName() const {
	return name_;
}

// 座標を返す
Vector3& Actor::position() {
	return position_;
}

Vector3 Actor::prevPosition()
{
	return previousPosition_;
}

// 回転行列を返す
Matrix& Actor::rotation() {
	return rotation_;
}

// 変換行列を返す
Matrix Actor::getPose() const {
	return Matrix(rotation_).Translation(position_);
}

// 子の検索
ActorPtr Actor::findCildren(const std::string& name) {
	return findCildren(
		[&](const Actor& actor) { return actor.getName() == name; });
}

// 子の検索
ActorPtr Actor::findCildren(std::function<bool(const Actor&)> fn) {
	const auto i = std::find_if(children_.begin(), children_.end(),
		[&](const ActorPtr& child) { return fn(*child); });
	if (i != children_.end()) {
		return *i;
	}
	for (const auto& child : children_) {
		const auto actor = child->findCildren(fn);
		if (actor != nullptr) {
			return actor;
		}
	}
	return nullptr;
}

void Actor::findCildren(const std::string & name, std::list<ActorPtr>& actorList)
{
	for (auto& c : children_) {
		if (c->getName() == name) {
			actorList.push_back(c);
		}
	}
}
void Actor::findCildren(const std::string & name, std::list<std::weak_ptr<Actor>>& actorList)
{
	for (auto& c : children_) {
		if (c->getName() == name) {
			actorList.push_back(c);
		}
	}
}

// 子の衝突判定
void Actor::collideChildren(Actor& other) {
	eachChildren(
		[&](Actor& my) {
		other.eachChildren([&](Actor& target) { my.collide(target); });
	});
}

// 子の衝突判定
void Actor::collideSibling() {
	for (auto i = children_.begin(); i != children_.end(); ++i) {
		std::for_each(std::next(i), children_.end(),
			[&](const ActorPtr& actor) { (*i)->collide(*actor); });
	}
}

// 子の追加
void Actor::addChild(const ActorPtr& child) {
	children_.push_front(child);
}

// 子を巡回
void Actor::eachChildren(std::function<void(Actor&)>  fn) {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

// 子を巡回 (const版）
void Actor::eachChildren(std::function<void(const Actor&)> fn) const {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

// 子を削除
void Actor::removeChildren() {
	removeChildren([](Actor& child) { return child.isDead(); });
	eachChildren([](Actor& child) { child.removeChildren(); });
}

// 子を削除
void Actor::removeChildren(std::function<bool(Actor&)> fn) {
	children_.remove_if(
		[&](const ActorPtr& child) { return fn(*child); });
}

// 子を消去
void Actor::clearChildren() {
	children_.clear();
}

// モーションの設定
void Actor::setMotion(const int motion, const float speed) {
	motionID_ = motion;
	motionSpeed_ = speed;
}

// Worldの取得
IWorld* Actor::getWorld() {
	return world_;
}

// 判定の形の取得
IBodyPtr Actor::getBody() {
	return body_;
}

// 速度を返す
Vector3 Actor::velocity() {
	return position_ - previousPosition_;
}

// 床に衝突したか
bool Actor::isOnFloor() const {
	return hitNum_ > 0;
}

// メッセージ処理
void Actor::handleMessage(EventMessage message, void* param) {
	onMessage(message, param);
	eachChildren([&](Actor& child) { child.handleMessage(message, param); });
}

void Actor::receiveNotification(Notification start)
{
	switch (start)
	{
	case Notification::Call_CreateJustEffect: {
		CreateJustEffect();
		break;
	}
	case Notification::Call_JustStep: {
		JustStep();
		break;
	}
	default:
		break;
	}

}

// フィールドとの衝突判定
bool Actor::field(Vector3& result) {
	Vector3 hitcenter;
	if (world_->getField()->getMesh().collide_capsule(position_ + body_->points(0), position_ + body_->points(1), body_->radius(), (VECTOR*)&hitcenter))
	{
		result = hitcenter;

		return true;
	}
	return false;
}

void Actor::CreateJustEffect()
{
}

void Actor::JustStep()
{
}

// 壁との衝突判定
bool Actor::wall_hit_check(Vector3 & pos, std::vector<MV1_COLL_RESULT_POLY*> walls) {
	// 衝突フラグ
	bool hitFlag = false;

	// 移動ベクトル
	Vector3 dir = currentPosition_ - previousPosition_;

	// 移動したかどうかで処理を分岐
	if (dir.Horizontal().Length() <= 0) return false;

	// 壁ポリゴンの数だけ繰り返し
	for (int i = 0; i < walls.size(); i++) {
		// ポリゴンとプレイヤーが当たっていなかったら次のカウントへ
		if (!(hitFlag = hit_check_cap_tri(currentPosition_, walls[i]->Position))) continue;

		// 壁に当たったら壁に遮られない移動成分分だけ移動する
		// プレイヤーをスライドさせるベクトル
		Vector3 polyNormal = Vector3::VECTORToVector3(walls[i]->Normal);

		// 進行方向ベクトルと壁ポリゴンの法線ベクトルに垂直なベクトルを算出
		Vector3 slideVec = Vector3::Cross(dir, polyNormal);

		// 算出したベクトルと壁ポリゴンの法線ベクトルに垂直なベクトルを算出、これが
		// 元の移動成分から壁方向の移動成分を抜いたベクトル
		slideVec = Vector3::Cross(polyNormal, slideVec);

		// それを移動前の座標に足したものを新たな座標とする
		currentPosition_ = previousPosition_ + slideVec;

		// 新たな移動座標で壁ポリゴンと当たっていないかどうかを判定する
		for (int j = 0; j < walls.size(); j++) {
			// 当たっていたらループから抜ける
			if (hit_check_cap_tri(currentPosition_, walls[j]->Position)) break;
		}
	}

	// 壁に当たっていたら壁から押し出す処理を行う
	if (!hitFlag) return false;

	// 壁ポリゴンの数だけ繰り返し
	for (int i = 0; i < walls.size(); i++) {
		// プレイヤーと当たっているかを判定
		if (!hit_check_cap_tri(currentPosition_, walls[i]->Position)) continue;

		// 当たっていたら規定距離分プレイヤーを壁の法線方向に移動させる
		currentPosition_ = currentPosition_ + Vector3::VECTORToVector3(walls[i]->Normal);

		// 移動した上で壁ポリゴンと接触しているかどうかを判定
		for (int j = 0; j < walls.size(); j++) {
			// 当たっていたらループを抜ける
			if (hit_check_cap_tri(currentPosition_, walls[j]->Position)) break;
		}
	}

	return hitFlag;
}

// 床との衝突判定
bool Actor::floor_hit_check(Vector3 & pos, std::vector<MV1_COLL_RESULT_POLY*> floors) {
	// 床ポリゴンに当たったかどうかのフラグを倒しておく
	bool hitFlag = false;

	float MaxY = 0.0f;

	// 床ポリゴンの数だけ繰り返し
	for (int i = 0; i < floors.size(); i++) {
		// 走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定( 傾斜で落下状態に移行してしまわない為 )
		HITRESULT_LINE LineRes = HitCheck_Line_Triangle(Vector3::Vector3ToVECTOR(currentPosition_), Vector3::Vector3ToVECTOR(currentPosition_ + Vector3::Up * PERSON_HEIGHT), floors[i]->Position[0], floors[i]->Position[1], floors[i]->Position[2]);

		// 当たっていなかったら何もしない
		if (LineRes.HitFlag == FALSE) continue;

		// 既に当たったポリゴンがあり、且つ今まで検出した床ポリゴンより低い場合は何もしない
		if (hitFlag && MaxY > LineRes.Position.y) continue;

		// ポリゴンに当たったフラグを立てる
		hitFlag = true;

		// 接触したＹ座標を保存する
		MaxY = LineRes.Position.y;
	}

	// 床ポリゴンに当たったかどうかで処理を分岐
	if (!hitFlag) return false;

	// 接触したポリゴンで一番高いＹ座標をプレイヤーのＹ座標にする
	currentPosition_.y = MaxY;

	return hitFlag;
}

// カプセルとポリゴンとの衝突判定
bool Actor::hit_check_cap_tri(const Vector3& actor, const VECTOR poly[]) {
	return HitCheck_Capsule_Triangle(Vector3::Vector3ToVECTOR(actor + body_->points(0)), Vector3::Vector3ToVECTOR(actor + body_->points(1)), body_->radius(), poly[0], poly[1], poly[2])==TRUE;
}

bool Actor::hit_check_mesh_line(const Vector3 & start, const Vector3 & end, Vector3 * point, Vector3 * normal) const
{
	//当たっているかを調べて、交点と法線を返す
	const auto coll_poly = MV1CollCheck_Line(world_->getField()->modelHandle(), 0, start, end);
	//交点と法線データを入れる
	if (coll_poly.HitFlag == TRUE) {
		if (point != nullptr) {
			*point = Vector3::VECTORToVector3(coll_poly.HitPosition);
		}
		if (normal != nullptr) {
			*normal = Vector3::VECTORToVector3(coll_poly.Normal);
		}
	}
	return coll_poly.HitFlag == TRUE;

}

// メッセージ処理
void Actor::onMessage(EventMessage, void*) {}

// 更新
void Actor::onUpdate(float) {}

// 描画
void Actor::onDraw() const {
	body_->transform(getPose())->draw();
}

// 衝突した
void Actor::onCollide(Actor&) {}

void Actor::onCollideResult()
{
}

// 衝突判定
bool Actor::isCollide(Actor& other) const {
	//getPoseを通して、自動的に合った判定を作る
	return body_->transform(getPose())->isCollide(*other.getBody()->transform(other.getPose()).get(), HitInfo());
}
