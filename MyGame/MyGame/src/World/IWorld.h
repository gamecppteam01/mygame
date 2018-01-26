#pragma once

#include "../Actor/ActorPtr.h"
#include"../Field/FieldPtr.h"
#include"../Camera/CameraPtr.h"
#include"../UI/UIPtr.h"
#include"../Game/ID.h"
#include <string>
#include<list>
#include<functional>

enum class ActorGroup;
class ScoreManager;
class ScoreMap;
class TempoManager;
class FieldGrid;
// ワールド抽象インターフェース
class IWorld {
public:
	// 仮想デストラクタ
	virtual ~IWorld() {}
	//検索が必要なクラスの初期化
	virtual void FindInitialize() = 0;
	// アクターの追加
	virtual void addActor(ActorGroup group, const ActorPtr& actor) = 0;
	// アクターの検索
	virtual ActorPtr findActor(const std::string& name) = 0;
	// アクターの複数検索
	virtual void findActors(const std::string& name, std::list<ActorPtr>& actorList) = 0;
	// アクターの複数検索
	virtual void findActors(const std::string& name, std::list<std::weak_ptr<Actor>>& actorList) = 0;
	// メッセージの送信
	virtual void sendMessage(EventMessage message, void* param = nullptr) = 0;
	//描画関数終了後に描画をセットする関数
	virtual void setLateDraw(std::function<void()> draw, bool isBeforeUI=true) = 0;

	virtual void addUI(UIPtr ui) = 0;

	// フィールドの取得
	virtual FieldPtr getField() const = 0;
	virtual CameraPtr getCamera() = 0;
	virtual ScoreManager getScoreManager()const = 0;
	virtual ScoreManager& getCanChangedScoreManager() = 0;
	virtual ScoreMap& getCanChangedScoreMap() = 0;
	virtual void addStepTimeListener(const ActorPtr& actor) = 0;
	virtual TempoManager& getCanChangedTempoManager() = 0;
	virtual TempoManager getTempoManager()const = 0;
	virtual UIPtr findUI(const std::string& name) = 0;
	virtual FieldGrid& getGrid() = 0;
};
