#pragma once
#include <string>
#include "../Math/Vector2.h"

class UI {
public:
	//コンストラクタ
	UI(const std::string& name, const Vector2& position );
	//デストラクタ
	virtual ~UI(){}
	//一時停止
	virtual void pause() {};
	//再開
	virtual void restart() {};
	//初期化
	virtual void initialize()=0;
	//更新
	virtual void update(float deltaTime)=0;
	//描画
	virtual void draw() const=0;
	
	//名前を取得
	std::string getName()const;

	bool isEnd()const;
protected:
	//場所
	Vector2 position_;
	//名前
	std::string name_;

	bool isEnd_{ false };
	
};