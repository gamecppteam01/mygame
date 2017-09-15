#pragma once

#include "Base/Body.h"

// AABB
class BoundingBox : public Body {
public:
	//AABB�̔�����쐬
	BoundingBox(const Vector3& min, const Vector3& max);
public:
	// �Փ˔���
	virtual bool isCollide(const IBody& other, HitInfo& hitinfo) const override;
	// �Փ˔���(��)
	virtual bool intersects(const BoundingSphere& sphere, HitInfo& hitinfo) const override;
	// �Փ˔���(�J�v�Z��)
	virtual bool intersects(const BoundingCapsule& capsule, HitInfo& hitinfo) const override;
	// �Փ˔���(����)
	virtual bool intersects(const BoundingSegment& segment, HitInfo& hitinfo) const override;
	// �Փ˔���(AABB)
	virtual bool intersects(const BoundingBox& aabb, HitInfo& hitinfo) const override;
	// �Փ˔���(OBB)
	virtual bool intersects(const OrientedBoundingBox& obb, HitInfo& hitinfo) const override;
	// �Փ˔���(���C)
	virtual bool intersects(const Ray& ray, HitInfo& hitinfo) const override;
	// �Փ˔���(���f��)
	virtual bool intersects(const CollisionModel& model, HitInfo& hitinfo) const override;
	
	// ��ܔ���(�_)
	virtual bool contains(const Vector3& point) const override;
	// ��ܔ���(��)
	virtual bool contains(const BoundingSphere& sphere) const override;
	// ��ܔ���(����)
	virtual bool contains(const BoundingSegment& segment) const override;
	// ��ܔ���(AABB)
	virtual bool contains(const BoundingBox& aabb) const override;
	// ��ܔ���(OBB)
	virtual bool contains(const OrientedBoundingBox& obb) const override;

	// Body�̕��s�ړ�
	virtual IBodyPtr translate(const Vector3& pos) const override;
	// Body�̕ϊ�
	virtual IBodyPtr transform(const Matrix& mat) const override;

	// Body�̕��s�ړ�
	BoundingBox translate_e(const Vector3& pos) const;
	// Body�̕ϊ�
	BoundingBox transform_e(const Matrix& mat) const;

	// ���̏Փ˔���
	bool intersects(const Vector3& position, const Vector3& direction, float& start, float& end) const;
	// �ߐړ_
	Vector3 ClosestPoint(const Vector3& target)const;
	// ���_
	Vector3 CornerPoint(int cornerIndex)const;
	// ��`�̃T�C�Y
	Vector3 Size()const;
	// ���S���W
	Vector3 Center()const;

	// �}�`�`��
	virtual void draw() const override;
	virtual void draw(const Vector3& position) const override;
};
