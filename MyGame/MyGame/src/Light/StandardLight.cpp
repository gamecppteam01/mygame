#include "StandardLight.h"
#include<DxLib.h>

//コンストラクタ
StandardLight::StandardLight(){
	initialize();
}

//初期化
void StandardLight::initialize() {
	setUseLighting(true);
	setLightEnable(true);
}

//ライティング計算処理を使用するかどうかを設定する
void StandardLight::setUseLighting(bool value) {
	SetUseLighting(value);
}

//ピクセルシェーダでライティング計算をするかどうか設定する
void StandardLight::setUsePixelLighting(bool valeu) {
	SetUsePixelLighting(valeu);
}


//グローバルアンビエントカラーを設定する
void StandardLight::setGlobalAmbientLight(Color& color) {
	SetGlobalAmbientLight(GetColorF(color.r, color.g, color.b, color.a));
}

//標準ライトのタイプをディレクショナルライトにする(方向)
void StandardLight::changeLightTypeDir(const Vector3& direction) {
	ChangeLightTypeDir(VGet(direction.x, direction.y, direction.z));
}

//標準ライトのタイプをポイントライトにする(座標、ライトの有効距離、減衰パラメータ0、減衰パラメータ1、減衰パラメータ2)
void StandardLight::changeLightTypePoint(const Vector3& position, float range, float atten0, float atten1, float atten2){
	ChangeLightTypePoint(VGet(position.x, position.y, position.z), range, atten0, atten1, atten2);
}

//標準ライトのタイプをスポットライトにする(座標、方向、コーンの外角度、コーンの内角度、ライトの有効距離、減衰パラメータ0、減衰パラメータ1、減衰パラメータ2)
void StandardLight::changeLightTypeSpot(const Vector3& position, const Vector3& direction, float cone_outangle, float cone_inangle, float range, float atten0, float atten1, float atten2) {
	ChangeLightTypeSpot(VGet(position.x, position.y, position.z), VGet(direction.x, direction.y, direction.z), cone_outangle, cone_inangle, range, atten0, atten1, atten2);
}

//標準ライトの有効、無効をセットする
void StandardLight::setLightEnable(bool value) {
	SetLightEnable(value);
}

//標準ライトのディフーズカラーを設定する
void StandardLight::setLightDiffuseColor(Color& color) {
	SetLightDifColor(GetColorF(color.r, color.g, color.b, color.a));
}

//標準ライトのスペキュラカラーを設定する
void StandardLight::setLghtSpecurColor(Color& color) {
	SetLightSpcColor(GetColorF(color.r, color.g, color.b, color.a));
}

//標準ライトのアンビエントカラーを設定する
void StandardLight::setLightAmbientColor(Color& color) {
	SetLightAmbColor(GetColorF(color.r, color.g, color.b, color.a));
}

//標準ライトの方向を設定する
void StandardLight::setLightDirection(Vector3& direction) {
	SetLightDirection(VGet(direction.x, direction.y, direction.z));
}

//標準ライトの位置を設定する
void StandardLight::setLightPosition(Vector3& position) {
	SetLightPosition(VGet(position.x, position.y, position.z));
}

//標準ライトの有効距離と距離減衰パラメータを設定する
void StandardLight::setLightRangeAtten(float range, float atten0, float atten1, float atten2) {
	SetLightRangeAtten(range, atten0, atten1, atten2);
}

//標準ライトの照射角度パラメータを設定する
void StandardLight::setLightAngle(float outangle, float inangle) {
	SetLightAngle(outangle, inangle);
}

//標準ライトのタイプを取得する
int StandardLight::getLightType() {
	return GetLightType();
}

//標準ライトの有効、無効を取得する
bool StandardLight::getLightEnable() {
	return GetLightEnable();
}

//標準ライトのディフーズカラーを取得する
Color StandardLight::getLightDiffuseColor() {
	return Color(GetLightDifColor().r, GetLightDifColor().g, GetLightDifColor().b, GetLightDifColor().a);
}

//標準ライトのスペキュラカラーを取得する
Color StandardLight::getLighSpecurColor() {
	return Color(GetLightSpcColor().r, GetLightSpcColor().g, GetLightSpcColor().b, GetLightSpcColor().a);
}

//標準ライトのアンビエントカラーを取得する
Color StandardLight::getLightAmbientColor() {
	return Color(GetLightAmbColor().r, GetLightAmbColor().g, GetLightAmbColor().b, GetLightAmbColor().a);
}

//標準ライトの方向を取得する
Vector3 StandardLight::getLightDirection() {
	return Vector3(GetLightDirection().x, GetLightDirection().y, GetLightDirection().z);
}

//標準ライトの位置を取得する
Vector3 StandardLight::getLightPosition() {
	return Vector3(GetLightPosition().x, GetLightPosition().y, GetLightPosition().z);
}
