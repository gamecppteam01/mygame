//#pragma once
//#include "CollisionParameter.h"
//#include "../../Math/MathHelper.h"
//#include "../../Actor/Actor.h"
//
//
//// ����
//struct Line
//{
//	Vector3 startPos = Vector3::Zero;
//	Vector3 endPos = Vector3::Zero;
//
//	Line(Vector3& start, Vector3& end) :
//		startPos(start), endPos(end)
//	{}
//};
//
//// ��
//struct Sphere
//{
//	Vector3	centerPos = Vector3::Zero;
//	float	radius = 0.0f;
//
//	Sphere(Vector3& center, float r) :
//		centerPos(center), radius(r)
//	{}
//
//};
//
//// �J�v�Z��
//struct Capsule
//{
//	Vector3 startPos = Vector3::Zero;
//	Vector3 endPos = Vector3::Zero;
//	float	radius = 0.0f;
//
//	Capsule(Vector3& start, Vector3& end, float radius) :
//		startPos(start), endPos(end), radius(radius)
//	{}
//
//};
//
//// �|���S��
//struct Triangle
//{
//	Vector3	position[3];
//
//	Triangle(Vector3& p1, Vector3& p2, Vector3& p3)
//	{
//		position[0] = p1;
//		position[1] = p2;
//		position[2] = p3;
//	}
//};
//
//// ��
//struct Box
//{
//	// ���̒��S�_
//	Vector3 centerPos;
//	// ������
//	// [0]:Right
//	// [1]:Up
//	// [2]:Backward (MyMatrix Dxlib �ɂ��)
//	Vector3 rotate[3];
//	// �R�ӂ̔����̒���
//	Vector3 halfSize;
//
//	//
//	Box(Vector3& center, Vector3& x, Vector3& y, Vector3& z, Vector3& size) :
//		centerPos(center), rotate(), halfSize(size / 2.0f)
//	{
//		rotate[0] = x;
//		rotate[1] = y;
//		rotate[2] = z;
//	}
//
//};
//
//
//struct Collision
//{
//
//	// ����OBB�̏Փ˔���
//	static CollisionParameter Sphere_vs_OBB(CollisionParameter& colpara, Sphere& sphere, Box& box);
//	// �J�v�Z���ƃJ�v�Z���̏Փ˔���
//	static CollisionParameter Capsule_vs_Capsule(CollisionParameter& colpara, Capsule& c1, Capsule& c2);
//
//	// OBB�Ɠ_�̍Őڋߓ_�����߂�
//	static void ClosestPtPointOBB(CollisionParameter& colpara, Vector3& point, Box& box);
//
//};
//


#pragma once

#include "../../Math/Math.h"
#include<vector>

struct Capsule {
	Vector3 startPos = Vector3::Zero;
	Vector3 endPos = Vector3::Zero;
	float	radius = 0.0f;

	Capsule(Vector3& start, Vector3& end, float radius) :
		startPos(start), endPos(end), radius(radius){}

};

struct Triangle {
	Vector3	position[3];

	Triangle(Vector3& p1, Vector3& p2, Vector3& p3)
	{
		position[0] = p1;
		position[1] = p2;
		position[2] = p3;
	}

};

class Collision {
public:
	// �����m�̏Փ˔���
	static bool Sphere_Sphere(const Vector3& p1, const float& radius1, const Vector3& p2, const float& radius2);
	
	// �J�v�Z�����m�̏Փ˔���
	static bool Capsule_Capsule(const Vector3 p1[], const float& radius1, const Vector3 p2[], const float& radius2);
	static bool Capsule_Capsule(const Vector3& pos1, const Matrix& mat1, const float & len1, const float& radius1, const Vector3& pos2, const Matrix& mat2, const float & len2, const float& radius2);

	// �������m�̏Փ˔���
	static bool Segment_Segment(const Vector3 p1[], const Vector3 p2[]);
	static bool Segment_Segment(const Vector3& pos1, const Matrix& mat1, const float & length1, const Vector3& pos2, const Matrix& mat2, const float & length2);

	// ���ƃJ�v�Z���̏Փ˔���
	static bool Sphere_Capsule(const Vector3& sphere, const float& sphere_r, const Vector3 capsule[], const float& capsule_r);
	static bool Sphere_Capsule(const Vector3& sphere, const float& sphere_r, const Vector3& cap_pos, const Matrix& cap_mat, const float & cap_len, const float& cap_radius);

	// ���Ɛ����̏Փ˔���
	static bool Sphere_Segment(const Vector3& sphere, const float& sphere_r, const Vector3 segment[]);
	static bool Sphere_Segment(const Vector3& sphere, const float& sphere_r, const Vector3& seg_pos, const Matrix& seg_mat, const float & seg_len);

	// �J�v�Z���Ɛ����̏Փ˔���
	static bool Capsule_Segment(const Vector3 capsule[], const float& capsule_r, const Vector3 segment[]);
	static bool Capsule_Segment(const Vector3& seg_pos, const Matrix& seg_mat, const float & seg_len, const Vector3& cap_pos, const Matrix& cap_mat, const float & cap_len, const float& cap_radius);
	static bool Capsule_Segment(const Vector3 & seg_pos1, const Vector3 & seg_pos2, const Vector3 & cap_pos, const Matrix & cap_mat, const float & cap_len, const float & cap_radius);

	static std::vector<MV1_COLL_RESULT_POLY> Model_Capsule(int modelHandle, const Vector3& start, const Vector3& end,float radius);
	static bool Capsule_Triangle(const Capsule& capsule, const Triangle& poly);
};

