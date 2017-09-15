#pragma once
#include<DxLib.h>
#include"../Vector3.h"
#include"../Matrix.h"
#include"CollisionTriangle.h"
#include<cmath>
#include"../../Graphic/DebugDraw.h"


class CollisionMesh {
public:
	CollisionMesh(int model) :model_{ model } {
	}
	//メッシュと線分の当たり判定
	bool collide_line(const VECTOR& start, const VECTOR& end, VECTOR* point = nullptr, VECTOR* normal = nullptr)const {
		//当たっているかを調べて、交点と法線を返す
		const auto coll_poly = MV1CollCheck_Line(model_, 0, start, end);
		//交点と法線データを入れる
		if (coll_poly.HitFlag == TRUE) {
			if (point != nullptr) {
				*point = coll_poly.HitPosition;
			}
			if (normal != nullptr) {
				*normal = coll_poly.Normal;
			}
		}
		return coll_poly.HitFlag == TRUE;
	}
	//メッシュと球体の当たり判定
	bool collide_sphere(const VECTOR& center, float radius, VECTOR* result = nullptr)const {
		//モデルと球体の当たり判定関数、当たった情報を持つ
		const auto coll_poly = MV1CollCheck_Sphere(model_, 0, center, radius);
		if (coll_poly.HitNum == 0) {
			//衝突判定データの削除、coll_polyはメモリ確保を動的に行っているため、Poly用のdelete代わりの関数を呼ぶ必要がある
			MV1CollResultPolyDimTerminate(coll_poly);
			return false;
		}
		auto result_center = center;
		for (int i = 0; i < coll_poly.HitNum; ++i) {
			//平面と点の衝突関係情報の入れ物
			PLANE_POINT_RESULT plane_point_result;
			//無限平面と点の当たり判定を行う、平面上に一番近い点を調べたりしてくれる
			Plane_Point_Analyse(
				&coll_poly.Dim[i].Position[0],//平面のうち好きな点、平面上であればposition[0]でなくても良い
				&coll_poly.Dim[i].Normal,
				&result_center,
				&plane_point_result//これに無限平面と、自身の点の最も近い点の情報等が入る
				);

			//三角形の中に、無限平面のうち一番近い点が入っているかを調べる=三角形の中に中心点が入っているかを調べる
			if (CollisionTriangle(
				coll_poly.Dim[i].Position[0],
				coll_poly.Dim[i].Position[1],
				coll_poly.Dim[i].Position[2]
				).is_inside(plane_point_result.Plane_MinDist_Pos)) {
				//面に当たってたら、面の法線方向に押し出す、大きさはoffset、めり込み分だけ押し出す
				const auto distance = std::sqrt(plane_point_result.Plane_Pnt_MinDist_Square);
				//法線方向に押し出すベクトルの計算
				const auto offset = VScale(coll_poly.Dim[i].Normal, radius - distance);
				result_center = VAdd(result_center, offset);
			}
		}
		//ポリゴンと辺の判定
		for (int i = 0; i < coll_poly.HitNum; ++i) {
			CollisionTriangle(
				coll_poly.Dim[i].Position[0],
				coll_poly.Dim[i].Position[1],
				coll_poly.Dim[i].Position[2]
				).collide_edge_and_sphere(result_center, radius, &result_center);
		}
		if (result != nullptr) {
			*result = result_center;
		}
		MV1CollResultPolyDimTerminate(coll_poly);
		return true;
	}
	//カプセルとの判定(start=上,end=下)
	bool collide_capsule(const VECTOR& start,const VECTOR& end,float radius, VECTOR* result=nullptr) {
		
		// プレイヤーの周囲にあるポリゴンを検出した結果が代入される当たり判定結果構造体
		MV1_COLL_RESULT_POLY_DIM HitDim = MV1CollCheck_Capsule(model_, -1, start, end, radius);

		if (HitDim.HitNum == 0) {
			// 検出したプレイヤーの周囲のポリゴン情報を開放する
			MV1CollResultPolyDimTerminate(HitDim);
			return false;
		}

		auto result_end = end;
		for (int i = 0; i < HitDim.HitNum; ++i) {
			//平面と点の衝突関係情報の入れ物
			PLANE_POINT_RESULT plane_point_result;
			//無限平面と点の当たり判定を行う、平面上に一番近い点を調べたりしてくれる
			Plane_Point_Analyse(
				&HitDim.Dim[i].Position[0],//平面のうち好きな点、平面上であればposition[0]でなくても良い
				&HitDim.Dim[i].Normal,
				&result_end,
				&plane_point_result//これに無限平面と、自身の点の最も近い点の情報等が入る
			);

			//三角形の中に、無限平面のうち一番近い点が入っているかを調べる=三角形の中に中心点が入っているかを調べる
			if (CollisionTriangle(
				HitDim.Dim[i].Position[0],
				HitDim.Dim[i].Position[1],
				HitDim.Dim[i].Position[2]
			).is_inside(plane_point_result.Plane_MinDist_Pos)) {
				//面に当たってたら、面の法線方向に押し出す、大きさはoffset、めり込み分だけ押し出す
				const auto distance = std::sqrt(plane_point_result.Plane_Pnt_MinDist_Square);
				//法線方向に押し出すベクトルの計算
				const auto offset = VScale(HitDim.Dim[i].Normal, radius - distance);
				result_end = VAdd(result_end, offset);
			}
		}
		//ポリゴンと辺の判定
		for (int i = 0; i < HitDim.HitNum; ++i) {
			CollisionTriangle(
				HitDim.Dim[i].Position[0],
				HitDim.Dim[i].Position[1],
				HitDim.Dim[i].Position[2]
			).collide_edge_and_capsule(start,result_end, radius, &result_end);
		}
		if (result != nullptr) {
			*result = result_end;
		}
		MV1CollResultPolyDimTerminate(HitDim);
		return true;



//		// 移動前の座標を保存
//		previousPosition_ = currentPosition_;
//		// 移動後の座標を算出
//		currentPosition_ = position_;
//
//		// 衝突したポリゴンを格納（壁）
//		std::vector<MV1_COLL_RESULT_POLY*> walls = std::vector<MV1_COLL_RESULT_POLY*>();
//
//		// プレイヤーの周囲にあるポリゴンを検出した結果が代入される当たり判定結果構造体
//		MV1_COLL_RESULT_POLY_DIM HitDim = MV1CollCheck_Capsule(world_->getField()->modelHandle(), -1, Vector3::Vector3ToVECTOR(currentPosition_ + body_->points(0)), Vector3::Vector3ToVECTOR(currentPosition_ + body_->points(1)), body_->radius());
//
//		hitNum_ = HitDim.HitNum;
//
//		// 検出されたポリゴンが壁ポリゴンか床ポリゴン判断し、それぞれ配列に格納
//		for (int i = 0; i < hitNum_; i++) {
//			// 内積で傾き具合を計算
//			float slope = Vector3::Dot(Vector3::VECTORToVector3(HitDim.Dim[i].Normal), Vector3::Up);
//
//			//壁の場合
//			if (slope < HIT_SLOPE_LIMIT) walls.push_back(&HitDim.Dim[i]);
//		}
//
//		// 衝突した壁ポリゴンがない場合return
//		if (!walls.empty()) wall_hit_check(currentPosition_, walls);
//
//		// 検出したプレイヤーの周囲のポリゴン情報を開放する
//		MV1CollResultPolyDimTerminate(HitDim);
//
//		// 新しい座標を保存する
//		position_ = currentPosition_;


	}

private:
	int model_;
};
