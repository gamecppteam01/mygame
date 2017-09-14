#pragma once

#include "IBodyPtr.h"

#include "ShapeType.h"

struct Vector3;
struct Matrix;
struct HitInfo;

class BoundingSphere;
class BoundingCapsule;
class BoundingSegment;
class BoundingBox;
class OrientedBoundingBox;
class Ray;
class CollisionModel;

// Body�C���^�[�t�F�[�X�N���X
class IBody{
public:
	// �R���X�g���N�^
	IBody() {}
	// �f�X�g���N�^
	virtual ~IBody() = default;
public:
	// Body�̕��s�ړ�
	virtual IBodyPtr translate(const Vector3& position) const = 0;
	// Body�̕ϊ�
	virtual IBodyPtr transform(const Matrix& matrix) const = 0;
	// �Փ˔���
	virtual bool isCollide(const IBody& other, HitInfo& hitinfo) const = 0;
	// �Փ˔���(��)
	virtual bool intersects(const BoundingSphere& other, HitInfo& hitinfo) const = 0;
	// �Փ˔���(�J�v�Z��)
	virtual bool intersects(const BoundingCapsule& other, HitInfo& hitinfo) const = 0;
	// �Փ˔���(����)
	virtual bool intersects(const BoundingSegment& other, HitInfo& hitinfo) const = 0;
	// �Փ˔���(AABB)
	virtual bool intersects(const BoundingBox& other, HitInfo& hitinfo) const = 0;
	// �Փ˔���(OBB)
	virtual bool intersects(const OrientedBoundingBox& other, HitInfo& hitinfo) const = 0;
	// �Փ˔���(���C)
	virtual bool intersects(const Ray& other, HitInfo& hitinfo) const = 0;
	// �Փ˔���(���f��)
	virtual bool intersects(const CollisionModel& other, HitInfo& hitinfo) const = 0;

	virtual bool contains(const Vector3& point) const { return false; }

	virtual bool contains(const BoundingSphere& sphere) const { return false; }

	virtual bool contains(const BoundingSegment& segment) const { return false; }

	virtual bool contains(const BoundingBox& aabb) const { return false; }

	virtual bool contains(const OrientedBoundingBox& obb) const { return false; }
	// �����ON�AOFF
	virtual void active(bool active) = 0;
	// ���肪���邩�ǂ���
	virtual bool enabled() const = 0;
	// �}�`�`��
	virtual void draw() const = 0;
	virtual void draw(const Vector3& position) const = 0;
	// �`��̎擾
	virtual ShapeType type() const = 0;
	// ���S���W�̎擾
	virtual Vector3 position() const = 0;
	// �ϊ��s��̎擾
	virtual Matrix matrix() const = 0;
	// ���a�̎擾
	virtual float radius() const = 0;
	// �����̎擾
	virtual float length() const = 0;
	// �����̎擾
	virtual Vector3 direction() const = 0;
	// �c���̎擾
	virtual float height() const = 0;
	// �����̎擾
	virtual float width() const = 0;
	// ���s�̎擾
	virtual float depth() const = 0;
	// ��`�̍ŏ��_�̎擾
	virtual Vector3 box_min() const = 0;
	// ��`�̍ő�_�̎擾
	virtual Vector3 box_max() const = 0;
	// ��`�̑傫���̎擾
	virtual Vector3 extents() const = 0;
	// ��`�̎��̎擾
	virtual Vector3 axis(const int index) const = 0;
	// �_�̎擾
	virtual Vector3 points(const int index) const = 0;
};

