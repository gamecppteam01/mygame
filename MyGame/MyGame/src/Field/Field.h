#pragma once
#include"../Math/Collision/CollisionMesh.h"
#include"Audience.h"
// �t�B�[���h�N���X
class Field {
public:
	// �R���X�g���N�^
	Field(int field=-1, int skybox=-1);
	// �X�V
	void update(float deltaTime);
	// �`��
	void draw() const;
	// �t�B�[���h�̃n���h���擾
	int modelHandle();
	CollisionMesh& getMesh();
	bool isInField(const Vector3& position);
	Vector3 CorrectPosition(const Vector3& position);
	float getXWidth()const;
	float getZWidth()const;
	// �R�s�[�֎~
	Field(const Field& other) = delete;
	Field& operator = (const Field& other) = delete;
private:
	int mField;
	int fieldUp_;
	int fieldSide_;
	int wallUp_;
	int wallSide_;
	int wallCorner_;
	int mSkyBox;
	int audience_;
	CollisionMesh mesh_;
	Audience audience;
};
