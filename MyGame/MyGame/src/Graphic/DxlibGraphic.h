#pragma once

#include<DxLib.h>
#include<math.h>
#include"../Math/Vector3.h"
#include"../Math/Matrix.h"

static void DrawCircleGauge3D(const Vector3& pos,const Vector3& upVector, const int handle, float percent) {
	//100%を0～4の範囲に変換する
	float useparam = fabs(percent) / 25.0f;

	//長さを取得
	int SX, SY;
	GetGraphSize(handle, &SX, &SY);

	for (int i = 0; i < 4; ++i) {
		//25%分(0～1範囲)取り出す
		float ang = useparam;
		if (ang>1.0f)ang = 1.0f;

		//取り出した分だけ大元から減らす
		useparam -= ang;

		VERTEX_3D vec[3];

		Vector3 rotVector = Vector3::Cross(upVector, Vector3::Right);
		//90°毎の回転行列を作成
		Matrix rotMatrix = Matrix::CreateFromAxisAngle(upVector, ang*90.0f + 90.0f*i);
		//位置を指定
		vec[0].pos = pos+ rotVector*Matrix::CreateFromAxisAngle(upVector, 90.0f*i);

		vec[1].pos = pos+rotVector*rotMatrix;

		vec[2].pos = pos;


		//色は暫定
		for (int j = 0; j < 3; ++j) {
			vec[j].a = 255;
			vec[j].r = 255;
			vec[j].g = 255;
			vec[j].b = 255;
		}

		//テクスチャ座標
		vec[0].u = sinf((i + 0)*0.5f*DX_PI_F)*1.0f + 0.5f;
		vec[0].v = cosf((i + 0)*0.5f*DX_PI_F)*1.0f + 0.5f;

		vec[1].u = sinf((i + ang)*0.5f*DX_PI_F)*1.0f + 0.5f;
		vec[1].v = cosf((i + ang)*0.5f*DX_PI_F)*1.0f + 0.5f;

		vec[2].u = 0.5f;
		vec[2].v = 0.5f;

		vec[0].pos = Vector3{ 10.0f,15.0f,0.0f };
		vec[1].pos = Vector3{ 10.0f,15.0f,10.0f };
		vec[2].pos = Vector3{ 0.0f,15.0f,10.0f };

		//描画
		//DrawPolygon3D(vec, 3, handle, TRUE);
		DrawPolygon3D(vec, 1, handle, TRUE);
		//DrawGraph(10, 10, handle, TRUE);
		//角度を消費しきってたら中断
		if (useparam <= 0.0f)break;
	}
}
// paramに負を与えると反対方向、sangleが開始角。
//void DrawMyCircleGauge(const Vector3& pos, const int handle, const float param, const float sangle) {
//	//パラメータを取得
//	float useparam = fabs(param) / 25.0f;
//	int rev = (param>0.0) * 2 - 1;
//
//	//長さを取得
//	int SX, SY;
//	GetGraphSize(handle, &SX, &SY);
//
//	//４つに分ける
//	for (int i = 0; i<4; ++i) {
//		//使用する角度分
//		float ang = useparam;
//		if (ang>1.0f)ang = 1.0f;
//
//		//使用した分だけ消費
//		useparam -= ang;
//
//		//宣言
//		VERTEX_3D vec[3];
//
//		//位置を指定
//		vec[0].pos = x + sinf(sangle + (i + 0)*0.5f*DX_PI_F*rev)*SX - 0.5f;
//		vec[0].y = y + cosf(sangle + (i + 0)*0.5f*DX_PI_F*rev)*SY - 0.5f;
//
//		vec[1].x = x + sinf(sangle + (i + ang)*0.5f*DX_PI_F*rev)*SX - 0.5f;
//		vec[1].y = y + cosf(sangle + (i + ang)*0.5f*DX_PI_F*rev)*SY - 0.5f;
//
//		vec[2].x = (float)x - 0.5f;
//		vec[2].y = (float)y - 0.5f;
//
//
//		//色は暫定
//		for (int j = 0; j<3; ++j) {
//			vec[j].a = 255;
//			vec[j].r = 255;
//			vec[j].g = 255;
//			vec[j].b = 255;
//		}
//
//		//テクスチャ座標
//		vec[0].u = sinf(sangle + (i + 0)*0.5f*DX_PI_F*rev)*1.0f + 0.5f;
//		vec[0].v = cosf(sangle + (i + 0)*0.5f*DX_PI_F*rev)*1.0f + 0.5f;
//
//		vec[1].u = sinf(sangle + (i + ang)*0.5f*DX_PI_F*rev)*1.0f + 0.5f;
//		vec[1].v = cosf(sangle + (i + ang)*0.5f*DX_PI_F*rev)*1.0f + 0.5f;
//
//		vec[2].u = 0.5f;
//		vec[2].v = 0.5f;
//
//		//描画
//		DrawPolygon3D(vec, 3, handle, TRUE, FALSE);
//
//		//角度を消費しきってたら中断
//		if (useparam <= 0.0f)break;
//	}
//}