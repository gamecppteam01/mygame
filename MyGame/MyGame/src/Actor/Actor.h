#pragma once

#include "DxLib.h"

#include "ActorPtr.h"
#include"../Math/Math.h"
#include"Body\Base\IBodyPtr.h"
#include"Body\Base\DummyBody.h"
#include"../Judge/StepTimer.h"
#include"../Game/ID.h"
#include <string>
#include <memory>
#include <functional>
#include <forward_list>
#include <vector>
#include<list>
class IWorld;

class Actor:public std::enable_shared_from_this<Actor>{
public:
	// コンストラクタ
	Actor(IWorld* world, const std::string& name, const Vector3& position = Vector3::Zero, const IBodyPtr& body = std::make_shared<DummyBody>());
	// コンストラクタ
	explicit Actor(const std::string& name = "none");
	// 仮想デストラクタ
	virtual ~Actor() {}
	//初期化(必要なキャラクターのみoverride)
	virtual void initialize();
	void pause();
	void restart();
	virtual void onPause();
	virtual void onRestart();
	// 更新
	void update(float deltaTime);
	// 描画
	void draw() const;
	// 衝突処理
	void collide(Actor& other);
	// 衝突事後処理
	void collideResult();
	// 死亡しているか？
	bool isDead() const;
	// 死亡する
	void dead();
	// 名前を返す
	const std::string& getName() const;
	// 座標を返す
	virtual Vector3& position();
	virtual Vector3 prevPosition();
	// 回転行列を返す
	Matrix& rotation();
	// 変換行列を返す
	Matrix getPose() const;
	// 子の検索
	ActorPtr findCildren(const std::string& name);
	// 子の検索
	ActorPtr findCildren(std::function<bool(const Actor&)> fn);
	// 子の検索及び追加
	void findCildren(const std::string& name, std::list<ActorPtr>& actorList);
	// 子の検索及び追加
	void findCildren(const std::string& name, std::list<std::weak_ptr<Actor>>& actorList);
	// 子の追加
	void addChild(const ActorPtr& child);
	// 子を巡回
	void eachChildren(std::function<void(Actor&)> fn);
	// 子を巡回(const版)
	void eachChildren(std::function<void(const Actor&)> fn) const;
	// 子を削除する
	void removeChildren(std::function <bool(Actor&)> fn);
	// 子を削除する
	void removeChildren();
	// 子を消去
	void clearChildren();
	//子との判定
	void collideChildren(Actor& other);
	//子の判定
	void collideSibling();
	// モーションの設定
	void setMotion(const int motion, const float speed);
	// Worldの取得
	IWorld* getWorld();
	// 速度を返す
	Vector3 velocity();
	//判定の取得
	IBodyPtr getBody();
	// 床に衝突したか
	bool isOnFloor() const;
	// メッセージ処理
	void handleMessage(EventMessage message, void* param);
	//通知処理
	void receiveNotification(Notification start);

	int getCharacterNumber()const { return characterNumber_; }
	void setCharacterNumber(int num) { characterNumber_ = num; }
	// コピー禁止
	Actor(const Actor& other) = delete;
	Actor& operator = (const Actor& other) = delete;
protected:
	// フィールドとの衝突判定(足場と当たった場合はtrueを返す)
	virtual bool field(Vector3& result=Vector3());

protected:
	//エフェクト生成通知の処理
	virtual void CreateJustEffect();
	//ステップ判定通知の処理
	virtual void JustStep();

	// 壁との衝突判定
	bool wall_hit_check(Vector3& pos, std::vector<MV1_COLL_RESULT_POLY*> walls);
	// 床との衝突判定
	bool floor_hit_check(Vector3& pos, std::vector<MV1_COLL_RESULT_POLY*> floors);
	// カプセルとポリゴンとの衝突判定
	bool hit_check_cap_tri(const Vector3& actor, const VECTOR poly[]);
	//メッシュと線分の当たり判定
	bool hit_check_mesh_line(const Vector3& start, const Vector3& end, Vector3* point = nullptr, Vector3* normal = nullptr)const;
private:
	// メッセージ処理
	virtual void onMessage(EventMessage message, void* param);
	// 更新
	virtual void onUpdate(float deltaTime);
	// 描画
	virtual void onDraw() const;
	// 衝突した
	virtual void onCollide(Actor& other);
	// 衝突した後
	virtual void onCollideResult();
	// 衝突判定
	bool isCollide(Actor& other) const;

protected:
	//キャラクター識別番号
	int characterNumber_{ 0 };
	// ワールド
	IWorld*	world_;
	// 名前
	std::string	name_;
	// 座標
	Vector3	position_;
	// 回転
	Matrix	rotation_;
	// 衝突判定
	IBodyPtr body_;
	// 死亡フラグ
	bool dead_;
	// モデルハンドル
	MODEL_ID modelHandle_;
	// モーションID
	int	motionID_;
	// モーション速度
	float motionSpeed_;
	// 移動前の座標
	Vector3	previousPosition_;
	// 現在の座標
	Vector3	currentPosition_;
	// 衝突したポリゴンの数
	int	hitNum_;
private:
	// 子アクター
	std::forward_list<ActorPtr> children_;
};
