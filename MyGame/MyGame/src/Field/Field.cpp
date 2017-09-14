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
	MV1SetPosition(mSkyBox, Vector3::Vector3ToVECTOR(Vector3(FIELD_SIZE, 0, FIELD_SIZE) * FIELD_SCALE * 0.5f));
	// スカイボックスの拡大率指定
	MV1SetScale(mSkyBox, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE * 15));
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
