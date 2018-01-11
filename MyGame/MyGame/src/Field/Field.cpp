#include "Field.h"

#include "../Define.h"

#include<DxLib.h>
#include"../Math/Vector3.h"
#include"../Graphic/Model.h"
#include"../Graphic/Sprite.h"

float to_radian(float degree) {
	return degree / 180.0f*DX_PI_F;
}
// �R���X�g���N�^
Field::Field(int field,int skybox) :
	mField(field), mSkyBox(skybox),mesh_(mField),audience() {
	//���f�����ݒ肳��Ă��Ȃ�������Ԃ�
	if (mField < 0||mSkyBox<0)return;

	fieldSide_= Model::GetInstance().GetHandle(MODEL_ID::STAGE_RIGHTLEFT_MODEL);
	fieldUp_= Model::GetInstance().GetHandle(MODEL_ID::STAGE_UPDOWN_MODEL);
	wallCorner_ = Model::GetInstance().GetHandle(MODEL_ID::STAGE_WALL_CORNER_MODEL);
	wallSide_ = Model::GetInstance().GetHandle(MODEL_ID::STAGE_WALL_SIDE_MODEL);
	wallUp_ = Model::GetInstance().GetHandle(MODEL_ID::STAGE_WALL_UP_MODEL);


	Vector3 wallUp{ 0.0f,0.0f,420.0f };
	// �t�B�[���h�̍��W�w��
	MV1SetPosition(mField, Vector3::Vector3ToVECTOR(FIELD_POS * FIELD_SCALE));
	MV1SetPosition(wallUp_, Vector3::Vector3ToVECTOR(wallUp *FIELD_SCALE));

	// �t�B�[���h�̊g�嗦�w��
	MV1SetScale(mField, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE));
	MV1SetScale(fieldSide_, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE));
	MV1SetScale(fieldUp_, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE));
	MV1SetScale(wallCorner_, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE));
	MV1SetScale(wallSide_, Vector3::Vector3ToVECTOR(Vector3{1.0f,1.0f,1.5f} *FIELD_SCALE));
	MV1SetScale(wallUp_, Vector3::Vector3ToVECTOR(Vector3{ 1.5f,1.0f,1.0f } * FIELD_SCALE));

	// �X�J�C�{�b�N�X�̍��W�w��
	//MV1SetPosition(mSkyBox, Vector3::Vector3ToVECTOR(Vector3(FIELD_SIZE, 0, FIELD_SIZE) * FIELD_SCALE * 0.5f));
	MV1SetPosition(mSkyBox, Vector3::Vector3ToVECTOR(Vector3::Zero));
	// �X�J�C�{�b�N�X�̊g�嗦�w��
	//MV1SetScale(mSkyBox, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE * 15));
	MV1SetScale(mSkyBox, Vector3::Vector3ToVECTOR(Vector3::One*5.0f));
	audience.initialize();
}

// �X�V
void Field::update(float deltaTime) {
	if (mField < 0 || mSkyBox<0)return;
	audience.update(deltaTime);
}

// �`��
void Field::draw() const {
	if (mField < 0 || mSkyBox<0)return;

	Vector3 right{ 375.0f,0.0f,0.0f };
	Vector3 up{ 0.0f,0.0f,225.0f };

	Vector3 wallUp{ 0.0f,0.0f,420.0f };
	Vector3 wallRight{ 450.0f,0.0f,0.0f };

	// �X�J�C�{�b�N�X�̕`��
	MV1DrawModel(mSkyBox);
	// �t�B�[���h�̕`��
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

	audience.draw(up, Vector3{ -90.0f,0.0f,0.0f });
	audience.draw(right, Vector3{ -90.0f,0.0f,0.0f });
	audience.draw(-right, Vector3{ -90.0f,0.0f,0.0f });
}

// �t�B�[���h�̃n���h���擾
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
