#pragma once

#include "IBody.h"
#include "../../../Math/Math.h"

class Body : public IBody {
public:
	// �R���X�g���N�^
	Body() : mType(ShapeType::None), mPosition(Vector3::Zero), mMatrix(Matrix::Identity), mRadius(0.0f), mLength(0.0f), mDirection(Vector3::Zero), mHeight(0.0f), mWidth(0.0f), mDepth(0.0f), mMin(Vector3::Zero), mMax(Vector3::Zero), mExtents(Vector3::Zero), mEnabled(false){}
	// �R���X�g���N�^(��)
	Body(const ShapeType& type, const Vector3& position, const float& radius) :
		mType(type), mPosition(position), mMatrix(Matrix::Identity), mRadius(radius), mLength(0.0f), mDirection(Vector3::Zero), mHeight(0.0f), mWidth(0.0f), mDepth(0.0f), mMin(Vector3::Zero), mMax(Vector3::Zero), mExtents(Vector3::Zero), mEnabled(true) {}
	// �R���X�g���N�^(����)
	Body(const ShapeType& type, const Vector3& position, const Matrix& mat, const float& length) :
		mType(type), mPosition(position), mMatrix(mat), mRadius(0.0f), mLength(length), mDirection(Vector3::Zero), mHeight(0.0f), mWidth(0.0f), mDepth(0.0f), mMin(Vector3::Zero), mMax(Vector3::Zero), mExtents(Vector3::Zero), mEnabled(true) {}
	// �R���X�g���N�^(���C)
	Body(const ShapeType& type, const Vector3& position, const Matrix& mat, const Vector3& direction) :
		mType(type), mPosition(position), mMatrix(Matrix::Identity), mRadius(0.0f), mLength(0.0f), mDirection(direction), mHeight(0.0f), mWidth(0.0f), mDepth(0.0f), mMin(Vector3::Zero), mMax(Vector3::Zero), mExtents(Vector3::Zero), mEnabled(true) {}
	// �R���X�g���N�^(�J�v�Z��)
	Body(const ShapeType& type, const Vector3& position, const Matrix& mat, const float& radius, const float& length) :
		mType(type), mPosition(position), mMatrix(mat), mRadius(radius), mLength(length), mDirection(Vector3::Zero), mHeight(0.0f), mWidth(0.0f), mDepth(0.0f), mMin(Vector3::Zero), mMax(Vector3::Zero), mExtents(Vector3::Zero), mEnabled(true) {}
	// �R���X�g���N�^(AABB)
	Body(const ShapeType& type, const Vector3& position, const Vector3 & min, const Vector3 & max) :
		mType(type), mPosition(Vector3::Zero), mMatrix(Matrix::Identity), mRadius(0.0f), mLength(0.0f), mDirection(Vector3::Zero), mHeight(0.0f), mWidth(0.0f), mDepth(0.0f), mMin(min), mMax(max), mExtents(Vector3::Zero), mEnabled(true) {}
	// �R���X�g���N�^(OBB)
	Body(const ShapeType& type, const Vector3& position, const Vector3& extents) :
		mType(type), mPosition(position), mMatrix(Matrix::Identity), mRadius(0.0f), mLength(0.0f), mDirection(Vector3::Zero), mHeight(0.0f), mWidth(0.0f), mDepth(0.0f), mMin(Vector3::Zero), mMax(Vector3::Zero), mExtents(extents), mEnabled(true) {}
	// �f�X�g���N�^
	virtual ~Body(){}

	// �����ON�AOFF
	virtual void active(bool active) override { mEnabled = active; }
	// ���肪���邩�ǂ���
	virtual bool enabled() const override { return mEnabled; }

	// �`��̎擾
	virtual ShapeType type() const override { return mType; }
	// ���S���W�̎擾
	virtual Vector3 position() const override { return mPosition; }
	// �ϊ��s��̎擾
	virtual Matrix matrix() const override { return mMatrix; }
	// ���a�̎擾
	virtual float radius() const override { return mRadius; }
	// �����̎擾
	virtual float length() const override { return mLength; }
	// �����̎擾
	virtual Vector3 direction() const override { return mDirection; }

	// �c���̎擾
	virtual float height() const override { return mHeight; }
	// �����̎擾
	virtual float width() const override { return mWidth; }
	// ���s�̎擾
	virtual float depth() const override { return mDepth; }
	// ��`�̍ŏ��_�̎擾
	virtual Vector3 box_min() const override { return mMin; }
	// ��`�̍ő�_�̎擾
	virtual Vector3 box_max() const override { return mMax; }
	// ��`�̑傫���̎擾
	virtual Vector3 extents() const override { return mExtents; }
	// ��`�̎��̎擾
	virtual Vector3 axis(const int index) const override { return mAxis[index]; }
	// �_�̎擾
	virtual Vector3 points(const int index) const override { return mPoints[index]; }
	
protected:
	// �`��
	ShapeType mType;
	// ���S���W
	Vector3 mPosition;
	// �ϊ��s��
	Matrix mMatrix;
	// ���a
	float mRadius;
	// ����
	float mLength;

	// ���C�p
	// ����
	Vector3 mDirection;
	
	// �{�b�N�X�p
	// �c��
	float mHeight;
	// ����
	float mWidth;
	// ���s
	float mDepth;

	// ��`�̍ŏ��_
	Vector3 mMin;
	// ��`�̍ő�_
	Vector3 mMax;

	// ��`�̑傫��
	Vector3 mExtents;
	// ��`�̎�
	Vector3 mAxis[3];

	// �_
	Vector3 mPoints[4];

	// ���肪���邩�ǂ���
	bool mEnabled;
};

