//#pragma once
//#include "../world/IWorld.h"
//
//class Actor;
//struct CollisionParameter;
//
//class CollisionFunction
//{
//public:
//	// コンストラクタ
//	explicit CollisionFunction(IWorld* world);
//	// デストラクタ
//	~CollisionFunction();
//
//	// アクターvs壁
//	CollisionParameter Actor_vs_Wall(const Actor& one, const Field& other) const;
//	// アクターvs床
//	CollisionParameter Actor_vs_Floor(const Actor& one, const Actor& other) const;
//	// プレイヤーvsエネミーシンボル
//	CollisionParameter Player_vs_EnemySymboll(const Actor& one, const Actor& other) const;
//	// プレイヤーvsエネミーシンボル
//	CollisionParameter Player_vs_Portal(const Actor& one, const Actor& other) const;
//	// カメラvs壁
//	CollisionParameter Camera_vs_Wall(const Actor& one, const Actor& other) const;
//
//private:
//	// ワールドポインタ
//	IWorld*		world_;
//};