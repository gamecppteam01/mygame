#pragma once
#include "../Math/Math.h"
#include "../Graphic/Sprite.h"
#include"../World/World.h"
#include "../UI/UI.h"
#include<list>

class MiniMap : public UI {
public:
	//�R���X�g���N�^
	MiniMap(IWorld* world, const Vector2& position
		,const Vector2& origin);
	//�J�n
	void initialize() override;
	void update(float delta_time) override;
	//�`��
	void draw() const override;

private:
	const Vector2 position_;
	const Vector2 origin_;
	Vector2 player_position_;
	std::list<Vector2> enemy_position_;
	std::list<Vector2> judge_position_;
	IWorld* world_;
};