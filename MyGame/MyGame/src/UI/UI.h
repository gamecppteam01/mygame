#pragma once
#include <string>
#include "../Math/Vector3.h"

class UI {
public:
	//コンストラクタ
	UI(const std::string& name, const Vector3& position );
	//デストラクタ
	virtual ~UI(){}

private:
	//初期化
	virtual void onInitialize();
	//更新
	virtual void onUpdate(float deltaTime);
	//描画
	virtual void onDraw() const;

protected:
	//場所
	Vector3 _position;
	//名前
	std::string _name;
	
};