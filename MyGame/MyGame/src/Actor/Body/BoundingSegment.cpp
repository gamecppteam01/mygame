#include "BoundingSphere.h"
#include "BoundingCapsule.h"
#include "BoundingSegment.h"
#include "BoundingBox.h"
#include "OrientedBoundingBox.h"
#include "Ray.h"
#include "CollisionModel.h"

#include "../../Math/Collision/Collision.h"

// �R���X�g���N�^
BoundingSegment::BoundingSegment(const Vector3 & pos, const Matrix & mat, const float& len):
	Body(ShapeType::Segment, pos, mat, len, true) {
	mPoints[0] = pos + Vector3::Up * len / 2;
	mPoints[1] = pos - Vector3::Up * len / 2;
}

BoundingSegment::BoundingSegment(const Vector3 & pos1, const Vector3 & pos2) :
	Body(ShapeType::Segment, 0.0f, Matrix::Identity, Vector3::Distance(pos1, pos2), true) {
	mPoints[0] = pos1;
	mPoints[1] = pos2;
}

// �Փ˔���
bool BoundingSegment::isCollide(const IBody & other, HitInfo & hitinfo) const {
	// �ǂ��炩�̔�����s��Ȃ��ꍇfalse
	if (!other.enabled() || !enabled())return false;
	
	return other.intersects(*this, hitinfo);
}

// �Փ˔���(��)
bool BoundingSegment::intersects(const BoundingSphere & other, HitInfo & hitinfo) const{
	return Collision::Sphere_Segment(other.position(), other.radius(), mPosition, mMatrix, mLength);
}

// �Փ˔���(�J�v�Z��)
bool BoundingSegment::intersects(const BoundingCapsule & other, HitInfo & hitinfo) const{
	//return Collision::Capsule_Segment(mPosition, mMatrix, mLength, other.position(), other.matrix(), other.length(), other.radius());
	return Collision::Capsule_Segment(mPoints[0], mPoints[1], other.position(), other.matrix(), other.length(), other.radius());
}

// �Փ˔���(����)
bool BoundingSegment::intersects(const BoundingSegment & other, HitInfo & hitinfo) const{
	return Collision::Segment_Segment(mPosition, mMatrix, mLength, other.mPosition, other.matrix(), other.length());
}

// �Փ˔���(AABB)
bool BoundingSegment::intersects(const BoundingBox & other, HitInfo & hitinfo) const{
	return false;
}

// �Փ˔���(OBB)
bool BoundingSegment::intersects(const OrientedBoundingBox & other, HitInfo & hitinfo) const{
	return false;
}

// �Փ˔���(���C)
bool BoundingSegment::intersects(const Ray & other, HitInfo & hitinfo) const{
	return false;
}

// �Փ˔���(���f��)
bool BoundingSegment::intersects(const CollisionModel & other, HitInfo & hitinfo) const{
	return false;
}

// Body�̕��s�ړ�
IBodyPtr BoundingSegment::translate(const Vector3 & pos) const{
	return std::make_shared<BoundingSegment>(translate_e(pos));
}

// Body�̕ϊ�
IBodyPtr BoundingSegment::transform(const Matrix & mat) const{
	return std::make_shared<BoundingSegment>(transform_e(mat));
}

// Body�̕��s�ړ�
BoundingSegment BoundingSegment::translate_e(const Vector3 & pos) const{
	return BoundingSegment(mPosition + pos, mMatrix, mLength);
}

// Body�̕ϊ�
BoundingSegment BoundingSegment::transform_e(const Matrix & mat) const{
	return BoundingSegment(mPosition + mat.Translation(), mMatrix * mat.RotationMatrix(), mLength * mat.Scale().y);
}

// �n�_����I�_�ւ̕�����Ԃ�
Vector3 BoundingSegment::Direction() const{
	Vector3 p[2];
	p[0] = mPosition + Vector3::Up * mLength / 2 * mMatrix;
	p[1] = mPosition + Vector3::Down * mLength / 2 * mMatrix;

	return Vector3::Normalize(p[0] - p[1]);
}

// �}�`�`��
void BoundingSegment::draw() const{
	Vector3 p[2];
	p[0] = mPosition + Vector3::Up * mLength / 2 * mMatrix;
	p[1] = mPosition + Vector3::Down * mLength / 2 * mMatrix;

	DrawLine3D(Vector3::Vector3ToVECTOR(p[0]), Vector3::Vector3ToVECTOR(p[1]), GetColor(255, 255, 255));
}

void BoundingSegment::draw(const Vector3 & position) const
{
	Vector3 p[2];
	p[0] = mPosition + Vector3::Up * mLength / 2 * mMatrix +position;
	p[1] = mPosition + Vector3::Down * mLength / 2 * mMatrix +position;

	DrawLine3D(Vector3::Vector3ToVECTOR(p[0]), Vector3::Vector3ToVECTOR(p[1]), GetColor(255, 255, 255));

}

