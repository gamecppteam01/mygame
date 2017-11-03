#include "MiniMap.h"
#include<list>

MiniMap::MiniMap(IWorld* world,const Vector2 & position 
	,const Vector3& player_position/*,const Vector3& enemy_position*//*, const Vector2& judge_position*/)
	:UI{ "MiniMap",position },position_(position){
	world_ = world;
	player_position_ = { player_position.x,player_position.z };
	//enemy_position_.push_back(enemy_position);
}

void MiniMap::initialize()
{
}

void MiniMap::update(float delta_time)
{
	auto player = world_->findActor("Player");
	player_position_ = { player->position().x,-player->position().z };
	std::list<ActorPtr> enemy;
	enemy_position_.clear();
	world_->findActors("Enemy", enemy);
	for (auto i : enemy) {
		Vector2 position = { i->position().x,-i->position().z };
		enemy_position_.push_back(position);
	}
	std::list<ActorPtr> judge;
	judge_position_.clear();
	world_->findActors("Judge", judge);
	for (auto i : judge) {
		Vector2 position = { i->position().x,-i->position().z };
		judge_position_.push_back(position);
	}
}

void MiniMap::draw() const
{
	//èÍèäÇ∏ÇÁÇµÇƒÇ‡ëÂè‰ïvÇ»ÇÊÇ§Ç…
	Sprite::GetInstance().Draw(SPRITE_ID::MINIMAP, position_, Vector2::Zero, Vector2(0.6f,0.6f));
	Sprite::GetInstance().Draw(SPRITE_ID::PLAYER, player_position_, Sprite::GetInstance().GetSize(SPRITE_ID::PLAYER) / 2 + Vector2(-1100.0f, -170.0f), Vector2::One);
	for (auto i : enemy_position_) {
		Sprite::GetInstance().Draw(SPRITE_ID::ENEMY, i, Sprite::GetInstance().GetSize(SPRITE_ID::ENEMY) / 2 + Vector2(-1100.0f, -170.0f), Vector2::One);
	}
	for (auto i : judge_position_) {
		Sprite::GetInstance().Draw(SPRITE_ID::JUDGE, i, Sprite::GetInstance().GetSize(SPRITE_ID::JUDGE) / 2 + Vector2(-1100.0f, -170.0f), Vector2::One);
	}
}
