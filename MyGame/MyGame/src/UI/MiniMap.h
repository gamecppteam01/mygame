#pragma once
#include "../Math/Math.h"
#include "../Graphic/Sprite.h"
#include"../World/World.h"
#include "../UI/UI.h"
#include"JudgeMapData.h"
#include<list>
#include<map>

class MiniMap : public UI {
public:
	//コンストラクタ
	MiniMap(IWorld* world, const Vector2& position
		,const Vector2& map_position);
	//開始
	void initialize() override;
	void update(float delta_time) override;
	//描画
	void draw() const override;

private:
	const Vector2 map_position_;
	Vector2 player_position_;
	Vector2 spotLight_position_;
	std::list<Vector2> enemy_position_;
	std::list<JudgeMapData> JudgeMapDataList_;
	int a = 0;
	IWorld* world_;
};