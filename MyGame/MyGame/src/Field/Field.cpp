#include "Field.h"

#include "../Define.h"

#include<DxLib.h>
#include"../Math/Vector3.h"

// �R���X�g���N�^
Field::Field(int field,int skybox) :
	mField(field), mSkyBox(skybox),mesh_(mField) {
	//���f�����ݒ肳��Ă��Ȃ�������Ԃ�
	if (mField < 0||mSkyBox<0)return;

	// �t�B�[���h�̍��W�w��
	MV1SetPosition(mField, Vector3::Vector3ToVECTOR(FIELD_POS * FIELD_SCALE));
	// �t�B�[���h�̊g�嗦�w��
	MV1SetScale(mField, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE));

	// �X�J�C�{�b�N�X�̍��W�w��
	MV1SetPosition(mSkyBox, Vector3::Vector3ToVECTOR(Vector3(FIELD_SIZE, 0, FIELD_SIZE) * FIELD_SCALE * 0.5f));
	// �X�J�C�{�b�N�X�̊g�嗦�w��
	MV1SetScale(mSkyBox, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE * 15));
}

// �X�V
void Field::update(float deltaTime) {
	if (mField < 0 || mSkyBox<0)return;
}

// �`��
void Field::draw() const {
	if (mField < 0 || mSkyBox<0)return;

	// �X�J�C�{�b�N�X�̕`��
	MV1DrawModel(mSkyBox);
	// �t�B�[���h�̕`��
	MV1DrawModel(mField);
}

// �t�B�[���h�̃n���h���擾
int Field::modelHandle(){
	return mField;
}

CollisionMesh& Field::getMesh()
{
	return mesh_;
}
