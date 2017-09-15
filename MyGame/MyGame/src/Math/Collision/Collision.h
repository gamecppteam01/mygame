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
	// 球同士の衝突判定
	static bool Sphere_Sphere(const Vector3& p1, const float& radius1, const Vector3& p2, const float& radius2);
	
	// カプセル同士の衝突判定
	static bool Capsule_Capsule(const Vector3 p1[], const float& radius1, const Vector3 p2[], const float& radius2);
	static bool Capsule_Capsule(const Vector3& pos1, const Matrix& mat1, const float & len1, const float& radius1, const Vector3& pos2, const Matrix& mat2, const float & len2, const float& radius2);

	// 線分同士の衝突判定
	static bool Segment_Segment(const Vector3 p1[], const Vector3 p2[]);
	static bool Segment_Segment(const Vector3& pos1, const Matrix& mat1, const float & length1, const Vector3& pos2, const Matrix& mat2, const float & length2);

	// 球とカプセルの衝突判定
	static bool Sphere_Capsule(const Vector3& sphere, const float& sphere_r, const Vector3 capsule[], const float& capsule_r);
	static bool Sphere_Capsule(const Vector3& sphere, const float& sphere_r, const Vector3& cap_pos, const Matrix& cap_mat, const float & cap_len, const float& cap_radius);

	// 球と線分の衝突判定
	static bool Sphere_Segment(const Vector3& sphere, const float& sphere_r, const Vector3 segment[]);
	static bool Sphere_Segment(const Vector3& sphere, const float& sphere_r, const Vector3& seg_pos, const Matrix& seg_mat, const float & seg_len);

	// カプセルと線分の衝突判定
	static bool Capsule_Segment(const Vector3 capsule[], const float& capsule_r, const Vector3 segment[]);
	static bool Capsule_Segment(const Vector3& seg_pos, const Matrix& seg_mat, const float & seg_len, const Vector3& cap_pos, const Matrix& cap_mat, const float & cap_len, const float& cap_radius);

	static std::vector<MV1_COLL_RESULT_POLY> Model_Capsule(int modelHandle, const Vector3& start, const Vector3& end,float radius);
	static bool Capsule_Triangle(const Capsule& capsule, const Triangle& poly);
};

