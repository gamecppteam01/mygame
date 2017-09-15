#pragma once

#include "Base/Body.h"

class BoundingSphere : public Body {
public:
	//���̔�����쐬
	BoundingSphere(const Vector3& pos, const float& rad);
public:
	// �Փ˔���
	virtual bool isCollide(const IBody& other, HitInfo& hitinfo) const override;
	// �Փ˔���(��)
	virtual bool intersects(const BoundingSphere& other, HitInfo& hitinfo) const override;
	// �Փ˔���(�J�v�Z��)
	virtual bool intersects(const BoundingCapsule& other, HitInfo& hitinfo) const override;
	// �Փ˔���(����)
	virtual bool intersects(const BoundingSegment& other, HitInfo& hitinfo) const override;
	// �Փ˔���(AABB)
	virtual bool intersects(const BoundingBox& other, HitInfo& hitinfo) const override;
	// �Փ˔���(OBB)
	virtual bool intersects(const OrientedBoundingBox& other, HitInfo& hitinfo) const override;
	// �Փ˔���(���C)
	virtual bool intersects(const Ray& other, HitInfo& hitinfo) const override;
	// �Փ˔���(���f��)
	virtual bool intersects(const CollisionModel& other, HitInfo& hitinfo) const override;
	// ��ܔ���(�_)
	virtual bool contains(const Vector3& point) const override;
	// ��ܔ���(��)
	virtual bool contains(const BoundingSphere& sphere) const override;

	// Body�̕��s�ړ�
	virtual IBodyPtr translate(const Vector3& pos) const override;
	// Body�̕ϊ�
	virtual IBodyPtr transform(const Matrix& mat) const override;

	// Body�̕��s�ړ�
	BoundingSphere translate_e(const Vector3& pos) const;
	// Body�̕ϊ�
	BoundingSphere transform_e(const Matrix& mat) const;

	// �}�`�`��
	virtual void draw() const override;
	virtual void draw(const Vector3& position) const override;
};
