#pragma once

#include "IWorld.h"
#include <functional>
#include"../Actor/ActorManager.h"
#include"../Field/FieldPtr.h"
#include"../Camera/CameraPtr.h"

enum class EventMessage;

// ワールドクラス
class World : public IWorld {
public:
	// コンストラクタ
	World();
	//初期化
	void Initialize();
	// 更新
	void update(float deltaTime);
	// 描画
	void draw() const;
	// メッセージ処理
	void handleMessage(EventMessage message, void* param);
	
	// フィールドの追加
	void addField(const FieldPtr& field);
	void addCamera(const CameraPtr& camera);
	// フィールドの取得
	virtual FieldPtr getField() const override;
	virtual CameraPtr getCamera() override;

	// アクターの追加
	virtual void addActor(ActorGroup group, const ActorPtr& actor) override;
	// アクターの検索
	virtual ActorPtr findActor(const std::string& name) override;
	// メッセージの送信
	virtual void sendMessage(EventMessage message, void* param = nullptr)  override;
	// イベントリスナーの追加
	void addEventMessageListener(std::function<void(EventMessage, void*)> listener);
	void end();
	
	// コピー禁止
	World(const World& other) = delete;
	World& operator = (const World& other) = delete;
private:
	FieldPtr field_;
	CameraPtr camera_;
	ActorManager actors_;
	
	// イベントリスナー
	std::function<void(EventMessage, void*)> listener_;
};

