#pragma once
#include "../Math/Math.h"
#include "../Graphic/Sprite.h"
#include"../World/World.h"
#include "../UI/UI.h"
#include<list>

class MiniMap : public UI {
public:
	//コンストラクタ
	MiniMap(IWorld* world, const Vector2& position);
	//開始
	void initialize() override;
	void update(float deltaTime) override;
	//描画
	void draw() const override;

private:
	const Vector2 position_;
	Vector2 scale_{ 0.2f,0.2f };
	Vector2 player_position;
	std::list<Vector2> enemy_position;
    int enemy_Number;
	IWorld* world_;
};