#pragma once
#include"UI.h"
#include"../Actor/Player/Player.h"
#include"StepUIPtr.h"
#include"StepUI.h"
#include"../Graphic/FontManager.h"
#include"../World/World.h"
#include<memory>

class StepUIManager : public UI {
public:
	StepUIManager(IWorld* world);
	//初期化
	void initialize() override;
	//更新
	void update(float deltaTime)override;
	//描画
	void draw()const override;
	//ステップ成功か否か
	bool is_StepSuccess() const;
private:
	IWorld* world_;
	std::weak_ptr<Player> player_;
};