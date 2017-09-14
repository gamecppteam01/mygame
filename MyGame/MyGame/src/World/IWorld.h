#pragma once

#include "../Actor/ActorPtr.h"
#include"../Field/FieldPtr.h"
#include"../Camera/CameraPtr.h"
#include <string>

enum class ActorGroup;
enum class EventMessage;

// ワールド抽象インターフェース
class IWorld {
public:
	// 仮想デストラクタ
	virtual ~IWorld() {}
	// アクターの追加
	virtual void addActor(ActorGroup group, const ActorPtr& actor) = 0;
	// アクターの検索
	virtual ActorPtr findActor(const std::string& name) = 0;
	// メッセージの送信
	virtual void sendMessage(EventMessage message, void* param = nullptr) = 0;
	// フィールドの取得
	virtual FieldPtr getField() const = 0;
	virtual CameraPtr getCamera() = 0;
};
