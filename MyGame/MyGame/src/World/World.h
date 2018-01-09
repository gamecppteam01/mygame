#pragma once

#include "IWorld.h"
#include <functional>
#include"../Actor/ActorManager.h"
#include"../Field/FieldPtr.h"
#include"../Camera/CameraPtr.h"
#include"../Graphic/Light.h"
#include"../Light/LightType.h"
#include"../UI/UIManager.h"
#include"../ScoreManager/ScoreManager.h"
#include"../ScoreManager/ScoreMap.h"
#include"../Sound/TempoManager.h"
#include"../ShadowMap/ShadowMap.h"
#include"../ShadowMap/ShadowMap_Data.h"
#include"../Camera/RoundCamera.h"

// ワールドクラス
class World : public IWorld {
public:
	// コンストラクタ
	World();
	~World();
	//初期化
	void Initialize();
	//検索の必要なクラスの初期化
	virtual void FindInitialize()override;

	void pause();
	void restart();
	// 更新
	void update(float deltaTime);
	void update_end(float deltaTime);
	// 描画
	void draw() const;
	// メッセージ処理
	void handleMessage(EventMessage message, void* param);
	
	//1フレームだけアクター更新
	void init_update();
	// フィールドの追加
	void addField(const FieldPtr& field);
	//カメラの追加
	void addCamera(const CameraPtr& camera);
	void addLight(DirectionalLight light);
	void addLight(SpotLight light);
	void addLight(PointLight light);
	//UIの追加
	virtual void addUI(UIPtr ui) override;
	virtual UIPtr findUI(const std::string& name)override;
	virtual void addStepTimeListener(const ActorPtr& actor) override;
	// フィールドの取得
	virtual FieldPtr getField() const override;
	virtual CameraPtr getCamera() override;
	virtual ScoreManager getScoreManager()const override;
	virtual ScoreManager& getCanChangedScoreManager()override;
	virtual ScoreMap& getCanChangedScoreMap()override;
	virtual TempoManager& getCanChangedTempoManager()override;
	virtual TempoManager getTempoManager()const override;
	// アクターの追加
	virtual void addActor(ActorGroup group, const ActorPtr& actor) override;
	// アクターの検索
	virtual ActorPtr findActor(const std::string& name) override;
	//アクターの一括検索
	virtual void findActors(const std::string& name, std::list<ActorPtr>& actorList) override;
	//アクターの一括検索
	virtual void findActors(const std::string& name, std::list<std::weak_ptr<Actor>>& actorList) override;
	// メッセージの送信
	virtual void sendMessage(EventMessage message, void* param = nullptr)  override;
	// イベントリスナーの追加
	void addEventMessageListener(std::function<void(EventMessage, void*)> listener);
	void end();
	
	virtual void setLateDraw(std::function<void()> draw, bool isBeforeUI = true) override;
	void setShadowMap(const bool flag,const MODEL_ID& id = MODEL_ID::DUMMY_MODEL);

	// コピー禁止
	World(const World& other) = delete;
	World& operator = (const World& other) = delete;

	void roundCam();
	void stopRound();
	bool roundEnd()const { return roundCamera_.isEnd(); }
	RoundCamera& getRoundCam() { return roundCamera_; }
private:
	void normaldraw() const;
	void shadowdraw() const;
private:
	FieldPtr field_;
	CameraPtr camera_;
	RoundCamera roundCamera_;//演出用カメラ
	Light  light_;
	ActorManager actors_;
	UIManager uiManager_;
	ScoreManager scoreManager_;
	//スコア倍率検出マップ
	ScoreMap scoreMap_;
	//ステップ通知
	StepTimer stepTimer_;

	std::list<std::function<void()>> lateDrawFuncList_;
	std::list<std::function<void()>> lateDrawFuncListAfterUI_;

	TempoManager tempo_;
	// イベントリスナー
	std::function<void(EventMessage, void*)> listener_;
	//シャドウマップ
	ShadowMap shadowmap_;
	//シャドウマップのデータ
	ShadowMap_Data shadow_data;
	int ShadowMapHandle;
	bool shadowflag_{ false };
};
