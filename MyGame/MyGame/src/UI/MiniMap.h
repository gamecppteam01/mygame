#pragma once
#include "../Math/Math.h"
#include "../Graphic/Sprite.h"
#include"../World/World.h"
#include "../UI/UI.h"
#include<list>

class MiniMap : public UI {
public:
	//�R���X�g���N�^
	MiniMap(IWorld* world, const Vector2& position);
	//�J�n
	void initialize() override;
	void update(float deltaTime) override;
	//�`��
	void draw() const override;

private:
	const Vector2 position_;
	Vector2 scale_{ 0.2f,0.2f };
	Vector2 player_position;
	std::list<Vector2> enemy_position;
    int enemy_Number;
	IWorld* world_;
};