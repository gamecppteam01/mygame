#include "BoundingSphere.h"
#include "BoundingCapsule.h"
#include "BoundingSegment.h"
#include "BoundingBox.h"
#include "OrientedBoundingBox.h"
#include "Ray.h"
#include "CollisionModel.h"

#include "../../Math/Collision/Collision.h"

//���̔�����쐬����
BoundingSphere::BoundingSphere(const Vector3& pos, const float& rad) :
	Body(ShapeType::Sphere, pos, rad){
}

// �Փ˔���
bool BoundingSphere::isCollide(const IBody & other, HitInfo & hitinfo) const {
	// �ǂ��炩�̔�����s��Ȃ��ꍇfalse
	if (!other.enabled() || !enabled())return false;
	
	return other.intersects(*this, hitinfo);
}

// �Փ˔���(��)
bool BoundingSphere::intersects(const BoundingSphere & other, HitInfo & hitinfo) const {
	return Collision::Sphere_Sphere(mPosition, mRadius, other.mPosition, other.mRadius);
}

// �Փ˔���(�J�v�Z��)
bool BoundingSphere::intersects(const BoundingCapsule & other, HitInfo & hitinfo) const {
	return Collision::Sphere_Capsule(mPosition, mRadius, other.position(), other.matrix(), other.length(), other.radius());
}

// �Փ˔���(����)
bool BoundingSphere::intersects(const BoundingSegment & other, HitInfo & hitinfo) const {
	return Collision::Sphere_Segment(mPosition, mRadius, other.position(), other.matrix(), other.length());
}

// �Փ˔���(AABB)
bool BoundingSphere::intersects(const BoundingBox & other, HitInfo & hitinfo) const {
	return false;
}

// �Փ˔���(OBB)
bool BoundingSphere::intersects(const OrientedBoundingBox & other, HitInfo & hitinfo) const{
	return false;
}

// �Փ˔���(���C)
bool BoundingSphere::intersects(const Ray & other, HitInfo & hitinfo) const{
	return false;
}

// �Փ˔���(���f��)
bool BoundingSphere::intersects(const CollisionModel & other, HitInfo & hitinfo) const{
	return false;
}

// ��ܔ���(�_)
bool BoundingSphere::contains(const Vector3 & point) const{
	return Vector3::DistanceSquared(mPosition, point) <= mRadius * mRadius;
}

// ��ܔ���(��)
bool BoundingSphere::contains(const BoundingSphere & sphere) const{
	return Vector3::DistanceSquared(mPosition, sphere.position()) + sphere.radius() <= mRadius;
}

// Body�̕��s�ړ�
IBodyPtr BoundingSphere::translate(const Vector3 & pos) const {
	return std::make_shared<BoundingSphere>(translate_e(pos));
}

// Body�̕ϊ�
IBodyPtr BoundingSphere::transform(const Matrix & mat) const {
	return std::make_shared<BoundingSphere>(transform_e(mat));
}

// Body�̕��s�ړ�
BoundingSphere BoundingSphere::translate_e(const Vector3 & pos) const {
	return BoundingSphere(mPosition + pos, mRadius);
}

// Body�̕ϊ�
BoundingSphere BoundingSphere::transform_e(const Matrix & mat) const {
	return BoundingSphere(mPosition + mat.Translation(), mRadius * mat.Scale().y);
}

// �}�`�`��
void BoundingSphere::draw() const{
	//DrawSphere3D(Vector3::Vector3ToVECTOR(mCenter), mRadius, 32, GetColor(255, 0, 0), GetColor(125, 125, 125), FALSE);
}

void BoundingSphere::draw(const Vector3 & position) const
{
}

