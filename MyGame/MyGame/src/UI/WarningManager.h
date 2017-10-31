#pragma once
#include "UI.h"
#include "WarningParamter.h"
#include"../World/IWorld.h"
#include <map>


class Player;

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
	WarningManager(IWorld* world);
	//初期化
	virtual void initialize() override;
	//更新
	virtual void update(float deltaTime) override;
	//描画
	virtual void draw() const override;

	void stateChange(const Vector3& v2);
	void stateChange(const Vector2& v2);

	void stateChange(float angle);

private:
	std::map<warningState, WarningParamter> parameters_;
	warningState state_;
	
	IWorld* world_;

	
	std::weak_ptr<Player> player_;
};