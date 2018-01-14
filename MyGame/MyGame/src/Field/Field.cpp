#include "Field.h"

#include "../Define.h"

#include<DxLib.h>
#include"../Math/Vector3.h"
#include"../Graphic/Model.h"
#include"../Graphic/Sprite.h"

float to_radian(float degree) {
	return degree / 180.0f*DX_PI_F;
}
// コンストラクタ
Field::Field(int field,int skybox) :
	mField(field), mSkyBox(skybox),mesh_(mField),audience() {
	//モデルが設定されていなかったら返す
	if (mField < 0||mSkyBox<0)return;

	fieldSide_= Model::GetInstance().GetHandle(MODEL_ID::STAGE_RIGHTLEFT_MODEL);
	fieldUp_= Model::GetInstance().GetHandle(MODEL_ID::STAGE_UPDOWN_MODEL);
	wallCorner_ = Model::GetInstance().GetHandle(MODEL_ID::STAGE_WALL_CORNER_MODEL);
	wallSide_ = Model::GetInstance().GetHandle(MODEL_ID::STAGE_WALL_SIDE_MODEL);
	wallUp_ = Model::GetInstance().GetHandle(MODEL_ID::STAGE_WALL_UP_MODEL);
	audience_ = Model::GetInstance().GetHandle(MODEL_ID::STAGE_SEAT);

	Vector3 wallUp{ 0.0f,0.0f,420.0f };
	// フィールドの座標指定
	MV1SetPosition(mField, Vector3::Vector3ToVECTOR(FIELD_POS * FIELD_SCALE));
	MV1SetPosition(wallUp_, Vector3::Vector3ToVECTOR(wallUp *FIELD_SCALE));

	// フィールドの拡大率指定
	MV1SetScale(mField, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE));
	MV1SetScale(fieldSide_, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE));
	MV1SetScale(fieldUp_, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE));
	MV1SetScale(wallCorner_, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE));
	MV1SetScale(wallSide_, Vector3::Vector3ToVECTOR(Vector3{1.0f,1.0f,1.5f} *FIELD_SCALE));
	MV1SetScale(wallUp_, Vector3::Vector3ToVECTOR(Vector3{ 1.5f,1.0f,1.0f } * FIELD_SCALE));

	// スカイボックスの座標指定
	//MV1SetPosition(mSkyBox, Vector3::Vector3ToVECTOR(Vector3(FIELD_SIZE, 0, FIELD_SIZE) * FIELD_SCALE * 0.5f));
	MV1SetPosition(mSkyBox, Vector3::Vector3ToVECTOR(Vector3::Zero));
	// スカイボックスの拡大率指定
	//MV1SetScale(mSkyBox, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE * 15));
	MV1SetScale(mSkyBox, Vector3::Vector3ToVECTOR(Vector3::One*5.0f));

	audience.initialize();
}

// 更新
void Field::update(float deltaTime) {
	if (mField < 0 || mSkyBox<0)return;
	audience.update(deltaTime);
}

