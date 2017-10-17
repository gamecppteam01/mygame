#include "MiniMap.h"
#include<list>

MiniMap::MiniMap(IWorld* world,const Vector2 & position)
	:UI{ "MiniMap",position },position_(position){
	world_ = world;
}

void MiniMap::initialize()
{
}

void MiniMap::update(float deltaTime)
{
	auto player = world_->findActor("Player");
	std::list<ActorPtr> enemy;
	world_->findActors("Enemy",enemy);
	//if (player == nullptr) return;
	//if (enemy == nullptr) return;
	player_position = { player->position().x,-player->position().z };
	enemy_position.clear();
	for (auto i : enemy) {
		Vector2 position = { i->position().x,-i->position().z };
		enemy_position.push_back(position);
	}
}

void MiniMap::draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::MINIMAP, position_, Vector2::Zero, Vector2(0.6f,0.6f));
	Sprite::GetInstance().Draw(SPRITE_ID::PLAYER, player_position, Vector2(-1100,-170), Vector2(1.0,1.0));
	for (auto i : enemy_position) {
		Sprite::GetInstance().Draw(SPRITE_ID::ENEMY, i, Vector2(-1100, -170), Vector2(1.0, 1.0));
	}
}
