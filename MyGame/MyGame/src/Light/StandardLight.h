#pragma once
#include"../Math/Vector3.h"
#include"../Math/Color.h"

//標準ライトクラス
class StandardLight {
public:
	//コンストラクタ
	StandardLight();
	//初期化
	void initialize();
	//ライティング計算処理を使用するかどうかを設定する
	void setUseLighting(bool value);
	//グローバルアンビエントカラーを設定する
	void setGlobalAmbientLight(Color& color);
	//標準ライトのタイプをディレクショナルライトにする(方向)
	void changeLightTypeDir(const Vector3& direction);
	//標準ライトのタイプをポイントライトにする(座標、ライトの有効距離、減衰パラメータ0、減衰パラメータ1、減衰パラメータ2)
	void changeLightTypePoint(const Vector3& position, float range, float atten0 = 0.0f, float atten1 = 0.01f, float atten2 = 0.0f);
	//標準ライトのタイプをスポットライトにする(座標、方向、コーンの外角度、コーンの内角度、ライトの有効距離、減衰パラメータ0、減衰パラメータ1、減衰パラメータ2)
	void changeLightTypeSpot(const Vector3& position, const Vector3& direction, float cone_outangle, float cone_inangle, float range, float atten0 = 0.0f, float atten1 = 0.01f, float atten2 = 0.0f);
	//標準ライトの有効、無効をセットする
	void setLightEnable(bool value);
	//標準ライトのディフーズカラーを設定する
	void setLightDiffuseColor(Color& color);
	//標準ライトのスペキュラカラーを設定する
	void setLghtSpecurColor(Color& color);
	//標準ライトのアンビエントカラーを設定する
	void setLightAmbientColor(Color& color);
	//標準ライトの方向を設定する
	void setLightDirection(Vector3& direction);
	//標準ライトの位置を設定する
	void setLightPosition(Vector3& position);
	//標準ライトの有効距離と距離減衰パラメータを設定する
	void setLightRangeAtten(float range, float atten0 = 0.0f, float atten1 = 0.01f, float atten2 = 0.0f);
	//標準ライトの照射角度パラメータを設定する
	void setLightAngle(float outangle, float inangle);
	//標準ライトのタイプを取得する
	int getLightType();
	//標準ライトの有効、無効を取得する
	bool getLightEnable();
	//標準ライトのディフーズカラーを取得する
	Color getLightDiffuseColor();
	//標準ライトのスペキュラカラーを取得する
	Color getLighSpecurColor();
	//標準ライトのアンビエントカラーを取得する
	Color getLightAmbientColor();
	//標準ライトの方向を取得する
	Vector3 getLightDirection();
	//標準ライトの位置を取得する
	Vector3 getLightPosition();
};