// 描画
void Field::draw() const {
	if (mField < 0 || mSkyBox<0)return;

	Vector3 right{ 375.0f,0.0f,0.0f };
	Vector3 up{ 0.0f,0.0f,225.0f };

	Vector3 wallUp{ 0.0f,0.0f,420.0f };
	Vector3 wallRight{ 450.0f,0.0f,0.0f };

	// スカイボックスの描画
	MV1DrawModel(mSkyBox);
	// フィールドの描画
	MV1DrawModel(mField);
	MV1SetPosition(fieldSide_, Vector3::Vector3ToVECTOR(right * FIELD_SCALE));
	MV1DrawModel(fieldSide_);
	MV1SetPosition(fieldSide_, Vector3::Vector3ToVECTOR(-right * FIELD_SCALE));
	MV1DrawModel(fieldSide_);

	MV1SetPosition(fieldUp_, Vector3::Vector3ToVECTOR(up *FIELD_SCALE));
	MV1DrawModel(fieldUp_);
	MV1SetPosition(fieldUp_, Vector3::Vector3ToVECTOR(-up *FIELD_SCALE));
	MV1DrawModel(fieldUp_);
	float x = 420.0f; float y = 300.0f;

	//MV1SetPosition(wallCorner_, Vector3::Vector3ToVECTOR(Vector3{x,0.0f,y} *FIELD_SCALE));
	//MV1SetRotationXYZ(wallCorner_, Vector3{ 0.0f,0.0f,0.0f, });
	////MV1DrawModel(wallCorner_);
	//MV1SetRotationXYZ(wallCorner_, Vector3{ 0.0f,to_radian(-90.0f),0.0f, });
	//MV1SetPosition(wallCorner_, Vector3::Vector3ToVECTOR(Vector3{ -x,0.0f,y } *FIELD_SCALE));
	////MV1DrawModel(wallCorner_);
	//MV1SetPosition(wallCorner_, Vector3::Vector3ToVECTOR(Vector3{ x,0.0f,-y } *FIELD_SCALE));
	//MV1SetRotationXYZ(wallCorner_, Vector3{ 0.0f,to_radian(90.0f),0.0f, });
	////MV1DrawModel(wallCorner_);
	//MV1SetPosition(wallCorner_, Vector3::Vector3ToVECTOR(Vector3{ -x,0.0f,-y } *FIELD_SCALE));
	//MV1SetRotationXYZ(wallCorner_, Vector3{ 0.0f,to_radian(180.0f),0.0f, });
	////MV1DrawModel(wallCorner_);
	//MV1SetPosition(wallSide_, Vector3::Vector3ToVECTOR(wallRight *FIELD_SCALE));
	//MV1DrawModel(wallSide_);
	//MV1SetPosition(wallSide_, Vector3::Vector3ToVECTOR(-wallRight *FIELD_SCALE));
	//MV1DrawModel(wallSide_);
	//MV1DrawModel(wallUp_);
	
	//for (int i = 0; i < 9; i++) {
		MV1SetRotationXYZ(audience_, Vector3{ to_radian(0.0f),to_radian(180.0f),to_radian(0.0f) });
		MV1SetScale(audience_, Vector3::Vector3ToVECTOR(Vector3{ 1.05f,1.0f,1.0f } *13.5f));
		MV1SetPosition(audience_, Vector3::Vector3ToVECTOR(Vector3{ 3.0f,0.0f,135.0f }));
		MV1DrawModel(audience_);
	//}
	//for (int i = 0; i < 6; i++) {
		MV1SetRotationXYZ(audience_, Vector3{ to_radian(0.0f),to_radian(90.0f),to_radian(0.0f) });
		MV1SetScale(audience_, Vector3::Vector3ToVECTOR(Vector3{ 1.0f,1.0f,1.0f } *13.5f));
		MV1SetPosition(audience_, Vector3::Vector3ToVECTOR(Vector3{-225.0f,0.0f, 0.0f }));
		MV1DrawModel(audience_);
	//}
	//for (int i = 0; i < 6; i++) {
		MV1SetRotationXYZ(audience_, Vector3{ to_radian(0.0f),to_radian(270.0f),to_radian(0.0f) });
		MV1SetScale(audience_, Vector3::Vector3ToVECTOR(Vector3{ 1.0f,1.0f,1.0f } * 13.5f));
		MV1SetPosition(audience_, Vector3::Vector3ToVECTOR(Vector3{225.0f,0.0f, 0.0f }));
		MV1DrawModel(audience_);
	//}

	//audience.draw(Vector3{0.0f,51.0f,190.0f},   Vector3{ -40.0f,0.0f,0.0f },1);
	//audience.draw(Vector3{275.0f,50.0f,0.0f},   Vector3{ 0.0f,90.0f,40.0f },2);
	//audience.draw(Vector3{-275.0f,50.0f,0.0f}, Vector3{ 0.0f,-90.0f,-40.0f },2);
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
	return 280.0f*FIELD_SCALE;
}

float Field::getZWidth() const
{
	return 130.0f*FIELD_SCALE;
}
