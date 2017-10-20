#pragma once

#include "Actor.h"
#include"ActorPtr.h"
#include <map>
#include<list>

enum class ActorGroup;
enum class ShapeType;

class ActorManager {
public:
	// コンストラクタ
	ActorManager();
	// 初期化
	void initialize();
	// 更新
	void update(float deltaTime);
	// 描画
	void draw() const;
	// アクターの追加
	void addActor(ActorGroup group, const ActorPtr& actor);
	// アクターの検索
	ActorPtr findActor(const std::string& name);
	// アクターの検索
	void findActor(const std::string& name,std::list<ActorPtr>& actorList);
	// メッセージ処理
	void handleMessage(EventMessage message, void* param);
	// コピー禁止
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator = (const ActorManager& other) = delete;
private:
	// 衝突判定
	void collide();
private:
	// ルートノード
	Actor root_;
	// アクターグループ
	std::map<ActorGroup, ActorPtr> actors_;
};
