#include "MiniMap.h"
#include<list>
#include"../Input/Keyboard.h"

MiniMap::MiniMap(IWorld* world,const Vector2& position ,const Vector2& map_position)
	:UI{ "MiniMap",position },world_(world), map_position_(map_position){
}

void MiniMap::initialize(){
}

void MiniMap::update(float delta_time){
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::A))isEnd_ = true;
	//Playerの座標を取ってくる
	auto player = world_->findActor("Player");
	player_position_ = { player->position().x,-player->position().z };
	//SpotLightの座標を取ってくる
	auto spotlight = world_->findActor("SpotLight");
	spotLight_position_ = { spotlight->position().x , -spotlight->position().z };
	//Enemyの座標を取ってくる
	enemy_position_.clear();
	std::list<ActorPtr> enemy;
	world_->findActors("Enemy", enemy);
	for (auto i : enemy) {
		Vector2 position = { i->position().x,-i->position().z };
		enemy_position_.push_back(position);
	}
	//Judgeの座標と向きを取ってくる
	JudgeMapDataList_.clear();
	std::list<ActorPtr> judge;
	world_->findActors("Judge", judge);
	for (auto i : judge) {
		Vector2 position = { i->position().x,-i->position().z };
		//向きの計算
		Vector2 V1 = { i->rotation().Forward().x,i->rotation().Forward().z };
		V1.Normalize();
		Vector2 V2 = Vector2::Up;
		V2.Normalize();
		float cross = Vector2::Cross(V1, V2);
		float result = Vector2::Dot(V1, V2);
		result = MathHelper::ACos(result);
		if (cross <= 0) {
			result *= -1;
		}

		JudgeMapDataList_.push_back(JudgeMapData(position, result));
	}
}

void MiniMap::draw() const{
	//本リソースになった時に修正する
	Sprite::GetInstance().Draw(SPRITE_ID::MINIMAP, position_, Vector2::Zero, Vector2(0.6f, 0.6f));
	//ここから下は修正しない
	Sprite::GetInstance().Draw(SPRITE_ID::SPOTLIGHT, spotLight_position_ + map_position_, Sprite::GetInstance().GetSize(SPRITE_ID::SPOTLIGHT) / 2, Vector2::One);
	for (auto i : JudgeMapDataList_) {
		Sprite::GetInstance().Draw(SPRITE_ID::JUDGE_VISION, i.position_ + map_position_, Vector2(25, 0), Vector2::One, i.rotation_);
		Sprite::GetInstance().Draw(SPRITE_ID::JUDGE, i.position_ + map_position_, Sprite::GetInstance().GetSize(SPRITE_ID::JUDGE) / 2, Vector2::One, i.rotation_);
	}
	for (auto i : enemy_position_) {
		Sprite::GetInstance().Draw(SPRITE_ID::ENEMY, i + map_position_, Sprite::GetInstance().GetSize(SPRITE_ID::ENEMY) / 2, Vector2::One);
	}
	Sprite::GetInstance().Draw(SPRITE_ID::PLAYER, player_position_ + map_position_, Sprite::GetInstance().GetSize(SPRITE_ID::PLAYER) / 2, Vector2::One);
}
