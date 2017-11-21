#include "LightHandle.h"
#include<DxLib.h>

//ライトタイプ
const int LightHandle::DirType = DX_LIGHTTYPE_DIRECTIONAL;
const int LightHandle::PointType = DX_LIGHTTYPE_POINT;
const int LightHandle::SpotType = DX_LIGHTTYPE_SPOT;

//コンストラクタ
LightHandle::LightHandle(){
	initialize();
}

//初期化
void LightHandle::initialize(){
	setUseLighting(true);
	lightHandles_.clear();
}

//ライティング計算処理を使用するかどうかを設定する
void LightHandle::setUseLighting(bool value) {
	SetUseLighting(value);
}

//グローバルアンビエントカラーを設定する
void LightHandle::setGlobalAmbientLight(Color& color) {
	SetGlobalAmbientLight(GetColorF(color.r, color.g, color.b, color.a));
}

//デレクショナルタイプのライトハンドルの作成
void LightHandle::createDirLightHandle(const std::string& handle, const Vector3& direction) {
	lightHandles_[handle] = CreateDirLightHandle(VGet(direction.x, direction.y, direction.z));
}

//ポイントタイプのライトハンドルの作成
void LightHandle::createPointLightHandle(const std::string& handle, const Vector3& position, float range, float atten0, float atten1, float atten2) {
	lightHandles_[handle] = CreatePointLightHandle(VGet(position.x, position.y, position.z), range, atten0, atten1, atten2);
}

//スポットタイプのライトハンドルの作成
void LightHandle::createSpotLightHandle(const std::string& handle, const Vector3& position, const Vector3& direction, float cone_outangle, float cone_inangle, float range, float atten0, float atten1, float atten2) {
	lightHandles_[handle] = CreateSpotLightHandle(VGet(position.x, position.y, position.z), VGet(direction.x, direction.y, direction.z), cone_outangle, cone_inangle, range, atten0, atten1, atten2);
}

//ライトハンドルを削除する
void LightHandle::deleteLightHandle(const std::string& handle) {
	DeleteLightHandle(lightHandles_[handle]);
	lightHandles_.erase(handle);
}

//ライトハンドルを全て削除する
void LightHandle::deleteLightHandleAll() {
	DeleteLightHandleAll();
	lightHandles_.clear();
}

//ライトハンドルのタイプを変更する
void LightHandle::changeLightTypeHandle(const std::string& handle, int lightType) {
	SetLightTypeHandle(lightHandles_[handle], lightType);
}

//ライトハンドルの有効、無効を設定する
void LightHandle::setLightEnableHandle(const std::string& handle, bool value) {
	SetLightEnableHandle(lightHandles_[handle], value);
}

//ライトハンドルのディフューズカラーを設定する
void LightHandle::setLightDiffuseColorHandle(const std::string& handle, Color& color) {
	SetLightDifColorHandle(lightHandles_[handle], GetColorF(color.r, color.g, color.b, color.a));
}

//ライトハンドルのスペキュラーカラーを設定する
void LightHandle::setLightSpecuarColorHandle(const std::string& handle, Color& color) {
	SetLightSpcColorHandle(lightHandles_[handle], GetColorF(color.r, color.g, color.b, color.a));
}

//ライトハンドルのアンビエントカラーを設定する
void LightHandle::setLightAmbientColorHandle(const std::string& handle, Color& color) {
	SetLightAmbColorHandle(lightHandles_[handle], GetColorF(color.r, color.g, color.b, color.a));
}

//ライトハンドルの方向を指定する
void LightHandle::setLightDirectionHandle(const std::string& handle, const Vector3& direction) {
	SetLightPositionHandle(lightHandles_[handle], VGet(direction.x, direction.y, direction.z));
}

//ライトハンドルの位置を設定する
void LightHandle::setLightPositionHandle(const std::string& handle, const Vector3& position) {
	SetLightPositionHandle(lightHandles_[handle], VGet(position.x, position.y, position.z));
}

//ライトハンドルの有効距離と距離減衰パラメータを設定する
void LightHandle::setLightRangeAttenHandle(const std::string& handle, float range, float atten0, float atten1, float atten2) {
	SetLightRangeAttenHandle(lightHandles_[handle], range, atten0, atten1, atten2);
}

//ライトハンドルの照射角度パラメータを設定する
void LightHandle::setLightAngleHandle(const std::string& handle, float cone_outangle, float cone_inangle) {
	SetLightAngleHandle(lightHandles_[handle], cone_outangle, cone_inangle);
}

//ライトハンドルのタイプを取得する
int LightHandle::getLightTypeHandle(const std::string& handle) {
	return GetLightTypeHandle(lightHandles_[handle]);
}

//ライトハンドルの有効、無効を取得する
bool LightHandle::getLightEnableHandle(const std::string& handle) {
	return GetLightEnableHandle(lightHandles_[handle]);
}

//ライトハンドルのディフューズカラーを取得する
Color LightHandle::getLightDiffuseColorHandle(const std::string& handle) {
	return Color(
		GetLightDifColorHandle(lightHandles_[handle]).r,
		GetLightDifColorHandle(lightHandles_[handle]).g,
		GetLightDifColorHandle(lightHandles_[handle]).b, 
		GetLightDifColorHandle(lightHandles_[handle]).a);
}

//ライトハンドルのスペキュラーカラーを取得する
Color LightHandle::getLightSpecuarColorHandle(const std::string& handle) {
	return Color(
		GetLightSpcColorHandle(lightHandles_[handle]).r,
		GetLightSpcColorHandle(lightHandles_[handle]).g,
		GetLightSpcColorHandle(lightHandles_[handle]).b,
		GetLightSpcColorHandle(lightHandles_[handle]).a);
}

//ライトハンドルのアンビエントカラーを取得する
Color LightHandle::getLightAmbientColorHandle(const std::string& handle) {
	return Color(
		GetLightAmbColorHandle(lightHandles_[handle]).r,
		GetLightAmbColorHandle(lightHandles_[handle]).g,
		GetLightAmbColorHandle(lightHandles_[handle]).b,
		GetLightAmbColorHandle(lightHandles_[handle]).a);
}

//ライトハンドルの方向を取得する
Vector3 LightHandle::getLightDirectionHandle(const std::string& handle) {
	return Vector3(
		GetLightDirectionHandle(lightHandles_[handle]).x,
		GetLightDirectionHandle(lightHandles_[handle]).y,
		GetLightDirectionHandle(lightHandles_[handle]).z);
}

//ライトハンドルの位置を取得する
Vector3 LightHandle::getLightPositionHandle(const std::string& handle) {
	return Vector3(
		GetLightPositionHandle(lightHandles_[handle]).x,
		GetLightPositionHandle(lightHandles_[handle]).y,
		GetLightPositionHandle(lightHandles_[handle]).z);
}

//有効になっているライトハンドルの数を取得する
int LightHandle::getEnableLightHandleNum() {
	return GetEnableLightHandleNum();
}

//有効になっているライトハンドルを取得する
int LightHandle::getEnableLightHandle(int index) {
	return GetEnableLightHandle(index);
}