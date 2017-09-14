#include "Ray.h"

// �R���X�g���N�^
Ray::Ray(const Vector3 & position, const Vector3 & direction) :
	Body(ShapeType::Ray, position, Matrix::Identity, direction){}

// �Փ˔���
bool Ray::isCollide(const IBody & other, HitInfo & hitinfo) const{
	return false;
}

// �Փ˔���(��)
bool Ray::intersects(const BoundingSphere & other, HitInfo & hitinfo) const{
	return false;
}

// �Փ˔���(�J�v�Z��)
bool Ray::intersects(const BoundingCapsule & other, HitInfo & hitinfo) const{
	return false;
}

// �Փ˔���(����)
bool Ray::intersects(const BoundingSegment & other, HitInfo & hitinfo) const{
	return false;
}

// �Փ˔���(AABB)
bool Ray::intersects(const BoundingBox & other, HitInfo & hitinfo) const{
	return false;
}

// �Փ˔���(OBB)
bool Ray::intersects(const OrientedBoundingBox & other, HitInfo & hitinfo) const{
	return false;
}

// �Փ˔���(���C)
bool Ray::intersects(const Ray & other, HitInfo & hitinfo) const{
	return false;
}

// �Փ˔���(���f��)
bool Ray::intersects(const CollisionModel & other, HitInfo & hitinfo) const{
	return false;
}

// Body�̕��s�ړ�
IBodyPtr Ray::translate(const Vector3 & pos) const {
	return std::make_shared<Ray>(translate_e(pos));
}

// Body�̕ϊ�
IBodyPtr Ray::transform(const Matrix & mat) const {
	return std::make_shared<Ray>(transform_e(mat));
}

// Body�̕��s�ړ�
Ray Ray::translate_e(const Vector3 & pos) const {
	return Ray(mPosition + pos, mDirection);
}

// Body�̕ϊ�
Ray Ray::transform_e(const Matrix & mat) const {
	return Ray(mPosition * mat, mDirection);
}

// �}�`�`��
void Ray::draw() const{}

void Ray::draw(const Vector3 & position) const
{
}
