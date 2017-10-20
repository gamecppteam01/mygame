#pragma once
#include "UI.h"
#include "WarningParamter.h"
#include <map>


 enum class warningState {
	UP,
	DOWN,
	RIGHT,
	LEFT,

	None,

};

class WarningManager : public UI {
public:
	//コンストラクタ
	WarningManager();
	//初期化
	virtual void initialize() override;
	//更新
	virtual void update(float deltaTime) override;
	//描画
	virtual void draw() const override;

	void stateChange(const Vector3& v2);

private:
	std::map<warningState, WarningParamter> parameters_;
	warningState state_;
	
	//警告のカウント
	int warningCount_;
	//警告の時間
	float warningTime_;
	
};