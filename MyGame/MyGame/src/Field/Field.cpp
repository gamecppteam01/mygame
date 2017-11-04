#include "Field.h"

#include "../Define.h"

#include<DxLib.h>
#include"../Math/Vector3.h"

// コンストラクタ
Field::Field(int field,int skybox) :
	mField(field), mSkyBox(skybox),mesh_(mField) {
	//モデルが設定されていなかったら返す
	if (mField < 0||mSkyBox<0)return;

	// フィールドの座標指定
	MV1SetPosition(mField, Vector3::Vector3ToVECTOR(FIELD_POS * FIELD_SCALE));
	// フィールドの拡大率指定
	MV1SetScale(mField, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE));

	// スカイボックスの座標指定
	//MV1SetPosition(mSkyBox, Vector3::Vector3ToVECTOR(Vector3(FIELD_SIZE, 0, FIELD_SIZE) * FIELD_SCALE * 0.5f));
	MV1SetPosition(mSkyBox, Vector3::Vector3ToVECTOR(Vector3::Zero));
	// スカイボックスの拡大率指定
	//MV1SetScale(mSkyBox, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE * 15));
	MV1SetScale(mSkyBox, Vector3::Vector3ToVECTOR(Vector3::One*5.0f));
}

// 更新
void Field::update(float deltaTime) {
	if (mField < 0 || mSkyBox<0)return;
}

// 描画
void Field::draw() const {
	if (mField < 0 || mSkyBox<0)return;

	// スカイボックスの描画
	MV1DrawModel(mSkyBox);
	// フィールドの描画
	MV1DrawModel(mField);
}

// フィールドのハンドル取得
int Field::modelHandle(){
	return mField;
}

CollisionMesh& Field::getMesh()
{
	return mesh_;
}

bool Field::isInField(const Vector3 & position)
{
	return std::abs(position.x) < getXWidth() && std::abs(position.z) < getZWidth();
}

Vector3 Field::CorrectPosition(const Vector3 & position)
{
	Vector3 result=position;
	if (position.x > getXWidth())result.x = getXWidth();
	if (position.x < -getXWidth())result.x = -getXWidth();
	if (position.z > getZWidth())result.z = getZWidth();
	if (position.z < -getZWidth())result.z = -getZWidth();

	return result;
}

float Field::getXWidth() const
{
	return 120.0f;
}

float Field::getZWidth() const
{
	return 120.0f;
}
