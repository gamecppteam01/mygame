//#include "CollisionFunction.h"
//#include "Collision.h"
//#include "CollisionDX.h"
//#include "CollisionParameter.h"
//#include "../dxlib/DXConverter.h"
//#include "../graphic/Model.h"
//#include "../actor/Actor.h"
//#include "../actor/Stage.h"
//
////#include "../util/collision/Line.h"
////#include "../util/collision/Ray.h"
//#include "../../Actor/Body/BoundingSphere.h"
//#include "../util/collision/BoundingBox.h"
//#include "../util/collision/OrientedBoundingBox.h"
//
//CollisionFunction::CollisionFunction(IWorld * world) :
//world_(world)
//{
//}
//
//CollisionFunction::~CollisionFunction()
//{
//}
//
//CollisionParameter CollisionFunction::Actor_vs_Wall(const Actor & one, const Actor & other) const
//{
//	CollisionParameter colpara;
//	colpara.colID = COL_ID::ACTOR_WALL_COL;
//
//	/* パラメータ取得 */
//	// 移動ベクトル
//	auto moveVec = one.GetVelocity();
//	// 今のパラメータ
//	auto nowParam = one.GetParameter();
//
//	// 当たり判定用カプセルデータ
//	Capsule actor(nowParam);
//	// 当たり判定用ステージデータ
//	ModelData stage(Model::GetInstance().GetHandle(static_cast<Stage*>(const_cast<Actor*>(&other))->GetColModelID()));
//
//	// 壁ポリゴン保存ベクター
//	static std::vector<MV1_COLL_RESULT_POLY> walls;
//	walls.clear();
//
//	// 周囲のポリゴンデータを回収
//	colpara = CollisionDX::Model_vs_Capsule(colpara, walls, stage, actor, ModelCollType::Wall);
//
//	// 周囲に壁ポリゴンがなければ終了
//	if (walls.size() == 0)
//	{
//		walls.clear();
//		colpara.colFrag = false;
//		return colpara;
//	}
//
//	// 移動量削減処理
//	for (auto& wall : walls)
//	{
//		// 移動していなければ省略
//		if (moveVec.Length() <= 0.1f) break;
//
//		// 試行数
//		int count = 0;
//		// ポリゴン生成
//		Triangle poly(
//			DXConverter::GetInstance().ToVector3(wall.Position[0]),
//			DXConverter::GetInstance().ToVector3(wall.Position[1]),
//			DXConverter::GetInstance().ToVector3(wall.Position[2]));
//
//		// カプセルとポリゴンが当たっていなければ省略
//		if (!CollisionDX::Capsule_vs_Triangle(actor, poly))	continue;
//		// 移動ベクトルとポリゴンの法線のなす角が鋭角なら省略
//		if (Vector3::Dot(moveVec.Normalize(), DXConverter::GetInstance().ToVector3(wall.Normal)) > 0.0f) continue;
//
//		// 移動量ベクトル
//		Vector3 slideVec;
//		// 移動量から壁による妨害部分を削除
//		slideVec = Vector3::Cross(moveVec, DXConverter::GetInstance().ToVector3(wall.Normal));
//		slideVec = Vector3::Cross(DXConverter::GetInstance().ToVector3(wall.Normal), slideVec);
//
//		/* 押し出し後の情報を反映 */
//		// 今の座標
//		auto pos = nowParam.mat.Translation() + slideVec * 0.025f;
//		nowParam.mat.Translation(pos);
//		actor = Capsule(nowParam);
//
//		// 新しい位置での当たり判定
//		for (auto& w : walls)
//		{
//			// ポリゴン生成
//			Triangle ppoly(
//				DXConverter::GetInstance().ToVector3(w.Position[0]),
//				DXConverter::GetInstance().ToVector3(w.Position[1]),
//				DXConverter::GetInstance().ToVector3(w.Position[2]));
//			// 当たっていたらループから抜ける
//			if (CollisionDX::Capsule_vs_Triangle(actor, ppoly))	break;
//			count++;
//		}
//		// 試行数と壁ポリゴンの数が一緒ならループから抜ける
//		if (count == walls.size())	break;
//	}
//
//	// 押し出し最大挑戦回数
//	static const int MAX_CHALLENGE_COUNT = 64;
//	// 押し出し処理を行う
//	for (int challengeNumber = 0; challengeNumber < MAX_CHALLENGE_COUNT; challengeNumber++)
//	{
//		// 試行数
//		unsigned int count;
//		for (count = 0; count < walls.size(); count++)
//		{
//			// ポリゴン生成
//			Triangle currentPoly(
//				DXConverter::GetInstance().ToVector3(walls.at(count).Position[0]),
//				DXConverter::GetInstance().ToVector3(walls.at(count).Position[1]),
//				DXConverter::GetInstance().ToVector3(walls.at(count).Position[2]));
//
//			// カプセルとポリゴンが当たっていなければ省略
//			if (!CollisionDX::Capsule_vs_Triangle(actor, currentPoly))	continue;
//			// 移動ベクトルとポリゴンの法線のなす角が鋭角なら省略
//			if (Vector3::Dot(moveVec.Normalize(), DXConverter::GetInstance().ToVector3(walls.at(count).Normal)) > 0.0f &&
//				moveVec.Length() <= 0.1f) continue;
//
//			// 壁ポリゴンの法線×規定量移動させる
//			auto pos = nowParam.mat.Translation() + DXConverter::GetInstance().ToVector3(walls.at(count).Normal) * 0.02f;
//			nowParam.mat.Translation(pos);
//			actor = Capsule(nowParam);
//
//			unsigned int k;
//			for (k = 0; k < walls.size(); k++)
//			{
//				// ポリゴン生成
//				auto afterPoly = Triangle(
//					DXConverter::GetInstance().ToVector3(walls.at(k).Position[0]),
//					DXConverter::GetInstance().ToVector3(walls.at(k).Position[1]),
//					DXConverter::GetInstance().ToVector3(walls.at(k).Position[2]));
//				// 当たっていたらループから抜ける
//				if (CollisionDX::Capsule_vs_Triangle(actor, afterPoly))	break;
//			}
//			// 全てのポリゴンと当たっていなかったらループ脱出
//			if (k == walls.size()) break;
//		}
//		// 試行数と壁ポリゴンの数が違っていたらポリゴンと当たっていないためループ脱出
//		if (count != walls.size()) break;
//	}
//
//	// 情報更新
//	colpara.colFrag = true;
//	colpara.colPos = nowParam.mat.Translation();
//	walls.clear();
//
//	return colpara;
//}
//
//CollisionParameter CollisionFunction::Actor_vs_Floor(const Actor & one, const Actor & other) const
//{
//	CollisionParameter colpara;
//	colpara.colID = COL_ID::ACTOR_STAGE_COL;
//
//	/* 当たり判定用データ作成 */
//	// 当たり判定用ステージ
//	ModelData stage(Model::GetInstance().GetHandle(static_cast<Stage*>(const_cast<Actor*>(&other))->GetColModelID()));
//	// 当たり判定用線分
//	Line actor(one.GetParameter().mat.Translation() + Vector3(0.0f, 50.0f, 0.0f), one.GetParameter().mat.Translation() + Vector3(0.0f, -50.0f, 0.0f));
//
//	colpara = CollisionDX::Model_vs_Line(colpara, stage, actor);
//
//	return colpara;
//}
//
//CollisionParameter CollisionFunction::Player_vs_EnemySymboll(const Actor & one, const Actor & other) const
//{
//	CollisionParameter colpara;
//
//	colpara.colID = COL_ID::PLAYER_ENEMYSYMBOL_COL;
//	colpara = CollisionDX::Capsule_vs_Capsule(colpara, Capsule(one.GetParameter()), Capsule(other.GetParameter()));
//
//	return colpara;
//}
//
//CollisionParameter CollisionFunction::Player_vs_Portal(const Actor & one, const Actor & other) const
//{
//	CollisionParameter colpara;
//
//	colpara.colID = COL_ID::PLAYER_PORTAL_COL;
//
//	// プレイヤーからポータルまでの距離
//	Vector3 p = one.GetParameter().mat.Translation() * Vector3(1.0f, 0.0f, 1.0f);
//	Vector3 o = other.GetParameter().mat.Translation() * Vector3(1.0f, 0.0f, 1.0f);
//	float distance = Vector3::Distance(p, o);
//	// プレイヤーの半径とポータルの半径
//	float r = one.GetParameter().radius + other.GetParameter().radius;
//	// 一定距離以上離れている場合衝突していない
//	if (distance >= r)	return colpara;
//
//	// Sphere
//	BoundingSphere sphere(one.GetParameter().mat.Translation(), one.GetParameter().radius);
//	// OBB
//	OrientedBoundingBox box(other.GetParameter().mat.Translation(), other.GetParameter().size,
//		other.GetParameter().mat.Right(), other.GetParameter().mat.Up(), other.GetParameter().mat.Backward());
//	
//	colpara.colFrag = box.Intersects(sphere, &colpara.colPos);
//
//	return colpara;
//}
//
//CollisionParameter CollisionFunction::Camera_vs_Wall(const Actor & one, const Actor & other) const
//{
//	CollisionParameter colpara;
//	colpara.colID = COL_ID::CAMERA_WALL_COL;
//
//	/* 当たり判定用データ作成 */
//	// 当たり判定用ステージ
//	ModelData stage(Model::GetInstance().GetHandle(static_cast<Stage*>(const_cast<Actor*>(&other))->GetColModelID()));
//	/* 当たり判定用線分 */
//	// プレイヤー座標
//	Vector3 playerPos;
//	world_->EachActor(ACTOR_ID::PLAYER_ACTOR, [&](Actor& other)
//	{
//		playerPos = other.GetParameter().mat.Translation() + Vector3(0.0f, other.GetParameter().size.y, 0.0f);
//	});
//	// プレイヤーからカメラへの線分
//	Vector3 currentPos = one.GetParameter().mat.Translation();
//	Line line(playerPos, currentPos);
//	colpara = CollisionDX::Model_vs_Line(colpara, stage, line);
//	// カメラの位置を算出
//	float distance = Vector3::Distance(playerPos, currentPos);
//	float len = Vector3::Distance(playerPos, colpara.colPos);
//	float height = (distance - len) * 0.5f;
//	colpara.colPos += Vector3(0.0f, height, 0.0f);
//
//	return colpara;
//}
