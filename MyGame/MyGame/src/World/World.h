#pragma once

#include "IWorld.h"
#include <functional>
#include"../Actor/ActorManager.h"
#include"../Field/FieldPtr.h"
#include"../Camera/CameraPtr.h"
#include"../Graphic/Light.h"
#include"../Light/LightType.h"
#include"../UI/UIManager.h"
#include"../Judge/StepTimer.h"
#include"../ScoreManager/ScoreBase.h"

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
	//カメラの追加
	void addCamera(const CameraPtr& camera);
	void addLight(DirectionalLight light);
	void addLight(SpotLight light);
	void addLight(PointLight light);
	//UIの追加
	void addUI(UIPtr ui);
	virtual void addStepTimeListener(const ActorPtr& actor) override;
	// フィールドの取得
	virtual FieldPtr getField() const override;
	virtual CameraPtr getCamera() override;
	virtual StepTimer getStepTimer()const override;
	virtual ScoreBase getScoreBase()const override;
	virtual ScoreBase& getCanChangedScoreBase()override;
	// アクターの追加
	virtual void addActor(ActorGroup group, const ActorPtr& actor) override;
	// アクターの検索
	virtual ActorPtr findActor(const std::string& name) override;
	//アクターの一括検索
	virtual void findActors(const std::string& name,std::list<ActorPtr>& actorList) override;
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
	Light  light_;
	ActorManager actors_;
	UIManager uiManager_;
	ScoreBase scoreManager_;
	//ステップ通知
	StepTimer stepTimer_;
	// イベントリスナー
	std::function<void(EventMessage, void*)> listener_;
};
