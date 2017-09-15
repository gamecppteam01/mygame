#pragma once

#include "Base/Body.h"

// ����
class BoundingSegment : public Body {
public:
	//�����̔�����쐬
	BoundingSegment(const Vector3& pos, const Matrix& mat, const float& len);
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

	// Body�̕��s�ړ�
	virtual IBodyPtr translate(const Vector3& pos) const override;
	// Body�̕ϊ�
	virtual IBodyPtr transform(const Matrix& mat) const override;

	// Body�̕��s�ړ�
	BoundingSegment translate_e(const Vector3& pos) const;
	// Body�̕ϊ�
	BoundingSegment transform_e(const Matrix& mat) const;

	// �n�_����I�_�ւ̕�����Ԃ�
	Vector3 Direction()const;

	// �}�`�`��
	virtual void draw() const override;
	virtual void draw(const Vector3& position) const override;
};
