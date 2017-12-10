#pragma once
enum class ActorGroup {
	NPC,   //ノンプレイヤー
	PLAYER,//プレイヤー
	PLAYER_BULLET,//パートナー
	TUTORIAL,//チュートリアル用
	ENEMY,//敵
	ENEMY_BULLET,//敵
	EFFECT,//エフェクト
	DUMMYACTOR,//ダミー(空のアクター)


	ACTOR_COUNT//アクター数カウント
};