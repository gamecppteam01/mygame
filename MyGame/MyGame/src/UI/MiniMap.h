#pragma once
#include "../Math/Math.h"
#include "../Graphic/Sprite.h"
#include"../World/World.h"
#include "../UI/UI.h"
#include<list>

class MiniMap : public UI {
public:
	//コンストラクタ
	MiniMap(IWorld* world, const Vector2& position
		,const Vector2& origin);
	//開始
	void initialize() override;
	void update(float delta_time) override;
	//描画
	void draw() const override;

private:
	const Vector2 position_;
	const Vector2 origin_;
	Vector2 player_position_;
	std::list<Vector2> enemy_position_;
	std::list<Vector2> judge_position_;
	IWorld* world_;
};