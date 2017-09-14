#pragma once

#include "Body.h"

// »èÈµBody
class DummyBody : public Body{
public:
	// RXgN^
	DummyBody() {}
	// BodyÌ½sÚ®
	virtual IBodyPtr translate(const Vector3& position) const override { return std::make_shared<DummyBody>(); }
	// BodyÌÏ·
	virtual IBodyPtr transform(const Matrix& matrix) const override { return std::make_shared<DummyBody>(); }
	// ÕË»è
	virtual bool isCollide(const IBody& other, HitInfo& hitinfo) const override { return false; }
	// ÕË»è()
	virtual bool intersects(const BoundingSphere& other, HitInfo& hitinfo) const override { return false; }
	// ÕË»è(JvZ)
	virtual bool intersects(const BoundingCapsule& other, HitInfo& hitinfo) const override { return false; }
	// ÕË»è(üª)
	virtual bool intersects(const BoundingSegment& other, HitInfo& hitinfo) const override { return false; }
	// ÕË»è(AABB)
	virtual bool intersects(const BoundingBox& other, HitInfo& hitinfo) const override { return false; }
	// ÕË»è(OBB)
	virtual bool intersects(const OrientedBoundingBox& other, HitInfo& hitinfo) const override { return false; }
	// ÕË»è(C)
	virtual bool intersects(const Ray& other, HitInfo& hitinfo) const override { return false; }
	// ÕË»è(f)
	virtual bool intersects(const CollisionModel& other, HitInfo& hitinfo) const override { return false; }
	// }``æ
	virtual void draw() const override{}
	virtual void draw(const Vector3& position) const override{}
};
